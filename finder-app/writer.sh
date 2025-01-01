#!/bin/bash
# Script to create or overwrite the file with given string at desired location as per assignment description
# Author: Jitesh Patel

# Check if sufficient number of arguments are passed or not
if [[ $# -lt 2 ]]
then
    echo "Error: Not enough arguments  - required two arguments, passed $# arguments. Please pass two arguments: Full path for the file and String to write"
    exit 1
fi

# check if the first argument is directory or not
if [[ -d $1 ]]
then
    echo "Error: $1 is directory. Please use the full file path"
    exit 1
fi

# Create the full path and write to the file
mkdir -p "$(dirname "$1")" && echo "$2" | cat > "$1"

# final error handling if something goes wrong (wrong permission, file io error etc)
if [ $? -ne 0 ]; then
    echo "Error: Something went wrong while writing string $2 in file located at $1"
    exit 1
fi