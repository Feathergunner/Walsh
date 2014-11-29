#include <string>
#include <math.h>

//#include "src/WalshExpansion.cpp"
#include "include/BMPWriter.h"
#include "include/WalshExpansion.h"
#include "include/typedefs.h"
#include "include/WalshExpTypes.h"


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
    mat_u8 walsh = mat_u8(5,vec_u8(5,0));
    for (int i=0; i<5; i++)
    {
    	walsh[i][i]=240;
    	walsh[i][4-i]=240;
    }

    //get size of input-matrix:
    int width = walsh.size();
    int height = walsh[0].size();

    // change number of steps to manipulate image size
    // (image size = size^{steps+1}
    int steps = 4;

    //start walshExpansion:
    //change the used expansion function (see include/WalshExptypes.cpp and the functions in src/WalshExpansion.cpp)
    // or define your own Expansion-function
    we.generalWalshExpansion(walsh,steps,EXP_SMOOTH_STD);

    if(steps<3) we.printgray();

    //compute resultsize (needed for bmp-export)
    int res_width = pow(width,(steps+1));
    int res_height = pow(height,(steps+1));

    bw.write_sw(res_width,res_height,we.gray,"walsh.bmp");

    return 0;
}
