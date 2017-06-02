#include "internal.h"

uint8_t CheckFunc100()
{
    if(_au8Buffer[COM_COM_ID] != MB_COMMAND_RESET 
        && _au8Buffer[COM_COM_ID] != MB_COMMAND_SET_ADDRESS 
        && _au8Buffer[COM_COM_ID] != MB_COMMAND_SET_TIME)
    return EXC_REGS_QUANT;
    return 0;
}


// System commands
int8_t ModbusProcess_FC100()
{
    _u8BufferSize = 10;
    _lastCommand = _au8Buffer[COM_COM_ID];
    switch(_lastCommand)
    {
        case MB_COMMAND_RESET:
            Reset();
            break;
        case MB_COMMAND_SET_ADDRESS:
            _u8id = _au8Buffer[COM_DATA];
            eeprom_write(EE_MODBUS_ID, _u8id);
            while(EECON1bits.WR)
                continue;
            ModbusSetExceptionStatusBit(MB_EXCEPTION_LAST_COMMAND_STATE, true);
            break;  
        case MB_COMMAND_SET_TIME:
            SetHourMin(&(_au8Buffer[COM_ADD1_HI]), &(_au8Buffer[COM_ADD1_LO]), &(_au8Buffer[COM_ADD2_LO]));
            
            //----------------
            struct tm newTime;
            newTime.tm_year = _au8Buffer[COM_ADD3_HI] + 100; // since 1900
            newTime.tm_mon  = _au8Buffer[COM_ADD3_LO];
            newTime.tm_mday = _au8Buffer[COM_ADD2_HI];
            newTime.tm_hour = _au8Buffer[COM_ADD1_HI];
            newTime.tm_min  = _au8Buffer[COM_ADD1_LO];
            newTime.tm_sec  = _au8Buffer[COM_ADD2_LO];
            time_t newRawTime = mktime(&newTime);
            SetTime(&newRawTime);
            //----------------
            ModbusSetDeviceStatusBit(INPUT_TIME_SET);
            ModbusSetExceptionStatusBit(MB_EXCEPTION_LAST_COMMAND_STATE, true);
            break;
    }
    uint8_t u8CopyBufferSize = _u8BufferSize + 2;
    ModbusSendTxBuffer();

    return u8CopyBufferSize;
}