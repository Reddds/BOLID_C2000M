#include "internal.h"
#include "../i2c/i2c.h"

#define FILE_MAX_SIZE 128

uint16_t _lastFileNum = 0;

uint8_t CheckFunc20() // MB_FC_READ_FILE_RECORD
{
    uint8_t bytesCount = _au8Buffer[ FILE_DATA_LEN ];
    if(bytesCount < 0x07 || bytesCount > 0xF5)
        return EXC_REGS_QUANT;

    uint8_t offset = 0;
    uint8_t reqCount = 0;
    uint8_t resultLen = 0;
    while(offset < bytesCount)
    {
        if (_au8Buffer[offset + FILE_REF_TYPE ] != 6u)
            return EXC_ADDR_RANGE;
        // File #1 - EEPROM на чипе
        // File 2.. - внешний EEPROM
        uint16_t fileNo = word(_au8Buffer[ FILE_NUM_HI ], _au8Buffer[ FILE_NUM_LO ]);

        unsigned long startAddrBytes = word(_au8Buffer[offset + FILE_REC_HI ], _au8Buffer[offset + FILE_REC_LO ]) << 1;
        unsigned long recLenBytes = word(_au8Buffer[offset + FILE_REC_LEN_HI ], _au8Buffer[offset + FILE_REC_LEN_LO ]) << 1;
        
        if(fileNo == 1)
        {
            if (startAddrBytes + recLenBytes >= _EEPROMSIZE)
                return EXC_ADDR_RANGE;
        }
        else if(fileNo > 1)
        {
            if(recLenBytes > FILE_MAX_SIZE)
                return EXC_ADDR_RANGE;
            if ((fileNo - 2) * FILE_MAX_SIZE + startAddrBytes + recLenBytes > EXT_MEM_CHIP_SIZE * 2)
                return EXC_ADDR_RANGE;

        }
        else
            return EXC_ADDR_RANGE;
        
        if(resultLen + recLenBytes + 2 > MAX_BUFFER - 3)
            return EXC_ADDR_RANGE;
        resultLen += recLenBytes + 2;
        offset += 7;
        reqCount++;
        // only to 5 records
        if(reqCount > 5)
            return EXC_ADDR_RANGE;
    }
    return 0;
}


uint8_t CheckFunc21() // MB_FC_WRITE_FILE_RECORD
{
    if (_au8Buffer[ FILE_REF_TYPE ] != 6)
        return EXC_ADDR_RANGE;

    unsigned long startAddrBytes = word(_au8Buffer[ FILE_REC_HI ], _au8Buffer[ FILE_REC_LO ]) << 1;
    unsigned long recLenBytes = word(_au8Buffer[ FILE_REC_LEN_HI ], _au8Buffer[ FILE_REC_LEN_LO ]) << 1;
    // File #1 - EEPROM на чипе
    // File 2.. - внешний EEPROM
    uint16_t fileNo = word(_au8Buffer[ FILE_NUM_HI ], _au8Buffer[ FILE_NUM_LO ]);
    if(fileNo == 1)
    {
        if (startAddrBytes + recLenBytes >= _EEPROMSIZE)
            return EXC_ADDR_RANGE;
    }
    else if(fileNo > 1)
    {
        if(recLenBytes > FILE_MAX_SIZE)
            return EXC_ADDR_RANGE;
        if ((fileNo - 2) * FILE_MAX_SIZE + startAddrBytes + recLenBytes > EXT_MEM_CHIP_SIZE * 2)
            return EXC_ADDR_RANGE;

    }
    else
        return EXC_ADDR_RANGE;
    
    return 0;
}

/**
 * @brief
 * This method processes function 20
 * This method read a word array from EEPROM 
 *
 * File No - номер страницы по 128 байт каждая
 * Record No - позиция внутри страницы 0..64
 * 
 * Чтение первой страницы внешней памяти
 * [addr] 20 07 06 00 02 00 00 00 64
 * 
 * @return u8BufferSize Response to master length
 * @ingroup register
 */
