#!/bin/bash
#
set -e

FSCRPT=$(readlink -f "$0")
LDIR=$(dirname "$FSCRPT")

git clone https://github.com/SJTU-CGM/CDKAM
cd CDKAM
./install.sh
mkdir DTB
./download_taxonomy.sh DTB/
./download --download-library archaea --db DTB/
./download --download-library viral --db DTB/
./download --download-library fungi --db DTB/

./build_database.sh DTB/
#mv -R test ../



