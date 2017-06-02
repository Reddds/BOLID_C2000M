#include "internal.h"

enum MEI_MESSAGE
{
    MEI_ID = 0, //!< ID field
    MEI_FUNC, //!< Function code position
    MEI_TYPE, //!< MEI Type
    MEI_READ_DEV_ID, //!< Read Dev Id code
    MEI_OBJ_ID // Object Id
};


uint8_t CheckFunc43()
{
    if(_au8Buffer[ MEI_TYPE ] != 0x0E)
        return EXC_FUNC_CODE;
    uint8_t readDevId = _au8Buffer[ MEI_READ_DEV_ID ];
    if(readDevId != 0x01 && readDevId != 0x02 && readDevId != 0x04)
        return EXC_REGS_QUANT;
    if(readDevId == 0x04 && (_au8Buffer[ MEI_OBJ_ID ] > 0x06 && _au8Buffer[ MEI_OBJ_ID ] != 0x80))
        return EXC_ADDR_RANGE;
    return 0;
}

void CopyStringToBuffer(uint8_t objId, const char *src, uint8_t len)
{
    len--;// not copy endong zero
    _au8Buffer[_u8BufferSize++] = objId;
    _au8Buffer[_u8BufferSize++] = len;
    for(uint8_t i = 0; i < len; i++, _u8BufferSize++)
        _au8Buffer[_u8BufferSize] = src[i];
}

int8_t ModbusProcess_FC43()
{
    uint8_t devIdCode = _au8Buffer[ 3 ];
    /*
     * The parameter " Read Device ID code " allows to define four access types :
        01: request to get the basic device identification (stream access)
        02: request to get the regular device identification (stream access)
        03: request to get the extended device identification (stream access)
        04: request to get one specific identification object (individual access)
     */
    uint8_t objId = _au8Buffer[ 4 ];
    /*
     Identification conformity level of the device and type of supported access
        0x01: basic identification (stream access only)
        0x02: regular identification (stream access only)
        0x03: extended identification (stream access only)
        0x81: basic identification (stream access and individual access)
        0x82: regular identification (stream access and individual access)
        0x83: extended identification(stream access and individual
        access)
     */
    /*
     
     Objects:
     * 0 - VENDOR_NAME
     * 1 - PRODUCT_CODE
     * 2 - MAJOR_MINOR_REVISION
     * 3 - VENDOR_URL
     * 4 - PRODUCT_NAME
     * 5 - MODEL_NAME
     * 6 - USER_APPLICATION_NAME
     * 
     * 0x80 - Информация о EEPROM
     * 
     
     
     */
    _au8Buffer[ 5 ] = 0x00; // More Follows
    _au8Buffer[ 6 ] = 0x00; //Next Object Id
    
    _u8BufferSize = 8;
    switch(devIdCode)
    {
        case 0x01: // request to get the basic device identification (stream access)
            _au8Buffer[ 4 ] = 0x81; // Conformity level
            _au8Buffer[ 7 ] = 3; //Number of objects
            CopyStringToBuffer(0x00, VENDOR_NAME, sizeof(VENDOR_NAME));
            CopyStringToBuffer(0x01, PRODUCT_CODE, sizeof(PRODUCT_CODE));
            CopyStringToBuffer(0x02, MAJOR_MINOR_REVISION, sizeof(MAJOR_MINOR_REVISION));
            break;
        case 0x02: // request to get the regular device identification (stream access)
            _au8Buffer[ 4 ] = 0x82; // Conformity level
            _au8Buffer[ 7 ] = 4; //Number of objects
            CopyStringToBuffer(0x03, VENDOR_URL, sizeof(VENDOR_URL));
            CopyStringToBuffer(0x04, PRODUCT_NAME, sizeof(PRODUCT_NAME));
            CopyStringToBuffer(0x05, MODEL_NAME, sizeof(MODEL_NAME));
            CopyStringToBuffer(0x06, USER_APPLICATION_NAME, sizeof(USER_APPLICATION_NAME));
            break;
        case 0x04:  //request to get one specific identification object (individual access)
            _au8Buffer[ 7 ] = 1;
            switch(objId)
            {
                case 0x00:
                    _au8Buffer[ 4 ] = 0x81; // Conformity level
                    CopyStringToBuffer(objId, VENDOR_NAME, sizeof(VENDOR_NAME));
                    break;
                case 0x01:    
                    _au8Buffer[ 4 ] = 0x81; // Conformity level
                    CopyStringToBuffer(objId, PRODUCT_CODE, sizeof(PRODUCT_CODE));
                    break;
                case 0x02:    
                    _au8Buffer[ 4 ] = 0x81; // Conformity level
                    CopyStringToBuffer(objId, MAJOR_MINOR_REVISION, sizeof(MAJOR_MINOR_REVISION));
                    break;
                case 0x03:    
                    _au8Buffer[ 4 ] = 0x82; // Conformity level
                    CopyStringToBuffer(objId, VENDOR_URL, sizeof(VENDOR_URL));
                    break;
                case 0x04:    
                    _au8Buffer[ 4 ] = 0x82; // Conformity level
                    CopyStringToBuffer(objId, PRODUCT_NAME, sizeof(PRODUCT_NAME));
                    break;
                case 0x05:    
                    _au8Buffer[ 4 ] = 0x82; // Conformity level
                    CopyStringToBuffer(objId, MODEL_NAME, sizeof(MODEL_NAME));
                    break;
                case 0x06:    
                    _au8Buffer[ 4 ] = 0x82; // Conformity level
                    CopyStringToBuffer(objId, USER_APPLICATION_NAME, sizeof(USER_APPLICATION_NAME));
                    break;
                    
                    
                case 0x80:
                    _au8Buffer[ 4 ] = 0x83; //??????? Conformity level
                    CopyStringToBuffer(objId, EepromInfoDesc, sizeof(EepromInfoDesc));
                    break;
                    
            }
            break;
    }
    uint8_t u8CopyBufferSize = _u8BufferSize;
    ModbusSendTxBuffer();

    return u8CopyBufferSize;    
}