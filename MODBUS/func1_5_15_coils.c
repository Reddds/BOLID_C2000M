#include "internal.h"

uint16_t u16regs;
uint16_t u16count;
uint8_t u8regs;

uint8_t CheckFunc1() // Read Coils
{
    u16regs = word(_au8Buffer[ ADD_HI ], _au8Buffer[ ADD_LO ]);
    u16count = word(_au8Buffer[ NB_HI ], _au8Buffer[ NB_LO ]);
    if (u16count < 1 || u16count > 0x07D0)
        return EXC_REGS_QUANT;
    if (u16regs + u16count > _coilsCount)
        return EXC_ADDR_RANGE;
    return 0;
}

uint8_t CheckFunc5() // Write Single Coil
{
    u16regs = word(_au8Buffer[ ADD_HI ], _au8Buffer[ ADD_LO ]);
    u8regs = _au8Buffer[ NB_HI ];
    if (u8regs != 0x00 && u8regs != 0xFF)
        return EXC_REGS_QUANT;
    if (u16regs > _coilsCount)
        return EXC_ADDR_RANGE;  
    return 0;    
}

uint8_t CheckFunc15() // Write Multiple Coils
{
    u16regs = word(_au8Buffer[ ADD_HI ], _au8Buffer[ ADD_LO ]);
    u16count = word(_au8Buffer[ NB_HI ], _au8Buffer[ NB_LO ]);
    if (u16count < 1 || u16count > 0x07D0)
        return EXC_REGS_QUANT;
    if (u16regs + u16count > _coilsCount)
        return EXC_ADDR_RANGE;
    return 0;    
}


/**
 * @brief
 * This method processes functions 1 & 2
 * This method reads a bit array and transfers it to the master
 *
 * @return u8BufferSize Response to master length
 * @ingroup discrete
 */
int8_t ModbusProcess_FC1(uint8_t *regs)
{
    uint8_t u8currentRegister;
    uint8_t u8currentBit, u8bytesno, u8bitsno;
    uint8_t u8CopyBufferSize;
    uint8_t u8currentCoil, u8coil;

    // get the first and last coil from the message
    uint16_t u16StartCoil = word(_au8Buffer[ ADD_HI ], _au8Buffer[ ADD_LO ]);
    _lastAddress = u16StartCoil;
    uint16_t u16Coilno = word(_au8Buffer[ NB_HI ], _au8Buffer[ NB_LO ]);
    _lastCount = u16Coilno;
    // put the number of bytes in the outcoming message
    u8bytesno = (uint8_t) (u16Coilno >> 3); // /8
    if (u16Coilno % 8 != 0)
        u8bytesno++;
    _au8Buffer[ ADD_HI ] = u8bytesno;
    _u8BufferSize = ADD_LO;

    // read each coil from the register map and put its value inside the outcoming message
    u8bitsno = 0;

    for (u8currentCoil = 0; u8currentCoil < u16Coilno; u8currentCoil++)
    {
        u8coil = u16StartCoil + u8currentCoil;
        u8currentRegister = (uint8_t) (u8coil >> 3); // /8
        u8currentBit = ((uint8_t) u8coil & 0x07u);

        bitWrite(
                _au8Buffer[ _u8BufferSize ],
                u8bitsno,
                bitRead(regs[u8currentRegister], u8currentBit));
        u8bitsno++;

        if (u8bitsno > 7)
        {
            u8bitsno = 0;
            _u8BufferSize++;
        }
    }

    // send outcoming message
    if (u16Coilno % 8 != 0)
        _u8BufferSize++;
    u8CopyBufferSize = _u8BufferSize + 2u;
    ModbusSendTxBuffer();
    return u8CopyBufferSize;
}


/**
 * @brief
 * This method processes function 5
 * This method writes a value assigned by the master to a single bit
 *
 * @return u8BufferSize Response to master length
 * @ingroup discrete
 */
int8_t ModbusProcess_FC5(uint8_t *regs)
{
    uint8_t u8currentRegister;
    uint8_t u8currentBit;
    uint8_t u8CopyBufferSize;
    uint16_t u16coil = word(_au8Buffer[ ADD_HI ], _au8Buffer[ ADD_LO ]);
    _lastAddress = u16coil;
    _lastCount = 1;
    // point to the register and its bit
    u8currentRegister = (uint8_t) (u16coil >> 3); // / 8
    u8currentBit = (uint8_t) (u16coil & 0x07);

    // write to coil
    bitWrite(
            regs[u8currentRegister],
            u8currentBit,
            _au8Buffer[ NB_HI ] == 0xff);


    // send answer to master
    _u8BufferSize = 6;
    u8CopyBufferSize = _u8BufferSize + 2u;
    ModbusSendTxBuffer();

    return u8CopyBufferSize;
}

/**
 * @brief
 * This method processes function 15 Write Multiple Coils
 * This method writes a bit array assigned by the master
 *
 * @return u8BufferSize Response to master length
 * @ingroup discrete
 */
int8_t ModbusProcess_FC15(uint8_t *regs)
{
    uint8_t u8currentRegister;
    uint8_t u8currentBit, u8frameByte, u8bitsno;
    uint8_t u8CopyBufferSize;
    uint8_t u8currentCoil, u8coil;
    bool bTemp;

    // get the first and last coil from the message
    uint16_t u16StartCoil = word(_au8Buffer[ ADD_HI ], _au8Buffer[ ADD_LO ]);
    _lastAddress = u16StartCoil;
    uint16_t u16Coilno = word(_au8Buffer[ NB_HI ], _au8Buffer[ NB_LO ]);
    _lastCount = u16Coilno;

    // read each coil from the register map and put its value inside the outcoming message
    u8bitsno = 0;
    u8frameByte = 7;
    for (u8currentCoil = 0; u8currentCoil < u16Coilno; u8currentCoil++)
    {

        u8coil = u16StartCoil + u8currentCoil;
        u8currentRegister = (uint8_t) (u8coil >> 3); // /8
        u8currentBit = ((uint8_t) u8coil & 0x07u);

        bTemp = bitRead(
                _au8Buffer[ u8frameByte ],
                u8bitsno);

        bitWrite(
                regs[u8currentRegister],
                u8currentBit,
                bTemp);

        u8bitsno++;

        if (u8bitsno > 7)
        {
            u8bitsno = 0;
            u8frameByte++;
        }
    }

    // send outcoming message
    // it's just a copy of the incomping frame until 6th byte
    _u8BufferSize = 6;
    u8CopyBufferSize = _u8BufferSize + 2u;
    ModbusSendTxBuffer();
    return u8CopyBufferSize;
}