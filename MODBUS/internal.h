/* 
 * File:   internal.h
 * Author: denis
 *
 * Created on 1 июня 2017 г., 22:43
 */

#ifndef INTERNAL_H
#define	INTERNAL_H

#define T35  5
#define INPUT_TIME_SET 0
#define INPUT_NEED_TIME_SET 1

#include <eeprom_routines.h>
#include "ModbusRtu.h"
#include "../interrupts.h"
#include "../user.h"

#ifdef C2000M
#include "../ParametersController.h"
#endif


#ifdef	__cplusplus
extern "C" {
#endif

    
#define MAX_BUFFER  256	//!< maximum size for the communication buffer in bytes
    
    
enum ERR_LIST
{
    ERR_NOT_MASTER = -1,
    ERR_POLLING = -2,
    ERR_BUFF_OVERFLOW = -3,
    ERR_BAD_CRC = -4,
    ERR_EXCEPTION = -5
};    
    
enum
{
    NO_REPLY = 255,
    EXC_FUNC_CODE = 1,
    EXC_ADDR_RANGE = 2,
    EXC_REGS_QUANT = 3,
    EXC_EXECUTE = 4,
    EXC_NOT_EXP_ID = 10, // В ответ пришёл неожиданный адрес устройства
    EXC_SLAVE_EXC = 11, // Исключение в опрашиваемом устройстве сети
};

/**
 * @enum MESSAGE
 * @brief
 * Indexes to telegram frame positions
 */
enum MESSAGE
{
    ID = 0, //!< ID field
    FUNC, //!< Function code position
    ADD_HI, //!< Address high byte
    ADD_LO, //!< Address low byte
    NB_HI, //!< Number of coils or registers high byte
    NB_LO, //!< Number of coils or registers low byte
    BYTE_CNT //!< byte counter = 6
};

enum
{
    RESPONSE_SIZE = 6,
    EXCEPTION_SIZE = 3,
    CHECKSUM_SIZE = 2
};



enum FILE_MESSAGE
{
    FILE_DATA_LEN = 2, //!< Request data length
    FILE_REF_TYPE, //!< Reference Type
    FILE_NUM_HI, //!< File Number high byte
    FILE_NUM_LO, //!< File Number low byte
    FILE_REC_HI, //!< Record Number high byte
    FILE_REC_LO, //!< Record Number low byte
    FILE_REC_LEN_HI, //!< Record length high byte
    FILE_REC_LEN_LO, //!< Record length low byte
    FILE_FIRST_BYTE
};

enum COMMAND_MESSAGE
{
    COM_ID = 0, //!< ID field
    COM_FUNC, //!< Function code position
    COM_COM_ID, // Command Id
    COM_DATA,
    COM_ADD1_HI,
    COM_ADD1_LO,
    COM_ADD2_HI,
    COM_ADD2_LO,
    COM_ADD3_HI,
    COM_ADD3_LO,
};

extern uint8_t _u8id;
extern int8_t _u8lastError;
extern uint8_t _u8lastRec;
extern uint8_t _au8Buffer[MAX_BUFFER];
extern uint8_t _u8BufferSize;
extern uint16_t _u16InCnt, _u16OutCnt, _u16errCnt;

extern uint32_t _u32time, _u32timeOut;
extern uint16_t _u16timeOut;

extern uint8_t _inputRegsCount, _holdingRegsCount;
extern uint8_t _discreteInputCount, _coilsCount;

extern uint8_t _lastFunction;

extern uint16_t _lastAddress;
extern uint16_t _lastCount;
extern uint8_t _lastCommand;
extern uint16_t _lastFileNum;


uint16_t ModbusCalcCRC(uint8_t u8length);

void ModbusSendTxBuffer();
int8_t ModbusGetRxBufferHeader();
int8_t ModbusGetRxBuffer();

uint8_t ModbusValidateAnswer();


uint8_t CheckFunc1();
uint8_t CheckFunc2();
uint8_t CheckFunc3();
uint8_t CheckFunc4();
uint8_t CheckFunc5();
uint8_t CheckFunc6();
uint8_t CheckFunc15();
uint8_t CheckFunc16();
uint8_t CheckFunc20();
uint8_t CheckFunc21();
uint8_t CheckFunc43();
uint8_t CheckFunc100();

int8_t ModbusProcess_FC1(uint8_t *regs);                    // Read Coils
int8_t ModbusProcess_FC3(uint16_t *regs, uint8_t u8size);   // Read Holding Registers
int8_t ModbusProcess_FC5(uint8_t *regs);                    // Write Single Coil &regs 
int8_t ModbusProcess_FC6(uint16_t *regs, uint8_t u8size);   // Write Single Register
int8_t ModbusProcess_FC7();                                 // Read Exception Status
int8_t ModbusProcess_FC15(uint8_t *regs);                  // Write Multiple Coils&regs 
int8_t ModbusProcess_FC16(uint16_t *regs, uint8_t u8size);  // Write Multiple registers
int8_t ModbusProcess_FC17();    // Report Slave ID
int8_t ModbusProcess_FC20();    // Read EEPROM
int8_t ModbusProcess_FC21();    // Writing to EEPROM
int8_t ModbusProcess_FC43();    // 43 / 14 (0x2B / 0x0E) Read Device Identification
int8_t ModbusProcess_FC100();   // system commands
int8_t ModbusProcess_FC101();   // user commands
int8_t ModbusProcess_FC102();   // Get device state

void ModbusClearDeviceStatus();
void ModbusSetDeviceStatusBit(uint8_t bitIndex);

#ifdef	__cplusplus
}
#endif

#endif	/* INTERNAL_H */

