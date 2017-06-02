#include "internal.h"

uint8_t _deviceStatus; // 0- Time set, 1 - need time set and sync

int8_t ModbusProcess_FC102()
{
    _au8Buffer[FUNC + 1] = _deviceStatus;
    _u8BufferSize = 3;
    uint8_t u8CopyBufferSize = _u8BufferSize + 2;
    ModbusSendTxBuffer();

    return u8CopyBufferSize;
}

void ModbusClearDeviceStatus()
{
    _deviceStatus = 0;
}

void ModbusSetDeviceStatusBit(uint8_t bitIndex)
{
    bitSet(_deviceStatus, bitIndex);
}