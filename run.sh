#!/bin/bash

# ---------------------------------------------------------------------
# python implementation
# Uncomment the line below and comment out everything else for executing the python version.
python ./src/find_political_donors.py ./raw_input/itcont.txt ./output/python_zip.txt ./output/python_date.txt
# ---------------------------------------------------------------------


# ---------------------------------------------------------------------
# cpp implementation
## Uncomment the lines below with a single '#' to use cpp implementations
####################
## use cmake to compile
#mkdir build
#cd build
#cmake ../src/donation_analysis_cpp
#
## make will generate executable in the parent directory
#make
#####################
#
## change back to parent directory
#cd ..
## execute
./find_political_donors ./raw_input/itcont.txt ./output/cpp_zip.txt ./output/cpp_date.txt
# ---------------------------------------------------------------------
