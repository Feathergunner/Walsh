#include <string>
#include <math.h>
#include <iostream>

//#include "src/WalshExpansion.cpp"
#include "include/BMPWriter.h"
#include "include/WalshExpansion.h"
#include "include/typedefs.h"
#include "include/WalshExpTypes.h"
#include "include/MatrixBuilder.h"


int main(){
    //init:
    WalshExpansion we = WalshExpansion();
    BMPWriter bw = BMPWriter();

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
	
	walsh = MatrixBuilder::get_predefined_Matrix(2);
	
	MatrixBuilder::print_Matrix(walsh);
	

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

    //compute resultsize (needed for bmp-export)
    int res_width = pow(width,(steps+1));
    int res_height = pow(height,(steps+1));

    bw.write_sw(res_width,res_height,we.gray,"walsh.bmp");

    return 0;
}
