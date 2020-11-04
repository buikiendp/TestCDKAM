#!/bin/bash
#
set -e

FSCRPT=$(readlink -f "$0")
LDIR=$(dirname "$FSCRPT")

git clone https://github.com/DerrickWood/kraken2
cd kraken2
./install_kraken2.sh ./
mkdir DTB
./kraken2-build --download-taxonomy --db DTB
./kraken2-build --download-library archaea --db DTB
./kraken2-build --download-library viral --db DTB
./kraken2-build --download-library fungi --db DTB

./kraken2-build --build --db DTB





