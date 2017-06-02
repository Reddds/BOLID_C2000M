#include "internal.h"
uint8_t _exceptionStatus = 0;

const unsigned char fctsupported[] = {
    MB_FC_READ_COILS,
    MB_FC_READ_DISCRETE_INPUT,
    MB_FC_READ_REGISTERS,
    MB_FC_READ_INPUT_REGISTER,
    MB_FC_WRITE_COIL,
    MB_FC_WRITE_REGISTER,
    MB_FC_READ_EXCEPTION_STATUS,
    MB_FC_WRITE_MULTIPLE_COILS,
    MB_FC_WRITE_MULTIPLE_REGISTERS,
    MB_FC_REPORT_SLAVE_ID,
    MB_FC_READ_FILE_RECORD,
    MB_FC_WRITE_FILE_RECORD,
    MB_FC_READ_DEVICE_ID,
    
    MB_FC_SYSTEM_COMMAND,
    MB_FC_USER_COMMAND,
    MB_FC_READ_DEVICE_STATUS
};

/**
 * @brief
 * This method validates slave incoming messages
 *
 * @return 0 if OK, EXCEPTION if anything fails
 * @ingroup buffer
 */
uint8_t ModbusValidateRequest()
{
    // check message crc vs calculated crc
    uint16_t u16MsgCRC =
            ((_au8Buffer[_u8BufferSize - 2] << 8)
            | _au8Buffer[_u8BufferSize - 1]); // combine the crc Low & High bytes
    if (ModbusCalcCRC(_u8BufferSize - 2) != u16MsgCRC)
    {
        _u16errCnt++;
        return NO_REPLY;
    }

    // check fct code
    bool isSupported = false;
    for (uint8_t i = 0; i< sizeof ( fctsupported); i++)
    {
        if (fctsupported[i] == _au8Buffer[FUNC])
        {
            isSupported = 1;
            break;
        }
    }
    if (!isSupported)
    {
        _u16errCnt++;
        return EXC_FUNC_CODE;
    }

    // check start address & nb range

    uint8_t res = 0;
    switch (_au8Buffer[ FUNC ])
    {
        case MB_FC_READ_COILS:
            res = CheckFunc1();
            break;
        case MB_FC_READ_DISCRETE_INPUT:
            res = CheckFunc2();
            break;
        case MB_FC_WRITE_MULTIPLE_COILS:
            res = CheckFunc15();
            break;
        case MB_FC_WRITE_COIL:
            res = CheckFunc5();
            break;
        case MB_FC_WRITE_REGISTER: // јдреса с 0!
            res = CheckFunc6();
            break;
        case MB_FC_READ_INPUT_REGISTER: // 4
            res = CheckFunc4();
            break;
        case MB_FC_READ_REGISTERS:
            res = CheckFunc3();
        break;
        case MB_FC_WRITE_MULTIPLE_REGISTERS: // јдреса с 0!
            res = CheckFunc16();
            break;
        case MB_FC_REPORT_SLAVE_ID:
            break;
            // Read eeprom
        case MB_FC_READ_FILE_RECORD:
            res = CheckFunc20();
            break;
            // Write to EEPROM
        case MB_FC_WRITE_FILE_RECORD:
            res = CheckFunc21();  
            break;
        case MB_FC_READ_DEVICE_ID:
            res = CheckFunc43();
            break;
            
        case MB_FC_SYSTEM_COMMAND:
            res = CheckFunc100(); 
            break;
        case MB_FC_USER_COMMAND:   
            break;
        case MB_FC_READ_DEVICE_STATUS:            
            break;
    }
    if(res == 0) // OK, no exception code thrown
    {
        _lastFunction = _au8Buffer[ FUNC ];
        return 0;
    }
    return res; // exception
}

/**
 * @brief
 * This method builds an exception message
 *
 * @ingroup buffer
 */
void ModbusBuildException(uint8_t u8exception)
{
    uint8_t u8func = _au8Buffer[ FUNC ]; // get the original FUNC code

    _au8Buffer[ ID ] = _u8id;
    _au8Buffer[ FUNC ] = u8func + 0x80u;
    _au8Buffer[ 2 ] = u8exception;
    _u8BufferSize = EXCEPTION_SIZE;
}

// 07 (0x07) Read Exception Status (Serial Line only)
int8_t ModbusProcess_FC7()
{
    _au8Buffer[ 2 ] = _exceptionStatus;
    _u8BufferSize = 3;
    uint8_t u8CopyBufferSize = _u8BufferSize;
    ModbusSendTxBuffer();
    return u8CopyBufferSize;
}

void ModbusSetExceptionStatusBit(uint8_t bitNum, bool value)
{
    bitWrite(_exceptionStatus, bitNum, value);
}