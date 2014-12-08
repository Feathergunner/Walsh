#ifndef MatrixBuilder_h
#define MatrixBuilder_h

#include <iostream>

#include "typedefs.h"
#include "WalshTransformations.h"

class MatrixBuilder
{
public:
	// constructs a center-symmetric matrix by taking 'topleft' four times and mirroring apropriately
	// evenwidth and evenheight can configure if the result matrix should have even oder odd size
	// in the second case, the last line/row of topleft will only apear once in the result
	// example:
	// topleft =	[ 1 0
	//				  0 1 ]
	// evenwidht, evenheight = true
	// the result will be:
	// [ 1 0 0 1
	//   0 1 1 0
	//   0 1 1 0
	//   1 0 0 1 ]
	static mat_u8 symmetric_Matrix_Expansion(mat_u8 topleft, bool evenwidth=false, bool evenheight=false);
	
	// for debugging etc: simple method that prints matrix to std-output
	static void print_Matrix(mat_u8 matrix);
	
	// smoothens every entry of 'matrix' by factors given by 'smoothfactor' towards 127
	// examples:
	// 		255 * 100 -> 127
	//		255 * 0 -> 255
	//		255 * 50 -> 192
	//		10 * 50 ~> 96
	static void smoothen_Matrix(mat_u8 *matrix, mat_u8 smoothfactor);

	// returns hardcodes mat_u8 by id. if no matrix for given id, returns std-walsh-matrix
	static mat_u8 get_predefined_Matrix(int id);
};

#endif