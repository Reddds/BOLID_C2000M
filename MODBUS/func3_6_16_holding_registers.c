#include "internal.h"

uint16_t u16regs = 0;
uint16_t u16count = 0;
uint8_t u8regs;

uint8_t CheckFunc3() //Read Holding Registers
{
#ifdef C2000M

    if(_au8Buffer[ ADD_HI ] == 0xFF)
    {
        if(_au8Buffer[ NB_HI ] != 0)
            return EXC_ADDR_RANGE;

        u16regs = _au8Buffer[ ADD_LO ] + _au8Buffer[ NB_LO ] - 1;
        if(u16regs >= ParamCount)
            return EXC_ADDR_RANGE;
        return 0;
    }
#else
    u16regs = word(_au8Buffer[ ADD_HI ], _au8Buffer[ ADD_LO ]);
    u16regs += word(_au8Buffer[ NB_HI ], _au8Buffer[ NB_LO ]);
#endif



    u8regs = (uint8_t) u16regs;
    if (u8regs > _holdingRegsCount)
        return EXC_ADDR_RANGE;
    return 0;
}

uint8_t CheckFunc6() //Write Single Register
{
    u16regs = word(_au8Buffer[ ADD_HI ], _au8Buffer[ ADD_LO ]);
#ifdef C2000M
    if(_au8Buffer[ ADD_HI ] == 0xFF)
    {
        if(_au8Buffer[ ADD_LO ] >= ParamCount)
            return EXC_ADDR_RANGE;
        return 0;
    }
#endif
    u8regs = (uint8_t) u16regs;
    if (u8regs > _holdingRegsCount) 
        return EXC_ADDR_RANGE;
    return 0;
}

uint8_t CheckFunc16() // Write Multiple registers
{
#ifdef C2000M

    if(_au8Buffer[ ADD_HI ] == 0xFF)
    {
        if(_au8Buffer[ NB_HI ] != 0)
            return EXC_ADDR_RANGE;

        u16regs = _au8Buffer[ ADD_LO ] + _au8Buffer[ NB_LO ] - 1;
        if(u16regs >= ParamCount)
            return EXC_ADDR_RANGE;
        return 0;
    }
#else
    u16regs = word(_au8Buffer[ ADD_HI ], _au8Buffer[ ADD_LO ]);
    u16regs += word(_au8Buffer[ NB_HI ], _au8Buffer[ NB_LO ]);
#endif


            
    u8regs = (uint8_t) u16regs;
    if (u8regs > _holdingRegsCount)
        return EXC_ADDR_RANGE;
    return 0;
}


/**
 * @brief
 * This method processes functions 3 & 4
 * This method reads a word array and transfers it to the master
 *
 * @return u8BufferSize Response to master length
 * @ingroup register
 */
int8_t ModbusProcess_FC3(uint16_t *regs, uint8_t u8size)
{
#ifdef C2000M
    bool isWriteParams = _au8Buffer[ ADD_HI ] == 0xFFu;
    uint8_t startAddress = _au8Buffer[ ADD_LO ];
    
#endif
    uint8_t u8StartAdd = word(_au8Buffer[ ADD_HI ], _au8Buffer[ ADD_LO ]);
    _lastAddress = u8StartAdd;
    uint16_t u16regsno = word(_au8Buffer[ NB_HI ], _au8Buffer[ NB_LO ]);
    _lastCount = u16regsno;
    uint8_t u8CopyBufferSize;
    uint16_t i;

    _au8Buffer[ 2 ] = u16regsno * 2;
    _u8BufferSize = 3;

#ifdef C2000M
    
    if(isWriteParams)
    {
        for (i = startAddress; i < startAddress + u16regsno; i++)
        {
            uint16_t par = GetParameterValue(i);
            _au8Buffer[ _u8BufferSize ] = HIGH_BYTE(par);
            _u8BufferSize++;
            _au8Buffer[ _u8BufferSize ] = LOW_BYTE(par);
            _u8BufferSize++;
        }
    }
    else
#endif  
    for (i = u8StartAdd; i < u8StartAdd + u16regsno; i++)
    {
        _au8Buffer[ _u8BufferSize ] = HIGH_BYTE(regs[i]);
        _u8BufferSize++;
        _au8Buffer[ _u8BufferSize ] = LOW_BYTE(regs[i]);
        _u8BufferSize++;
    }
  
    
    u8CopyBufferSize = _u8BufferSize + 2u;
    ModbusSendTxBuffer();

    return u8CopyBufferSize;
}


