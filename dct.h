/*
	Filename: dct.h
	Header file
*/
#include "types.h"

#ifndef DCT_H_
#define DCT_H_

void dct (
  data_t A[],
  coef_t B[],
  int W,
  int H,
  float &Q
  );

#endif
