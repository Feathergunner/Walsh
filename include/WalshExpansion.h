#include <cstdint>
#include <vector>
#include "typedefs.h"
#include "WalshExpTypes.cpp"

class WalshExpansion{
private:
    uint8_t invert(uint8_t val);

    /*
     these transformation-function transform a 8-bit-int- grayvalue "base" dependent on another 8-bit-int-grayvalue "factor"
     main idea of most of these transformations is:
        - grayvalues have a "orientation" towards white(>127) or black (<127)
        - factor < 127 => orientation of base inverted
        - factor > 127 => orientation of base stayes as-is
        - independent of orientation, base gets scaled/varied by value of factor
    */
    uint8_t discreteTransform(uint8_t base, uint8_t factor);
    uint8_t smoothTransform(uint8_t base, uint8_t factor);
    uint8_t smoothMidTransform(uint8_t base, uint8_t factor);
    uint8_t noizeTransform(uint8_t base, uint8_t factor);
    uint8_t noiz2Transform(uint8_t base, uint8_t factor);
    uint8_t noiz3Transform(uint8_t base, uint8_t factor);

    uint32_t width;
    uint32_t height;

public:
    //the result:
    mat_u8 gray;

    bool generalWalshExpansion(uint8_t Aw, uint8_t Ah, mat_u8 A, uint8_t num_of_iterations, WalshExpType type);
    //bool smoothWalshExpansion(uint8_t Aw, uint8_t Ah, mat_u8 A, uint8_t num_of_iterations);

    // print matrix "gray" to console output
    bool printgray();

};
