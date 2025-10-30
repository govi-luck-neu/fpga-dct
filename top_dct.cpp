/*
	Filename: dct.cpp

	INPUT:
		A[W*H]: signal matrix

	OUTPUT:
        B[W*H]: dct coef signal matrix
		C[W*H]: reconstructed  signal matrix

*/
#include "dct.h"
#include "inv_dct.h"

void top_dct (
  data_t A[],
  coef_t B[],
  data_t C[],
  int W,
  int H,
  int size,
  float &Q
  ) {

  dct(A, B, W, H, size, Q);
  inv_dct(B, C, W, H, size, Q);

  }