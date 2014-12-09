#ifndef ImgProcessor_h
#define ImgProcessor_h

#include "typedefs.h"
#include "BMPWriter.h"

// class for post-processing images in the form of grayvalue-matrices
class ImgProcessor{
	public:
	//-------------------------------------------------------------------------
	// analysation:
	//-------------------------------------------------------------------------
	
	// create histogram of *gray
	static vec_u32 get_histogram(mat_u8 *gray);
	// create cumulative histogram of *gray
	static vec_u32 get_cumulative_histogram(mat_u8 *gray);
	
	//-------------------------------------------------------------------------
	// visualisation:
	//-------------------------------------------------------------------------
	// create BMP-file with histogram
	static void write_hist_tofile(vec_u32 hist, const char* filename);
	
	//-------------------------------------------------------------------------
	// post-processing:
	//-------------------------------------------------------------------------
	//maximize contrast by histogram-linearization:
	static void linearisate_hist(mat_u8 *gray);
};

#endif