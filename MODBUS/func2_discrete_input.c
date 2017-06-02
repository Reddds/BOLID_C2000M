#include "internal.h"
uint16_t u16regs = 0;
uint16_t u16count = 0;

uint8_t CheckFunc2() //Read Discrete Inputs
{
    u16regs = word(_au8Buffer[ ADD_HI ], _au8Buffer[ ADD_LO ]);
    u16count = word(_au8Buffer[ NB_HI ], _au8Buffer[ NB_LO ]);
    if (u16count < 1 || u16count > 0x07D0)
        return EXC_REGS_QUANT;
    if (u16regs + u16count > _discreteInputCount)
        return EXC_ADDR_RANGE;
    return 0;
}
