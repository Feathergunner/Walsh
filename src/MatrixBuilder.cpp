#include "../include/MatrixBuilder.h"

mat_u8 MatrixBuilder::symmetric_Matrix_Expansion(mat_u8 topleft, bool evenwidth, bool evenheight)
{
	int width_tl, height_tl,
		width_ret, height_ret;
	width_tl = topleft.size();
	height_tl = topleft[0].size();
		
	width_ret = 2*width_tl;
	height_ret = 2*height_tl;
	if (!evenwidth)
		width_ret -=1;
	if (!evenheight)
		height_ret -=1;
		
	mat_u8 ret = mat_u8(width_ret,vec_u8(height_ret,0));
	
	for (int i=0; i<width_tl; i++){
		for (int j=0; j<height_tl; j++){
			ret[i][j] = topleft[i][j];
			ret[width_ret-i-1][j] = topleft[i][j];
			ret[i][height_ret-j-1] = topleft[i][j];
			ret[width_ret-i-1][height_ret-j-1] = topleft[i][j];
		}
	}
		
	return ret;
}

void MatrixBuilder::smoothen_Matrix(mat_u8 *matrix, mat_u8 smoothfactor)
{
	for (int i=0; i<(*matrix).size(); i++)
	{
		for (int j=0; j<(*matrix)[0].size(); j++)
		{
			uint16_t f = (smoothfactor[i][j]*127)/100;
			if ((*matrix)[i][j] > 127)
				(*matrix)[i][j] = (uint8_t)(128+WalshTransformations::smoothTransform(((*matrix)[i][j]-128),f));
			else
				(*matrix)[i][j] = (uint8_t)(128-WalshTransformations::smoothTransform(128-(*matrix)[i][j],f));
		}
	}
}

void MatrixBuilder::print_Matrix(mat_u8 matrix)
{
	for (int i=0; i<matrix.size(); i++)
	{
		for (int j=0; j<matrix[0].size(); j++)
			std::cout << (int)matrix[i][j] << " ";
		std::cout << "\n";
	}
	std::cout << "\n";
	return;
}