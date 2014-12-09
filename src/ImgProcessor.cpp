#include "../include/ImgProcessor.h"

vec_u32 ImgProcessor::get_histogram(mat_u8* gray)
{
	uint32_t gray_size_x = (*gray).size();
	uint32_t gray_size_y = (*gray)[0].size();
	
	// construct histogram:
	vec_u32 histogram = vector<uint32_t>(255,0);
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
	c_histogram[0] = histogram[0]
	for (int i=1; i<255; i++)
		c_histogram[i] = c_histogam[i-1] + histogram[i];
		
	return c_histogram;
}

void ImgProcessor::linearisate_hist(mat_u8 *gray)
{
	uint32_t gray_size_x = (*gray).size();
	uint32_t gray_size_y = (*gray)[0].size();
	uint32_t total = gray_size_x * gray_size_y;
	
	// get cumulative histogram
	vec_u32 cum_histogram = get_cumulative_histogram(gray)M
	
	// get linearisation:
	vec_u32 lin = vec_u32(255,0);
	int j=0;
	for (int i=0; i<255; i++)
	{
		lin[i] = 255/(total*cum_histogram[i]);
	}
	
	// apply linearisation to gray
	for (int i=0; i<gray_size_x; i++){
		for (int j=0; j<gray_size_y; j++){
			uint8_t tmp = (*gray)[i][j];
			(*gray)[i][j] = lin[tmp];
		}
	}
	
	return;
}