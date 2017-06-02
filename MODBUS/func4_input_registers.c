#include "internal.h"

uint16_t u16regs = 0;
uint16_t u16count = 0;
uint8_t u8regs;

uint8_t CheckFunc4() //Read Input Registers
{
    u16regs = word(_au8Buffer[ ADD_HI ], _au8Buffer[ ADD_LO ]);
    u16regs += word(_au8Buffer[ NB_HI ], _au8Buffer[ NB_LO ]);
    u8regs = (uint8_t) u16regs;
    if (u8regs > _inputRegsCount)
        return EXC_ADDR_RANGE;
    return 0;
}