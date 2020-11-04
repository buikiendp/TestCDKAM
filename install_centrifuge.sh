#!/bin/bash
#
set -e

FSCRPT=$(readlink -f "$0")
LDIR=$(dirname "$FSCRPT")

git clone https://github.com/DaehwanKimLab/centrifuge
cd centrifuge
centrifuge-download -o taxonomy taxonomy
centrifuge-download -o library -m -d "archaea,fungi,viral" refseq > seqid2taxid.map

cat library/*/*.fna > input-sequences.fna
centrifuge-build -p 4 --conversion-table seqid2taxid.map \
                 --taxonomy-tree taxonomy/nodes.dmp --name-table taxonomy/names.dmp \
                 input-sequences.fna abv




