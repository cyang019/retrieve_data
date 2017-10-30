#!/bin/bash

# ---------------------------------------------------------------------
## python implementation
## Uncomment the line below and comment out everything else for executing the python version.
#python ./src/find_political_donors.py ./input/itcont.txt ./output/medianvals_by_zip.txt ./output/medianvals_by_date.txt
# ---------------------------------------------------------------------


# ---------------------------------------------------------------------
## cpp implementation
## Uncomment the lines below with a single '#' to use cpp implementations
####################
## use cmake to compile if file not already compiled
if [ ! -e find_political_donors ]
then
    mkdir build
    cd build
    cmake ../src/donation_analysis_cpp

    ## make will generate executable in the parent directory
    make
fi
#####################
#
## change back to parent directory
cd ..
## execute
./find_political_donors ./input/itcont.txt ./output/medianvals_by_zip.txt ./output/medianvals_by_date.txt
# ---------------------------------------------------------------------