int8_t ModbusProcess_FC20()
{
    //uint8_t u8func = au8Buffer[ FUNC ];  // get the original FUNC code

    uint8_t requestDataLen = _au8Buffer[ FILE_DATA_LEN ];
    // File #1 - EEPROM на чипе
    // File 2..1026 - внешний EEPROM
    _lastFileNum = word(_au8Buffer[ FILE_NUM_HI ], _au8Buffer[ FILE_NUM_LO ]);
    uint8_t offset = 0;

    
    uint8_t startAddrBytes[5];
    uint8_t recLenBytes[5];
    uint8_t reqCount = 0;
    while(offset < requestDataLen)
    {
        startAddrBytes[reqCount] = (_au8Buffer[offset + FILE_REC_LO ]) << 1;
        recLenBytes[reqCount] = (_au8Buffer[offset + FILE_REC_LEN_LO ]) << 1;
        reqCount++;
        offset += 7;
    }
    
    offset = FILE_DATA_LEN + 1;
    _au8Buffer[ FILE_DATA_LEN ] = 0;
    _lastAddress = 0xff;
    _lastCount = 0;
    for(uint8_t r = 0; r < reqCount; r++)
    {
        _au8Buffer[offset++] = recLenBytes[r] + 1;
        _au8Buffer[offset++] = 6;
        if(startAddrBytes[r] < _lastAddress)
            _lastAddress = startAddrBytes[r];
        
        if(_lastFileNum == 1) // Из внутреннего EEPROM
        {
            for(uint8_t i = 0; i < recLenBytes[r]; i++)
            {
                _au8Buffer[offset++] = eeprom_read(startAddrBytes[r] + i);//_EEREG_EEPROM_READ
            }
        }
        else if(_lastFileNum > 1) // Из внешнего EEPROM
        {
            //uint8_t chipAddress = (fileNo - 2) < EXT_MEM_CHIP_PAGES ? EXT_MEM_CHIP_0 : EXT_MEM_CHIP_1;
            
            EESequentialRead(EXT_MEM_COMMAND, (_lastFileNum - 2) * PAGE_SIZE + startAddrBytes[r], &(_au8Buffer[offset]), recLenBytes[r]);
            offset += recLenBytes[r];
        }
        if(startAddrBytes[r] + recLenBytes[r] > _lastCount)
            _lastCount = startAddrBytes[r] + recLenBytes[r];
    }
    _au8Buffer[ FILE_DATA_LEN ] = offset - 3;// += recLenBytes[r] + 2;
    //        _EEREG_EEPROM_READ

    
    uint8_t u8CopyBufferSize;
    uint8_t i;
    //  uint16_t temp;

    // build header
    //au8Buffer[ NB_HI ]   = 0;
    //au8Buffer[ NB_LO ]   = u8regsno;
    _u8BufferSize = _au8Buffer[ FILE_DATA_LEN ] + 3;

    u8CopyBufferSize = _u8BufferSize; // +2;
    ModbusSendTxBuffer();

    return u8CopyBufferSize;
}

/**
 * @brief
 * This method processes function 21
 * This method writes a word array to EEPROM assigned by the master
 * 
 * 
 * [addr] 21 09 06 00 01 00 01 00 01 50 50
 *
 * @return u8BufferSize Response to master length
 * @ingroup register
 */
int8_t ModbusProcess_FC21()
{
    //uint8_t u8func = au8Buffer[ FUNC ];  // get the original FUNC code

    uint8_t requestDataLen = _au8Buffer[ FILE_DATA_LEN ];
    // File #1 - EEPROM на чипе
    // File 2..1026 - внешний EEPROM
    _lastFileNum = word(_au8Buffer[ FILE_NUM_HI ], _au8Buffer[ FILE_NUM_LO ]);
    uint16_t startAddrsBytes = word(_au8Buffer[ FILE_REC_HI ], _au8Buffer[ FILE_REC_LO ]) << 1;
    _lastAddress = startAddrsBytes;
    uint16_t recLenBytes = word(_au8Buffer[ FILE_REC_LEN_HI ], _au8Buffer[ FILE_REC_LEN_LO ]) << 1;
    _lastCount = recLenBytes;
    uint8_t u8CopyBufferSize;
    uint8_t i;
    //  uint16_t temp;

    // build header
    //au8Buffer[ NB_HI ]   = 0;
    //au8Buffer[ NB_LO ]   = u8regsno;
    _u8BufferSize = requestDataLen + 1;


    if(_lastFileNum == 1)
    {
        // write internsl EEPROM
        for (i = 0; i < recLenBytes; i++)
        {
            eeprom_write(startAddrsBytes + i, _au8Buffer[ FILE_FIRST_BYTE + i ]);
        }
        // wait for write end
        while(EECON1bits.WR)
            continue;
    }
    else if(_lastFileNum > 1) // write external EEPROM
    {
        WP_LATCH = 0; // Снимаем защиту от записи
        __delay_ms(5);
        EEPageWrite(EXT_MEM_COMMAND, (_lastFileNum - 2) * PAGE_SIZE + startAddrsBytes, &(_au8Buffer[ FILE_FIRST_BYTE ]), recLenBytes);
        WP_LATCH = 1;
        __delay_ms(5);
    }
    u8CopyBufferSize = _u8BufferSize + 2; // +2;
    ModbusSendTxBuffer();

    return u8CopyBufferSize;
}