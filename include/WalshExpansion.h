#include <cstdint>
#include <vector>
#include "typedefs.h"

class WalshExpansion{
    uint32_t width;
    uint32_t height;

    public:
    //the result:
    mat_u8 gray;

    bool discreteWalshExpansion(uint8_t Aw, uint8_t Ah, mat_u8 A, uint8_t num_of_iterations);
    bool smoothWalshExpansion(uint8_t Aw, uint8_t Ah, mat_u8 A, uint8_t num_of_iterations);

    bool printgray();

};
