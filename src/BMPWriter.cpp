#include "../include/BMPWriter.h"

void BMPWriter::write_col(int w, int h, mat_u8 red, mat_u8 green, mat_u8 blue, const char* filename){
	//Init:
	int x,y;
	FILE *f;
	uint8_t *img = new uint8_t[3*w*h];
	int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int

	/*
		write Data from r,g,b to img:
	*/
	for(int i=0; i<w; i++)
	{
		for(int j=0; j<h; j++)
		{
			x=i; y=(h-1)-j;
			img[(x+y*w)*3+2] = red[i][j];
			img[(x+y*w)*3+1] = green[i][j];
			img[(x+y*w)*3+0] = blue[i][j];
		}
	}

	/*
		Create Header and write file:
	*/
	uint8_t bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	uint8_t bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
	uint8_t bmppad[3] = {0,0,0};

	bmpfileheader[ 2] = (uint8_t)(filesize    );
	bmpfileheader[ 3] = (uint8_t)(filesize>> 8);
	bmpfileheader[ 4] = (uint8_t)(filesize>>16);
	bmpfileheader[ 5] = (uint8_t)(filesize>>24);

	bmpinfoheader[ 4] = (uint8_t)(       w    );
	bmpinfoheader[ 5] = (uint8_t)(       w>> 8);
	bmpinfoheader[ 7] = (uint8_t)(       w>>24);
	bmpinfoheader[ 6] = (uint8_t)(       w>>16);
	bmpinfoheader[ 8] = (uint8_t)(       h    );
	bmpinfoheader[ 9] = (uint8_t)(       h>> 8);
	bmpinfoheader[10] = (uint8_t)(       h>>16);
	bmpinfoheader[11] = (uint8_t)(       h>>24);

	remove(filename);
	f = fopen(filename,"wb");
	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);
	for(int i=0; i<h; i++)
	{
		//fwrite(img+(w*(h-i-1)*3),3,w,f);
		fwrite(img+w*i*3,3,w,f);
		fwrite(bmppad,1,(4-(w*3)%4)%4,f);
	}
	fclose(f);
}

/*
	method constructs three matrices red, green, blue
	such that the rgb-values resemble the grayvalues of the parameter-matrix grayvals
*/
void BMPWriter::write_sw(int w, int h, mat_u8 grayvals, const char* filename){
	mat_u8 red = grayvals;
	mat_u8 green = grayvals;
	mat_u8 blue = grayvals;
	write_col(w, h, red, green, blue, filename);
}

