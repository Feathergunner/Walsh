#include <string>
#include <math.h>

#include "src/WalshExpansion.cpp"
#include "src/BMPWriter.cpp"
#include "include/typedefs.h"
#include "include/WalshExpTypes.cpp"


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
    mat_u8 walsh = mat_u8(2,vec_u8(2,0));
    walsh[0][0]=250;
    walsh[1][1]=150;

    //get size of input-matrix:
    int width = walsh.size();
    int height = walsh[0].size();

    int steps = 9;

    //start walshExpansion:
    //we.discreteWalshExpansion(width,height,walsh,steps);
    we.generalWalshExpansion(width,height,walsh,steps,EXP_SMOOTH_NOIZ);

    if(steps<5) we.printgray();

    //compute resultsize (needed for bmp-export)
    int res_width = pow(width,(steps+1));
    int res_height = pow(height,(steps+1));

    bw.write_sw(res_width,res_height,we.gray,"walsh.bmp");

    return 0;
}
