#include "../include/WalshExpansion.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

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
uint8_t WalshExpansion::smoothTransform(uint8_t base, uint8_t factor){
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

    ret_16 = (b_16 * f_16)/128;
    ret_8 = (uint8_t)ret_16;

    if (bigbase) ret_8 += 127;
    else ret_8 = 127-ret_8;
    if (inv) return invert(ret_8);
    else return ret_8;
}

/*
 like smooth transform, but computes midvalue between base- and factor- grayvalue
*/
uint8_t WalshExpansion::smoothMidTransform(uint8_t base, uint8_t factor){
    uint8_t ret;
    bool inv = false, bigbase = false;
    if (factor > 127){
    	inv = true;
    	factor -= 127;
    }else factor = 127-factor;
    if (base > 127){
    	bigbase = true;
    	base -= 127;
    }else base = 127-base;

    ret = (base * factor)/128;

    if (bigbase) ret += 127;
    else ret = 127-ret;
    if (inv) return invert(ret);
    else return ret;
}

/*
 a purposly buggy transform that creates a strong noize-effect by uint8-overflow
*/
uint8_t WalshExpansion::noizeTransform(uint8_t base, uint8_t factor){
    uint8_t ret;
    bool inv = false, bigbase = false;
    if (factor > 127){
    	inv = true;
    	factor -= 127;
    }else factor = 127-factor;
    if (base > 127){
    	bigbase = true;
    	base -= 127;
    }else base = 127-base;

    ret = base*factor;

    if (bigbase) ret += 127;
    else ret = 127-ret;
    if (inv) return invert(ret);
    else return ret;
}

/*
 aaaaand another one
 aim is to create a glitch-like noize-effect by changing the grayvalues to constants within certain intervals
*/
uint8_t WalshExpansion::noiz2Transform(uint8_t base, uint8_t factor){
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

    ret_16 = (b_16 * f_16)/128;
    ret_8 = (uint8_t)ret_16;
    if (ret_8 > 28 && ret_8 < 36) ret_8 = 125;
    if (ret_8 > 92 && ret_8 < 100) ret_8 = 125;

    if (bigbase) ret_8 += 127;
    else ret_8 = 127-ret_8;
    if (inv) return invert(ret_8);
    else return ret_8;
}

/*
 aaaaand another one
 this one ignoring orientaton, creating darker results:
*/
uint8_t WalshExpansion::noiz3Transform(uint8_t base, uint8_t factor){
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

    ret_16 = (b_16 * f_16)/128;
    return (uint8_t)ret_16;
}

/*
    general WalshExpansion for Matrix A
    - all the values from A are in (0,255)
    - transforms by specified method type
    Expanded Matrix is saved in classvar gray
*/
bool WalshExpansion::generalWalshExpansion(uint8_t Aw, uint8_t Ah, mat_u8 A, uint8_t num_of_iterations, WalshExpType type){
    //initialise final matrix:
    //size:
    //uint32_t w,h;
    width = uint32_t (pow(Aw,(num_of_iterations+1)));
    height = uint32_t (pow(Ah,(num_of_iterations+1)));

    //matrix:
    gray = mat_u8(width, vec_u8(height,0));
    //initialise top left with inputmatrix A:
    for (int x=0; x<Aw; x++)
        for (int y=0; y<Ah; y++)
            gray[x][y] = A[x][y];

    //initialise vars for size of iteration: the size of the current matrix
    uint32_t w_it, h_it, w_lit, h_lit;
    //initialised with size of input-matrix:
    w_it = Aw;
    h_it = Ah;

    //BEGIN THE ITERATIONS!
    for (int i=0; i<num_of_iterations; i++){
        w_lit = w_it;
        h_lit = h_it;
        w_it *= Ah;
        h_it *= Ah;

        //Iterate through inputmatrix A:
        for (int x=0; x<Aw; x++)
            for (int y=0; y<Ah; y++){
                //Dont change if partmatrix is top-left
                if (x>0 || y>0){
                    /*
                     for every position in A, copy (and invert, if A[x][y]==255)
                     the matrix computed in the last step to new position
                    */
                    for (int xx=0; xx<w_lit; xx++)
                        for (int yy=0; yy<h_lit; yy++)
                            switch(type){
                                case EXP_DISCRETE    : gray[w_lit*x+xx][h_lit*y+yy] = discreteTransform( gray[xx][yy] , A[x][y] ); break;
                                case EXP_SMOOTH_STD  : gray[w_lit*x+xx][h_lit*y+yy] = smoothTransform( gray[xx][yy] , A[x][y] ); break;
                                case EXP_SMOOTH_MID  : gray[w_lit*x+xx][h_lit*y+yy] = smoothMidTransform( gray[xx][yy] , A[x][y] ); break;
                                case EXP_SMOOTH_NOIZ : gray[w_lit*x+xx][h_lit*y+yy] = noizeTransform( gray[xx][yy] , A[x][y] ); break;
                                case EXP_SMOOTH_NOI2 : gray[w_lit*x+xx][h_lit*y+yy] = noiz2Transform( gray[xx][yy] , A[x][y] ); break;
                                case EXP_SMOOTH_NOI3 : gray[w_lit*x+xx][h_lit*y+yy] = noiz3Transform( gray[xx][yy] , A[x][y] ); break;
                            }

                }
            }
    }
    return true;
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
