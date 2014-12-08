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

mat_u8 MatrixBuilder::get_predefined_Matrix(int id)
{
	mat_u8 ret, tl, smooth;
	switch(id)
	{
		case 1:
			// size: 9x9
			
			tl = mat_u8(5,vec_u8(5,0));
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
			
			smooth = mat_u8(5,vec_u8(5,99));
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
			
			smoothen_Matrix(&tl, smooth);
			
			ret = symmetric_Matrix_Expansion(tl);
		break;
		
		case 2:
			// X-star
			// fade out to center
			// size: 5x5
			
			tl = mat_u8(3,vec_u8(3,0));
			for (int i=0;i<3;i++)
				tl[i][i]=255;
			
			smooth = mat_u8(3,vec_u8(3,0));
			for (int i=0; i<3; i++)
				for (int j=0; j<3; j++)
					smooth[i][j] = 100 - (5*(i+j));
			
			smoothen_Matrix(&tl, smooth);
			
			ret = symmetric_Matrix_Expansion(tl);
		break;
		
		case 3:
			// + -star
			// with additional corner-points
			// fade out to center
			
			// size: 5x5
			
			tl = mat_u8(3,vec_u8(3,0));
			for (int i=0;i<3;i++)
			{
				tl[i][2] = 255;
				tl[2][i] = 255;
			}
			tl[0][0] = 255;
			
			smooth = mat_u8(3,vec_u8(3,0));
			for (int i=0; i<3; i++)
				for (int j=0; j<3; j++)
					smooth[i][j] = 100 - (5*(i+j));
			
			smoothen_Matrix(&tl, smooth);
			
			ret = symmetric_Matrix_Expansion(tl);
		break;
		
		default:
			//std-walsh
			ret = mat_u8(2,vec_u8(2,0));
			ret[1][1]=255;
	}
	
	return ret;
}
