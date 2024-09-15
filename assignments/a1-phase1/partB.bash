#!/bin/bash

# @author Wahhaj Javed, muj975, 11135711
# @author Nakhba Mubashir, epl482, 11317060
# @date 2024-09-14

print_help() {
    echo "./partB.bash version [<threads deadline size>...]"
    echo "version is one of partA1, partA2, or partA3. partA1 is windows only"
    echo "threads is the number of threads to spawn"
    echo "deadline is the max amount of time in seconds for the parent \
        process to run"
    echo "size is the integer up to which the squares are computed"
    echo "This script will continue to run in a loop until EOF is received"
}

if [[ $# -ne 1 ]]; then
    echo "Invalid number of arguments"
    print_help
    exit 1
fi

while read -r line; do
    echo "Processing line ${line}"
done

echo "Exiting partB.bash"



