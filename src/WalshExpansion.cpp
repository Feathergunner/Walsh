#include "../include/WalshExpansion.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

//simple method to invert 8-bit-grayvalues:
uint8_t invert(uint8_t val){
    return 255-val;
}

/*
    WalshExpansion for discrete Matrix A
    - all the values from A are ZERO or NON-ZERO(i.e. 1)
    - inverts 0 to 1 and 1 to 0

    Expanded Matrix is saved in classvar gray
*/
bool WalshExpansion::discreteWalshExpansion(uint8_t Aw, uint8_t Ah, mat_u8 A, uint8_t num_of_iterations){
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
                    if (A[x][y]==0){
                        for (int xx=0; xx<w_lit; xx++)
                            for (int yy=0; yy<h_lit; yy++){
                                gray[w_lit*x+xx][h_lit*y+yy]=gray[xx][yy];
                                //printf("current pos: x=%u, y=%u\n",w_lit*x+xx,h_lit*y+yy);
                            }
                    }else{
                        for (int xx=0; xx<w_lit; xx++)
                            for (int yy=0; yy<h_lit; yy++){
                                gray[w_lit*x+xx][h_lit*y+yy]=invert(gray[xx][yy]);
                                //printf("current pos: x=%u, y=%u\n",w_lit*x+xx,h_lit*y+yy);
                            }
                    }
                }
            }
    }
    return true;
}

/*
    To Do:
    a smooth version of the WalshExpansion that respects grayvalues
*/
bool WalshExpansion::smoothWalshExpansion(uint8_t Aw, uint8_t Ah, mat_u8 A, uint8_t num_of_iterations){

    return false;
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
