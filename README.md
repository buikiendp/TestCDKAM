# TestCDKAM
Testing scripts for CDKAM and other tools\
This tool installs CDKAM and Kraken2 inside the current folder. Then, it generates simulated read, run both CDKAM and Kraken2. After that, the classification results are compared with the original taxonomy at Genus and Species level.

(1) Install\
./install_CDKAM.sh\
./install_kraken2.sh\
./pre-install.sh

(2) Testing:\
./run.sh readLength errorRate
