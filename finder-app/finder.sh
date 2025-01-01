#!/bin/bash
# Script to find the search string in all files for a given directory and return the results as per assignment 1
# Author: Jitesh Patel

# Check if sufficient number of arguments are passed or not
if [[ $# -lt 2 ]]
then
    echo "Error: Not enough arguments  - required two arguments, passed $# arguments. Please pass two arguments: Target Directory and String to search"
    exit 1
fi

# check if the first argument is directory or not
if [[ ! -d $1 ]]
then
    echo "Error: $1 is not directory. Please pass the first argument as valid directory."
    exit 1
fi

# count the number of files and strings found using inbuilt tools
read -r TOTAL_LINES TOTAL_FILES < <(echo $(grep -rc $2 $1 | cut -d':' -f2 | awk '{sum += $1} END {print sum,NR}'))

# final error handling if something goes wrong
if [ $? -ne 0 ]; then
    echo "Error: Something went wrong while searching for $2 string in $1 directory"
    exit 1
else
    # TODO: unclear req. Do we need to show total files even if search string was not found?
    echo "The number of files are $TOTAL_FILES and the number of matching lines are $TOTAL_LINES"
fi





