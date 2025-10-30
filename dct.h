/*
	Filename: dct.h
	Header file
*/
//#include <ap_int.h>
#ifndef DCT_H_
#define DCT_H_

#define IDX(r,c,W) ((r)*(W) + (c))
#define AP 256

// typedef ap_int<5> data_t;
typedef int	data_t;
typedef int	coef_t;

void dct (
  data_t A[],
  coef_t B[],
  int W,
  int H,
  int size,
  float &Q
  );

#endif
