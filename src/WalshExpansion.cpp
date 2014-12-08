#include "../include/WalshExpansion.h"
#include <iostream>

void WalshExpansion::init(mat_u8 a){
	startMatrix = a;
	aw = a.size();
	ah = a[0].size();
}

//simple method to invert 8-bit-grayvalues:
uint8_t WalshExpansion::invert(uint8_t val){
    return 255-val;
}

/*
 simple invert method
*/
uint8_t WalshExpansion::discreteTransform(uint8_t base, uint8_t factor){
    if (factor > 127) return invert(base);
    else return base;
}

/*
 smooth transformation of grayscale-values:

 - base: the current value to copy in the output-matrix
 - factor: the coresponding value in the input-matrix

 rules of thumb:
 - f == 0 or f == 255 => equivalent to simple invert-method
 - f in between => new value gets compressed towards 127(gray)
   - f < 127 => orientation of b inverted (<127 => >127 or >127 => <127)
   - f > 127 => orientation of b stayes as-is
 - independent of orientation, b becomes compressed like new=b*f/128
*/
uint8_t WalshExpansion::Transform(uint8_t base, uint8_t factor, uint16_t(*func)(uint16_t, uint16_t))
{
	// Init for transform:
	uint16_t ret_16, b_16, f_16;
    uint8_t ret_8;
    bool inv = false, bigbase = false;
    if (factor > 127){
    	inv = true;
    	f_16 = factor-127;
    }else f_16 = 127-factor;
    if (base > 127){
    	bigbase = true;
    	b_16 = base - 127;
    }else b_16 = 127-base;
    
    // Do the transformation, use the functionpointer given as parameter:
    ret_16 = func(b_16,f_16);
    
    // finalise: downscale to 8 bit and get orientation right
    ret_8 = (uint8_t)ret_16;

    if (bigbase) ret_8 += 127;
    else ret_8 = 127-ret_8;
    if (inv) return invert(ret_8);
    else return ret_8;
}

/*
    general WalshExpansion for Matrix A
    - all the values from A are in (0,255)
    - transforms by specified method type
    Expanded Matrix is saved in classvar gray
*/
bool WalshExpansion::generalWalshExpansion(mat_u8 a, uint8_t num_of_iterations, WalshExpType type){
		
	init(a);
	
    //initialise final matrix:
    //size:
	float wf = pow(aw,(num_of_iterations+1));
	float hf = pow(ah,(num_of_iterations+1));
    width = (uint32_t) wf;
    height = (uint32_t) hf;
	
    //matrix:
    gray = mat_u8(width, vec_u8(height,0));
    //initialise top left with inputmatrix A:
    for (int x=0; x<aw; x++)
        for (int y=0; y<ah; y++)
            gray[x][y] = startMatrix[x][y];

    //initialise vars for size of iteration: the size of the current matrix
    uint32_t w_it, h_it, w_lit, h_lit;
    //initialised with size of input-matrix:
    w_it = aw;
    h_it = ah;

    //BEGIN THE ITERATIONS!
    for (int i=0; i<num_of_iterations; i++){
        w_lit = w_it;
        h_lit = h_it;
        w_it *= ah;
        h_it *= ah;

        //Iterate through inputmatrix A:
        computeIteration(w_it, h_it, w_lit, h_lit, type); 
    }
    return true;
}

void WalshExpansion::computeIteration(uint32_t w_it, uint32_t h_it, uint32_t w_lit, uint32_t h_lit, WalshExpType type){
	// initialise tmp: a copy of the output of last iteration
	mat_u8 tmp = mat_u8(w_lit, vec_u8(w_lit,0));
	for (int tx=0; tx<w_lit; tx++)
		for (int ty=0; ty<h_lit; ty++)
			tmp[tx][ty]=gray[tx][ty];
	
	for (int x=0; x<aw; x++){
		for (int y=0; y<ah; y++){
			// for every position in A, copy (and invert, if A[x][y]==255)
			// the matrix computed in the last step to new position
			for (int xx=0; xx<w_lit; xx++){
				for (int yy=0; yy<h_lit; yy++){
					switch(type){
					case EXP_DISCRETE    :
						gray[w_lit*x+xx][h_lit*y+yy] = discreteTransform( tmp[xx][yy] , startMatrix[x][y] );
						break;
					case EXP_SMOOTH_STD  :
						gray[w_lit*x+xx][h_lit*y+yy] = Transform( tmp[xx][yy] , startMatrix[x][y], WalshTransformations::smoothTransform );
						break;
					case EXP_SMOOTH_MID  :
						gray[w_lit*x+xx][h_lit*y+yy] = Transform( tmp[xx][yy] , startMatrix[x][y], WalshTransformations::smoothMidTransform );
						break;
					case EXP_SMOOTH_NOIZ :
						gray[w_lit*x+xx][h_lit*y+yy] = Transform( tmp[xx][yy] , startMatrix[x][y], WalshTransformations::noizeTransform );
						break;
					case EXP_SMOOTH_NOI2 :
						gray[w_lit*x+xx][h_lit*y+yy] = Transform( tmp[xx][yy] , startMatrix[x][y], WalshTransformations::noiz2Transform );
						break;
					case EXP_SMOOTH_NOI3 :
						gray[w_lit*x+xx][h_lit*y+yy] = Transform( tmp[xx][yy] , startMatrix[x][y], WalshTransformations::noiz3Transform );
						break;
					}
				}
			}		 
		}
	}
}


/*
    For Debugging purpose: prints the gray-matrix to console-output
*/
bool WalshExpansion::printgray(){
    for (uint32_t x=0; x<width; x++){
        for (uint32_t y=0; y<height; y++){
            printf("%3i ",gray[x][y]);
        }
        printf("\n");
    }

    return true;
}
