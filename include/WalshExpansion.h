#ifndef WalshExpansion_h
#define WalshExpansion_h

#include <cstdint>
#include <vector>
#include <math.h>
//#include <stdlib.h>
#include <stdio.h>

#include "typedefs.h"
#include "WalshExpTypes.h"
#include "WalshTransformations.h"

class WalshExpansion{
private:
  uint8_t invert(uint8_t val);

	void computeIteration(uint32_t w_it, uint32_t h_it, uint32_t w_lit, uint32_t h_lit, WalshExpType type);
	uint8_t discreteTransform(uint8_t base, uint8_t factor);
	uint8_t Transform(uint8_t base, uint8_t factor, uint16_t(*func)(uint16_t, uint16_t));

	// size of resultmatrix:
  uint32_t width;
  uint32_t height;
  
  // start-matrix:
  mat_u8 startMatrix;
  uint32_t aw, ah;
  
  // init instance for Walshexpansion:
  void init(mat_u8 a);

public:
  //the result:
  mat_u8 gray;
  

  bool generalWalshExpansion(mat_u8 a, uint8_t num_of_iterations, WalshExpType type);

  // print matrix "gray" to console output
  bool printgray();

};

#endif
