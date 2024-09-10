#!/bin/bash

if [[ "$#" -ne 1 ]]; then
    echo "Incorrect number of arguments"
    echo "Usage: ./run-lab1.bash counter"
    exit 1
fi

case $(uname -m) in

    x86_64)
        echo "Running sample-linux-x86_64"
        ./sample-linux-x86_64 "$1"
        ;;
    armv7l)
        echo "Running sample-linux-armv7l"
        ./sample-linux-armv7l "$1"
        ;;
    ppc)
        echo "Running sample-linux-ppc"
        ./sample-linux-ppc "$1"
        ;;
    *)
        echo "No executale available for $(uname -m)"
        ;;
esac

