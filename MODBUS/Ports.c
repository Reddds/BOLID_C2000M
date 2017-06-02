#include "internal.h"

// Read first 4 bytes
int8_t ModbusGetRxBufferHeader()
{
    _u8BufferSize = 0;
    for(uint8_t i = 0; i < 4; i++)
    {
        if(!PortAvailable())
            return ERR_EXCEPTION;
        _au8Buffer[ _u8BufferSize ] = PortRead();
        _u8BufferSize++;
    }
    return _u8BufferSize;
}
/**
 * @brief
 * This method moves Serial buffer data to the Modbus au8Buffer.
 *
 * @return buffer size if OK, ERR_BUFF_OVERFLOW if u8BufferSize >= MAX_BUFFER
 * @ingroup buffer
 */
int8_t ModbusGetRxBuffer()
{
    bool bBuffOverflow = false;

    //!!!  if (u8txenpin > 1) 
    //!!!      digitalWrite( u8txenpin, LOW );

    _u8BufferSize = 4;

    while (PortAvailable())
    {
        _au8Buffer[ _u8BufferSize ] = PortRead();
        _u8BufferSize++;
        if (_u8BufferSize >= MAX_BUFFER)
            bBuffOverflow = true;
    }
    _u16InCnt++;
    if (bBuffOverflow)
    {
        _u16errCnt++;
        return ERR_BUFF_OVERFLOW;
    }
    return _u8BufferSize;
}

/**
 * @brief
 * This method transmits au8Buffer to Serial line.
 * Only if u8txenpin != 0, there is a flow handling in order to keep
 * the RS485 transceiver in output state as long as the message is being sent.
 * This is done with UCSRxA register.
 * The CRC is appended to the buffer before starting to send it.
 *
 * @param nothing
 * @return nothing
 * @ingroup buffer
 */
void ModbusSendTxBuffer()
{
    //  uint8_t i = 0;

    // append CRC to message
    uint16_t u16crc = ModbusCalcCRC(_u8BufferSize);
    _au8Buffer[ _u8BufferSize ] = u16crc >> 8;
    _u8BufferSize++;
    _au8Buffer[ _u8BufferSize ] = u16crc & 0x00ff;
    _u8BufferSize++;


    // transfer buffer to serial line
    PortWrite(_au8Buffer, _u8BufferSize);

    // keep RS485 transceiver in transmit mode as long as sending


    //!!!  port->flush();
    _u8BufferSize = 0;

    // set time-out for master
    _u32timeOut = millis() + (unsigned long) _u16timeOut;

    // increase message counter
    _u16OutCnt++;
}
