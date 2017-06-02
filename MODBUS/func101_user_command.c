#include "internal.h"

uint8_t ModbusUserCommandId;
uint8_t ModbusUserCommandData;
uint8_t ModbusUserCommandAdditional1Hi;
uint8_t ModbusUserCommandAdditional1Lo;
uint8_t ModbusUserCommandAdditional2Hi;
uint8_t ModbusUserCommandAdditional2Lo;
uint8_t ModbusUserCommandAdditional3Hi;
uint8_t ModbusUserCommandAdditional3Lo;

uint8_t *ModbusGetUserCommandId(){return &ModbusUserCommandId;}
uint8_t *ModbusGetUserCommandData(){return &ModbusUserCommandData;}
uint16_t ModbusGetUserCommandAdditional1()
{
    return word(ModbusUserCommandAdditional1Hi, ModbusUserCommandAdditional1Lo);
}
uint8_t *ModbusGetUserCommandAdditional1Hi(){return &ModbusUserCommandAdditional1Hi;}
uint8_t *ModbusGetUserCommandAdditional1Lo(){return &ModbusUserCommandAdditional1Lo;}
uint16_t ModbusGetUserCommandAdditional2()
{
    return word(ModbusUserCommandAdditional2Hi, ModbusUserCommandAdditional2Lo);
}
uint8_t *ModbusGetUserCommandAdditional2Hi(){return &ModbusUserCommandAdditional2Hi;}
uint8_t *ModbusGetUserCommandAdditional2Lo(){return &ModbusUserCommandAdditional2Lo;}
uint16_t ModbusGetUserCommandAdditional3()
{
    return word(ModbusUserCommandAdditional3Hi, ModbusUserCommandAdditional3Lo);
}
uint8_t *ModbusGetUserCommandAdditional3Hi(){return &ModbusUserCommandAdditional3Hi;}
uint8_t *ModbusGetUserCommandAdditional3Lo(){return &ModbusUserCommandAdditional3Lo;}


// user commands
int8_t ModbusProcess_FC101()
{
    _u8BufferSize = 10;
    ModbusUserCommandId = _au8Buffer[COM_COM_ID];
    ModbusUserCommandData = _au8Buffer[COM_DATA];
    ModbusUserCommandAdditional1Hi = _au8Buffer[COM_ADD1_HI];
    ModbusUserCommandAdditional1Lo = _au8Buffer[COM_ADD1_LO];
    ModbusUserCommandAdditional2Hi = _au8Buffer[COM_ADD2_HI];
    ModbusUserCommandAdditional2Lo = _au8Buffer[COM_ADD2_LO];
    ModbusUserCommandAdditional3Hi = _au8Buffer[COM_ADD3_HI];
    ModbusUserCommandAdditional3Lo = _au8Buffer[COM_ADD3_LO];
    
    uint8_t u8CopyBufferSize = _u8BufferSize + 2;
    ModbusSendTxBuffer();

    return u8CopyBufferSize;
}
