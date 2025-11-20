# FPGA DCT Project
run using 

g++ -g -Wall -Wextra dct_test.cpp top_dct.cpp dct.cpp inv_dct.cpp -o dct_test.o; ./dct_test.o

or create vitis component using function files and test bench with dct_test.cpp and in.dat, then simulate

testing update

git branch/status

# swtich to branch
git checkout project-update2 
git add.
git commit -m ""
git push

# switch to main and upidate with branch
git checkout main
git pull origin main
git merge project-update2
git push origin main

source $XILINX_VITIS/settings64.sh
source $XILINX_XRT/setup.sh

v++ -c -t hw \
    --platform xilinx_u280_gen3x16_xdma_1_202211_1 \
    --kernel top_dct \
    -o top_dct.xo \
    top_dct.cpp dct.cpp inv_dct.cpp

v++ -l -t hw \
    --platform xilinx_u280_gen3x16_xdma_1_202211_1 \
    -o top_dct.hw.xclbin \
    top_dct.xo

g++ -std=c++17 -O2 \
    dct_test.cpp dct.cpp inv_dct.cpp top_dct.cpp \
    -o dct_host

copied to node
then ran using
./dct_host top_dct.hw.xclbin in.dat