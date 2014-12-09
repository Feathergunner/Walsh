#include "../include/ImgProcessor.h"
#include <iostream>

vec_u32 ImgProcessor::get_histogram(mat_u8* gray)
{
	uint32_t gray_size_x = (*gray).size();
	uint32_t gray_size_y = (*gray)[0].size();
	
	// construct histogram:
	vec_u32 histogram = vec_u32(255,0);
	for (int i=0; i<gray_size_x; i++){
		for (int j=0; j<gray_size_y; j++){
			histogram[(*gray)[i][j]]++;
		}
	}
	return histogram;
}

vec_u32 ImgProcessor::get_cumulative_histogram(mat_u8 *gray)
{
	vec_u32 histogram = get_histogram(gray);
	
	// get cumulative histogram
	vec_u32 c_histogram = vec_u32(255,0);
	c_histogram[0] = histogram[0];
	for (int i=1; i<255; i++)
		c_histogram[i] = c_histogram[i-1] + histogram[i];
		
	return c_histogram;
}

void ImgProcessor::write_hist_tofile(vec_u32 hist, const char* filename)
{
	// matrix for the image
	// initialise with 200 ( = light gray)
	mat_u8 histgray = mat_u8(255, vec_u8(255,200));
	
	// scale values of hist:
	// get max:
	uint32_t max = hist[0];
	for (int i=1; i<hist.size(); i++)
	{
		if (hist[i] > max)
			max = hist[i];
	}
	
	uint32_t scale = max/255;
	
	// construct matrix:
	for (int i=0; i<255; i++){
		int scaled_val = hist[i]/scale;
		for (int j=0; j<scaled_val; j++)
			histgray[i][254-j] = 0;
	}
	//print to *.bmp-file
	BMPWriter::write_sw(255,255,histgray, filename);
	return;
}

void ImgProcessor::linearisate_hist(mat_u8 *gray)
{
	uint32_t gray_size_x = (*gray).size();
	uint32_t gray_size_y = (*gray)[0].size();
	uint32_t total = gray_size_x * gray_size_y;
	
	// get cumulative histogram
	vec_u32 cum_histogram = get_cumulative_histogram(gray);
	
	// get linearisation:
	vec_u32 lin = vec_u32(255,0);
	for (int i=0; i<255; i++)
		lin[i] = (255*cum_histogram[i])/total;
	
	// apply linearisation to gray
	for (int i=0; i<gray_size_x; i++){
		for (int j=0; j<gray_size_y; j++){
			uint8_t tmp = (*gray)[i][j];
			(*gray)[i][j] = lin[tmp];
		}
	}
	
	return;
}