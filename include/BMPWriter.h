#ifndef BMPWriter_h
#define BMPWriter_h

#include <string>
#include <cstdint>
#include <stdio.h>
#include <stdlib.h>

#include "typedefs.h"


class BMPWriter{
    public:
    /*
        method to create an uint8_t img-array with
        - width w
        - height h
        and from
        - three arrays r, g, b that holds the colorvalues for red, green, blue

        writes this to a file named filename, note that the string filename has to end with .bmp
		
		methods adapted from
		http://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries

    */
    static void write_col(int w, int h, mat_u8 red, mat_u8 green, mat_u8 blue, const char* filename);

    /*
        method constructs three matrices red, green, blue
        such that the rgb-values resemble the grayvalues of the parameter-matrix grayvals
    */
    static void write_sw(int w, int h, mat_u8 grayvals, const char* filename);

};

#endif