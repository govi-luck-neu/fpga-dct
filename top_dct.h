/*
	Filename: top_dct.h
	Header file
*/
//#include <ap_int.h>
#ifndef TOP_DCT_H_
#define TOP_DCT_H_

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
  );

#endif
