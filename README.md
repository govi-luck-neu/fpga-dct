# FPGA DCT Project
run using 

g++ -g -Wall -Wextra dct_test.cpp top_dct.cpp dct.cpp inv_dct.cpp -o dct_test.o; ./dct_test.o

or create vitis component using function files and test bench with dct_test.cpp and in.dat, then simulate