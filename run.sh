#!/bin/bash
#
set -e

FSCRPT=$(readlink -f "$0")
LDIR=$(dirname "$FSCRPT")

echo "Gen test ..."
cd data
./gentest
cd ..

echo ""
echo "Run CDKAM"
cd CDKAM-develop
./CDKAM.sh DTB/ ../data/input.fasta ../data/out_CDKAM.txt --fasta
cd ..

echo ""
echo "Run Kraken2"
cd kraken2
./kraken2 --db DTB ../data/input.fasta > ../data/out_kraken.txt
cd ..

echo ""
echo "Comparing result ..."
cd data
./compare
cd ..


