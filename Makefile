



dct:
	g++ -g -Wall -Wextra -Wno-unused-label dct_test.cpp top_dct.cpp dct.cpp inv_dct.cpp -o dct_test.o
	
run: dct
	./dct_test.o