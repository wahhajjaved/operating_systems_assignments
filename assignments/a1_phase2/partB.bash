#!/bin/bash

# @author Wahhaj Javed, muj975, 11135711
# @author Nakhba Mubashir, epl482, 11317060
# @date 2024-09-14

set -e

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
    echo
    print_help
    exit 1
fi


case "$1" in
    "partA1")
        if [[ ! $(uname -s ) =~ "MINGW"  ]]; then
            echo "partA1 only works on Windows"
            echo
            print_help
            return 1
        fi
        exe=./partA1
        ;;
    "partA2")
        if [[ $(uname -s ) != "Linux" ]]; then
            echo "partA2 only works on Linux"
            echo
            print_help
            return 1
        fi
        exe=./partA2
        ;;
    "partA3")
        if [[ $(uname -s ) != "Linux" ]]; then
            echo "partA3 only works on Linux"
            echo
            print_help
            return 1
        fi
        exe=./partA3
        ;;
    *)
        echo "Unknown value for version"
        echo
        print_help
        return 1
        ;;
esac

regex_int=^[0-9]+$
runCount=0

while read -r -a line; do
    runCount=$((runCount+1))
    echo "------------------------"
    echo
    echo "------- Run: $runCount -------"
    
    if [[ ${#line[@]} -ne 3 ]]; then
        echo "Invalid number of arguments. Must be threads deadline size"
        continue
    fi

    threads="${line[0]}"
    deadline="${line[1]}"
    size="${line[2]}"

    if [[ ! "$threads" =~ $regex_int || "$threads" -le 0 ]]; then
        echo "Number of threads must be an integer greater than 0."
        continue
    fi
    if [[ ! "$deadline" =~ $regex_int || "$deadline" -le 0 ]]; then
        echo "Deadline must be an integer greater than 0."
        continue
    fi
    if [[ ! "$size" =~ $regex_int || "$size" -lt 0 ]]; then
        echo "size must be a non-negative integer."
        continue
    fi
    echo "Processing line ${line[@]} using $exe"
    $exe "$threads" "$deadline" "$size"
done

echo "Exiting partB.bash"



