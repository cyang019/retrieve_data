# Table of Contents
1. [Abstract](#abstract)
2. [Details of implementation](#details-of-implementation)
3. [How to use the code](#how-to-use-the-code)
4. [Additional Info](#additional-info)

# Abstract
This repo provides support to retrieve campaign contribution data from Federal Election Commission (FEC). Input files containing contributions by individuals can be downloaded from the [FEC website](http://classic.fec.gov/finance/disclosure/ftpdet.shtml). Data formats are explained [here](http://classic.fec.gov/finance/disclosure/metadata/DataDictionaryContributionsbyIndividuals.shtml). The focus of this repo is to export median values categorized using Filer Identification Number, zipcode, and transaction date from the raw data on the FEC webpage. To accomplish this task, as each line from an input file being fed into a parser, one output file keeps track of the running median of a recipient (CMTE_ID) and zipcode, while the other output sorts and summaries the medians using unique combinations of recipients and transaction dates. Both [C++ implementation](src/donation_analysis_cpp) and [python3 implementation](src/donation_analysis) are shown inside the repo.

# Details of implementation
### A high level description
1. a parser is created. 
2. for each line of input, its fields corresponding to `CMTE_ID`, `ZIP_CODE`, `TRANSACTION_DT`, `TRANSACTION_AMT`, and `OTHER_ID` are extracted. 
2. If the line is valid (with a non-empty `CMTE_ID`, empty `OTHER_ID` and non-negative `TRANSACTION_AMT`) the data is taken. 
3. If `ZIP_CODE` is valid (at least 5 digits), it would be stored in a _running median_ container. The running median along with count and total amount are calculated right away for the recipient with a zipcode. These values are written to `medianvals_by_zip.txt` directly.
4. If `TRANSACTION_DT` is valid (**mmddyyyy**), it would be stored in a _static median_ container for later calculation.
5. After input of all lines finish, calculate median from values contained in the _static median_container and output to file `medianvals_by_date.txt`.

### Explanation of Components



## C++ Implementation 





# How to use the code

