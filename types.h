/*
	Filename: types.h
	Header file
*/
// #include <ap_int.h>
// #include <ap_fixed.h>

typedef double	data_t;
// typedef ap_uint<8>   data_t;

typedef int	coef_t;
// typedef ap_int<16>   coef_t;

typedef double calc_t;
// typedef ap_fixed<24,16> calc_t;


#ifndef IDX
#define IDX(r,c,W) ((r)*(W) + (c))
#endif

#ifndef AP
#define AP 256
#endif
