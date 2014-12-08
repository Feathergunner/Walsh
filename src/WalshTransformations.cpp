#include "../include/WalshTransformations.h"

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
uint16_t WalshTransformations::smoothTransform(uint16_t base, uint16_t factor){
    return (base * factor)/127;
}


/*
 like smooth transform, but computes midvalue between base- and factor- grayvalue
*/
uint16_t WalshTransformations::smoothMidTransform(uint16_t base, uint16_t factor){
	return (base + factor)/2;
}

/*
 a purposly buggy transform that creates a strong noize-effect by uint8-overflow
*/
uint16_t WalshTransformations::noizeTransform(uint16_t base, uint16_t factor){
	return base*factor;
}

/*
 aaaaand another one
 aim is to create a noize-effect by changing the grayvalues to constants within certain intervals
*/
uint16_t WalshTransformations::noiz2Transform(uint16_t base, uint16_t factor){
	uint16_t ret;

	ret = (base * factor)/128;
	if (ret > 28 && ret < 36) ret = 125;
	if (ret > 92 && ret < 100) ret = 125;

	return ret;
}

/*
 aaaaand another one
*/
uint16_t WalshTransformations::noiz3Transform(uint16_t base, uint16_t factor){
	uint16_t ret;
	ret = (base*factor)/128;
	return ret;
}

