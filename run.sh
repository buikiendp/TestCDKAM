#!/bin/bash
#
set -e

FSCRPT=$(readlink -f "$0")
LDIR=$(dirname "$FSCRPT")

if [ $# -lt 2 ]; then
	echo "Usage: $0 readLength errorRate"
	exit
fi

if [ $1 -lt 500 ] || [ $1 -gt 5000 ]; then
	echo "The length of read should be > 1000 and < 500 bps"
	exit 0
fi

if [ $2 -gt 20 ]; then
	echo "The error rate should be < 20%"
	exit 0
fi

echo "(1) GEN TEST ..."
cd data
./gentest $1 $2
cd ..

echo ""
echo "(2) RUN CDKAM ..."
cd CDKAM
./CDKAM.sh DTB/ ../data/input.fasta ../data/out_CDKAM.txt --fasta
cd ..

echo ""
echo "(3) RUN Kraken2 ..."
cd kraken2
./kraken2 --db DTB ../data/input.fasta > ../data/out_kraken.txt
cd ..

echo ""
echo "(4) COMPARE RESULT ..."
cd data
./compare
cd ..


