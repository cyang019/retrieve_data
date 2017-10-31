# Table of Contents
1. [Abstract](#abstract)
2. [Details of implementation](#details-of-implementation)
3. [How to use the code](#how-to-use-the-code)
4. [Additional info](#additional-info)

# Abstract
This repo provides support to retrieve campaign contribution data from Federal Election Commission (FEC). Input files containing contributions by individuals can be downloaded from the [FEC website](http://classic.fec.gov/finance/disclosure/ftpdet.shtml). Data formats are explained [here](http://classic.fec.gov/finance/disclosure/metadata/DataDictionaryContributionsbyIndividuals.shtml). The focus of this repo is to export median values categorized using Filer Identification Number, zipcode, and transaction date from the raw data on the FEC webpage. To accomplish this task, as each line from an input file being fed into a parser, one output file keeps track of the running median of a recipient (CMTE_ID) and zipcode, while the other output sorts and summaries the medians using unique combinations of recipients and transaction dates. Both [C++ implementation](src/donation_analysis_cpp) and [python3 implementation](src/donation_analysis) are shown inside the repo.

# Details of implementation
### A high level description
1. a parser is created. 
2. for each line of input, its fields corresponding to `CMTE_ID`, `ZIP_CODE`, `TRANSACTION_DT`, `TRANSACTION_AMT`, and `OTHER_ID` are extracted. 
2. If the line is valid (with a non-empty `CMTE_ID`, empty `OTHER_ID` and non-negative `TRANSACTION_AMT`) the data is taken. 
3. If `ZIP_CODE` is valid (at least 5 digits), it would be stored in a _running median_ container. The running median along with count and total amount are calculated right away for the recipient with a zipcode. These values are written to `medianvals_by_zip.txt` directly.
4. If `TRANSACTION_DT` is valid (*mmddyyyy*), it would be stored in a _static median_ container for later calculation.
5. After input of all lines finish, calculate median from values contained in the _static median_ container and output to file `medianvals_by_date.txt`.

### Explanation of Components
* The running median calculator was implemented using two heaps. A max heap keeps track of the maximum value of the lower half of stored values, while a min heap keeps track of the minimum value of the upper half of stored values. They should either contain same number of elements or have the number of elements differ by 1. The time complexity for inserting an element would be bounded by O(logn) and retrieve the value would be an O(1) operation. The algorithm would take O(n) space for median calculation.
* The calculator for median by date uses a simple array type of container, so that insert an element would cost O(1). And since median is only calculated once for all data, a quick select type of algorithm is utilized for C++ implementation by `std::nth_element`. This implementation would cost O(n) on average, with the worst case costing O(n^2). For python implementation sorting and then selecting middle value was used (O(nlogn)). Quick select was not chosen because it did not show any improvements when parsing the entire 2015-2016 data set as input. The reason could be the small number of elements contained for most recipient date pair.
* To keep track of cmte_id-zipcode pair or cmte_id-date pair, in python implementation, dictionary was used to store a median container for each unique pair. In C++ implementation, strategy pattern was used for both median calculation container and tracker for each two level key-pairs. The tracker for both zipcode and date has the same interface to add in data and to retrieve data. And the median containers both use `push()` to add in values and `calcMedian()` for median calculation. In tracking zipcode, `std::unordered_map` was used, while in tracking date, `std::map` was used with a customized comparison function to sort dates in chronological order. Python dictionary was easy enough to use directly, and because of duck typing, such inheritance was not used in the python code. 

# How to use the code
* The [run.sh](run.sh) contains script to take input file with name `itcont.txt` from [input](input) directory, and would create `medianvals_by_zip.txt` and `medianvals_by_date` in the [output](output) directory. **By default, C++ implementation is enabled.** To use python implementation, uncomment `python ./src/find_political_donors.py ./input/itcont.txt ./output/medianvals_by_zip.txt ./output/medianvals_by_date.txt` and comment out all rest lines by `#`. To use C++ implementation, uncomment line 17 through 31 if no double `#` was presented on that line, and comment out the python implementation line.
* To use the C++ implementations for containers and median calculators as a separate library, change the **OFF** to **ON** in the [CMakeLists.txt](src/donation_analysis_cpp/CMakeLists.txt) on line 8: `option(INDEPENDENT_LIB "build an independent library" OFF)`. and then create a directory `build`, `cd build`, `cmake ..`, then `make install`. The library would be installed in `src/cpp_impl` after `make install`. To delete the libary, simply remove the created directory and the files inside it.


# Additional info
* unittests for C++ source code are located inside [src/unittest_cpp](src/unittest_cpp). googletest was configured using cmake.
* unittests for python source code are located inside [src/unittest_py3](src/unittest_py3).
