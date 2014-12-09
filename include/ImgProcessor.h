#ifndef ImgProcessor_h
#define ImgProcessor_h

#include "typedefs.h"

// class for post-processing images in the form of grayvalue-matrices
class ImgProcessor{
	public:
	// analysation:
	vec_u32 get_histogram(mat_u8 *gray);
	vec_u32 get_cumulative_histogram(mat_u8 *gray);
	
	// post-processing: maximize contrast by histogram-linearization
	void linearisate_hist(mat_u8 *gray);
};

#endif