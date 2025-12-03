/*
	Filename: inv_dct.h
	Header file
*/
#include "types.h"

#ifndef INV_DCT_H_
#define INV_DCT_H_

void inv_dct (
  coef_t A[],
  data_t B[],
  int W,
  int H,
  float Q
  );

#endif
