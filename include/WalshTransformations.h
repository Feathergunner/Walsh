#ifndef WalshTransformations_h
#define WalshTransformations_h

#include <cstdint>
#include "typedefs.h"

class WalshTransformations{
public:
	/*
   these transformation-function transform a 8-bit-int- grayvalue "base" dependent on another 8-bit-int-grayvalue "factor"
   main idea of most of these transformations is:
   - grayvalues have a "orientation" towards white(>127) or black (<127)
   - factor < 127 => orientation of base inverted
   - factor > 127 => orientation of base stayes as-is
   - independent of orientation, base gets scaled/varied by value of factor
  */
  static uint16_t smoothTransform(uint16_t base, uint16_t factor);
  static uint16_t smoothMidTransform(uint16_t base, uint16_t factor);
  static uint16_t noizeTransform(uint16_t base, uint16_t factor);
  static uint16_t noiz2Transform(uint16_t base, uint16_t factor);
  static uint16_t noiz3Transform(uint16_t base, uint16_t factor);
};

#endif
