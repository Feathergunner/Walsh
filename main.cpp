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

    /*
        construct a starting-matrix:
        this constructs a version of the standart-walsh-matrix
        0  0
        0 255
        (note that in the .bmp-output, 0 results in a black and 255 in a white pixel)
    */

    // define your own matrix here to produce individual images:
	
	mat_u8 tl = mat_u8(5,vec_u8(5,0));
	for (int i=0; i<5; i++){
		if(i!=3)
		{
			tl[i][4] = 255;
			tl[4][i] = 255;
		}
		if (i>1)
			tl[i][i] = 255;
		else
			tl[1-i][i] = 255;
	}
	
	mat_u8 smooth = mat_u8(5,vec_u8(5,99));
	smooth[0][0] = 50;
	smooth[0][1] = 55;
	smooth[1][0] = 55;
	smooth[1][1] = 60;
	smooth[0][2] = 65;
	smooth[2][0] = 65;
	smooth[2][1] = 70;
	smooth[1][2] = 70;
	smooth[2][2] = 75;
	smooth[3][0] = 80;
	smooth[0][3] = 80;
	smooth[3][1] = 85;
	smooth[1][3] = 85;
	smooth[3][2] = 90;
	smooth[2][3] = 90;
	smooth[3][3] = 95;
	
	MatrixBuilder::smoothen_Matrix(&tl, smooth);
	
	mat_u8 walsh = MatrixBuilder::symmetric_Matrix_Expansion(tl);
	MatrixBuilder::print_Matrix(walsh);
	
	/*
	int ss = 9;
	mat_u8 walsh = mat_u8(ss,vec_u8(ss,0));
    for (int i=0; i<ss; i++)
    {
		if (i > 1 && i < 7)
		{
			walsh[i][i]=240;
			walsh[i][ss-1-i]=240;
		}else{
			if (i<2){
				walsh[1-i][i] = 230;
				walsh[i][1-i] = 230;
			}else{
				walsh[8-i][i] = 230;
				walsh[i][8-i] = 230;
			}
		}
		if (i != 3 && i != 5)
		{
			walsh[4][i] = 230;
			walsh[i][4] = 230;
		}
    }
	*/

    //get size of input-matrix:
    int width = walsh.size();
    int height = walsh[0].size();

    // change number of steps to manipulate image size
    // (image size = size^{steps+1}
    int steps = 3;

    //start walshExpansion:
    //change the used expansion function (see include/WalshExptypes.cpp and the functions in src/WalshExpansion.cpp)
    // or define your own Expansion-function
    we.generalWalshExpansion(walsh,steps,EXP_SMOOTH_NOI2);

    if(steps<2) we.printgray();

    //compute resultsize (needed for bmp-export)
    int res_width = pow(width,(steps+1));
    int res_height = pow(height,(steps+1));

    bw.write_sw(res_width,res_height,we.gray,"walsh.bmp");

    return 0;
}
