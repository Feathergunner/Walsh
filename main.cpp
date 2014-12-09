#include <string>
#include <math.h>
#include <iostream>

#include "include/BMPWriter.h"
#include "include/WalshExpansion.h"
#include "include/typedefs.h"
#include "include/WalshExpTypes.h"
#include "include/MatrixBuilder.h"
#include "include/ImgProcessor.h"

int main(){
    //init:
    WalshExpansion we = WalshExpansion();

	mat_u8 walsh;
	
    /*
        construct a starting-matrix:
        this constructs a version of the standart-walsh-matrix
        0  0
        0 255
        (note that in the .bmp-output, 0 results in a black and 255 in a white pixel)
		
		walsh = mat_u8(2,vec_u8(2,0);
		walsh[1][1] = 255;
    */

    // define your own matrix here to produce individual images:
	
	walsh = MatrixBuilder::get_predefined_Matrix(4);
	
	//MatrixBuilder::print_Matrix(walsh);
	

    //get size of input-matrix:
    int width = walsh.size();
    int height = walsh[0].size();

    // change number of steps to manipulate image size
    // (image size = size^{steps+1}
    int steps = 4;

    //start walshExpansion:
    //change the used expansion function (see include/WalshExptypes.h and the functions in include/WalshTransformations.h)
    // or define your own Expansion-function
    we.generalWalshExpansion(walsh,steps,EXP_SMOOTH_STD);

    if(steps<2) we.printgray();
	
	// compute histogramm and cumulative histogram
	/*
	vec_u32 hist = ImgProcessor::get_histogram(&(we.gray));
	vec_u32 c_hist = ImgProcessor::get_cumulative_histogram(&(we.gray));
	ImgProcessor::write_hist_tofile(hist, "histogram.bmp");
	ImgProcessor::write_hist_tofile(c_hist, "histogram_cumulative.bmp");
	*/
	
	// apply histogram linearisation
	ImgProcessor::linearisate_hist(&(we.gray));
	
	
	// compute histogram and cumulative histogram (after linearisation)
	/*
	vec_u32 hist_l = ImgProcessor::get_histogram(&(we.gray));
	vec_u32 c_hist_l = ImgProcessor::get_cumulative_histogram(&(we.gray));
	ImgProcessor::write_hist_tofile(hist_l, "histogram_lin.bmp");
	ImgProcessor::write_hist_tofile(c_hist_l, "histogram_lin_cumulative.bmp");
	*/

    //compute resultsize (needed for bmp-export)
    int res_width = pow(width,(steps+1));
    int res_height = pow(height,(steps+1));

    BMPWriter::write_sw(res_width,res_height,we.gray,"walsh.bmp");

    return 0;
}