/**
 * @brief
 * This method processes function 6
 * This method writes a value assigned by the master to a single word
 *
 * @return u8BufferSize Response to master length
 * @ingroup register
 */
int8_t ModbusProcess_FC6(uint16_t *regs, uint8_t u8size)
{
    uint16_t u16add = word(_au8Buffer[ ADD_HI ], _au8Buffer[ ADD_LO ]);
    _lastAddress = u16add;
    _lastCount = 1;
    uint8_t u8CopyBufferSize;
    uint16_t u16val = word(_au8Buffer[ NB_HI ], _au8Buffer[ NB_LO ]);

#ifdef C2000M
    if(_au8Buffer[ ADD_HI ] == 0xFF) // Это значение параметра для вывода на экран
    {// ID параметра берётся из младшего байта
        SetParameterValue(_au8Buffer[ ADD_LO ], u16val);
        
//        uint16_t par = GetParameter(_au8Buffer[ ADD_LO ]);
//        _u8BufferSize = RESPONSE_SIZE;
//        
//        _au8Buffer[ _u8BufferSize ] = HIGH_BYTE(par);//!!!! для теста!!!
//        _u8BufferSize++;
//        _au8Buffer[ _u8BufferSize ] = LOW_BYTE(par);//!!!! для теста!!!
//        _u8BufferSize++;
//        _au8Buffer[ _u8BufferSize ] = _au8Buffer[ ADD_LO ];
//        _u8BufferSize++;
    }
    else
#endif
    regs[ u16add ] = u16val;    





    // keep the same header
    _u8BufferSize = RESPONSE_SIZE;
    

    u8CopyBufferSize = _u8BufferSize + 2u;
    ModbusSendTxBuffer();

    return u8CopyBufferSize;
}

/**
 * @brief
 * This method processes function 16
 * This method writes a word array assigned by the master
 *
 * @return u8BufferSize Response to master length
 * @ingroup register
 */
int8_t ModbusProcess_FC16(uint16_t *regs, uint8_t u8size)
{
    //  uint8_t u8func = au8Buffer[ FUNC ];  // get the original FUNC code
    uint16_t u16StartAdd = _au8Buffer[ ADD_HI ] << 8 | _au8Buffer[ ADD_LO ];
    _lastAddress = u16StartAdd;
    int8_t u8regsno = _au8Buffer[ NB_HI ] << 8 | _au8Buffer[ NB_LO ];
    _lastCount = u8regsno;
    uint8_t u8CopyBufferSize;
    uint8_t i;
    uint16_t temp;

    // build header
    _au8Buffer[ NB_HI ] = 0;
    _au8Buffer[ NB_LO ] = u8regsno;
    _u8BufferSize = RESPONSE_SIZE;

    // write registers
    for (i = 0; i < u8regsno && (u16StartAdd + i) < u8size; i++) // 
    {
        temp = word(
                _au8Buffer[ (BYTE_CNT + 1u) + i << 1 ],
                _au8Buffer[ (BYTE_CNT + 2u) + i << 1 ]);

        regs[ u16StartAdd + i ] = temp;
    }
    u8CopyBufferSize = _u8BufferSize + 2;
    ModbusSendTxBuffer();

    return u8CopyBufferSize;
}