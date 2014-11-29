#include <string>
#include <cstdint>
#include <stdio.h>
#include <stdlib.h>

#include "../include/typedefs.h"


class BMPWriter{
    /*
     methods adapted from
     http://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries
    */
    public:

    /*
        method to create an uint8_t img-array with
        - width w
        - height h
        and from
        - three arrays r, g, b that holds the colorvalues for red, green, blue

        writes this to a file named filename, note that the string filename has to end with .bmp

    */
    void write_col(int w, int h, mat_u8 red, mat_u8 green, mat_u8 blue, const char* filename);

    /*
        method constructs three matrices red, green, blue
        such that the rgb-values resemble the grayvalues of the parameter-matrix grayvals
    */
    void write_sw(int w, int h, mat_u8 grayvals, const char* filename);

};
