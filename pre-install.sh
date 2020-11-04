#!/bin/bash
#
set -e

FSCRPT=$(readlink -f "$0")
LDIR=$(dirname "$FSCRPT")

#cp $LDIR/CDKAM/DTB/targets.txt $LDIR/inputData

cd test
cp ../CDKAM/DTB/targets.txt ./
g++ -std=c++11 gentest.cpp -o gentest
g++ -std=c++11 compare_result.cpp -o compare
cd ..

