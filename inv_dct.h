/*
	Filename: inv_dct.h
	Header file
*/
//#include <ap_int.h>
#ifndef INV_DCT_H_
#define INV_DCT_H_

#ifndef IDX
#define IDX(r,c,W) ((r)*(W) + (c))
#endif

// typedef ap_int<5> data_t;
typedef int	data_t;
typedef int	coef_t;

void inv_dct (
  data_t A[],
  coef_t B[],
  int W,
  int H,
  int size,
  float Q
  );

#endif
