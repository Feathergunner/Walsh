#include <cstdint>
#include <vector>
#include "typedefs.h"
#include "WalshExpTypes.cpp"

class WalshExpansion{
private:
    uint8_t invert(uint8_t val);

    uint8_t discreteTransform(uint8_t base, uint8_t factor);
    uint8_t smoothTransform(uint8_t base, uint8_t factor);
    uint8_t smoothMidTransform(uint8_t base, uint8_t factor);
    uint8_t noizeTransform(uint8_t base, uint8_t factor);

    uint32_t width;
    uint32_t height;

public:
    //the result:
    mat_u8 gray;

    bool generalWalshExpansion(uint8_t Aw, uint8_t Ah, mat_u8 A, uint8_t num_of_iterations, WalshExpType type);
    //bool smoothWalshExpansion(uint8_t Aw, uint8_t Ah, mat_u8 A, uint8_t num_of_iterations);

    bool printgray();

};
