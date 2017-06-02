#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
//    #include <EEP.h>
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
#include <p18cxxx.h>    /* C18 General Include File */
#endif



#include "internal.h"


enum COM_STATES
{
    COM_IDLE = 0,
    COM_WAITING = 1

};



#define T35  5

uint8_t _u8id; //!< 0=master, 1..247=slave number
uint8_t _u8serno; //!< serial port: 0-Serial, 1..3-Serial1..Serial3
uint8_t _u8txenpin; //!< flow control pin: 0=USB or RS-232 mode, >0=RS-485 mode
uint8_t _u8state;
int8_t _u8lastError;
uint8_t _au8Buffer[MAX_BUFFER];
uint8_t _u8BufferSize;
uint8_t _u8lastRec;
//uint16_t *_holdingRegs;
uint8_t _inputRegsCount, _holdingRegsCount;
uint8_t _discreteInputCount, _coilsCount;
uint16_t _u16InCnt, _u16OutCnt, _u16errCnt;
uint16_t _u16timeOut;
uint32_t _u32time, _u32timeOut;


uint8_t _lastFunction = 0;

uint16_t _lastAddress = 0;
uint16_t _lastCount = 0; // number of coils or registers or file length in bytes in last command 
uint8_t _lastCommand = 0;


void ModbusInit(uint8_t u8id, uint8_t u8serno, uint8_t u8txenpin);
int8_t ModbusGetRxBufferHeader();
int8_t ModbusGetRxBuffer();
uint16_t ModbusCalcCRC(uint8_t u8length);
uint8_t ModbusValidateAnswer();
uint8_t ModbusValidateRequest();
void ModbusGet_FC1();
void ModbusGet_FC3();
void ModbusBuildException(uint8_t u8exception); // build exception message
/* _____PUBLIC FUNCTIONS_____________________________________________________ */


/**
 * @brief
 * Full constructor for a Master/Slave through USB/RS232C/RS485
 * It needs a pin for flow control only for RS485 mode
 *
 * @param u8id   node address 0=master, 1..247=slave
 * @param u8serno  serial port used 0..3
 * @param u8txenpin pin for txen RS-485 (=0 means USB/RS232C mode)
 * @ingroup setup
 * @overload Modbus::Modbus(uint8_t u8id, uint8_t u8serno, uint8_t u8txenpin)
 * @overload Modbus::Modbus()
 */

void Modbus(uint8_t u8serno, uint8_t u8txenpin)
{
    uint8_t tmpModbusId = eeprom_read(EE_MODBUS_ID);
    if(tmpModbusId == 0xff || tmpModbusId == 0) 
        tmpModbusId = DEFAULT_MODBUS_ID;
    
    
#ifdef SERIAL_DEBUG
    DebugPrintStr("Start MODBUS (");
    DebugPrintNumber(tmpModbusId, DEC);
    DebugPrintStr(")\n");
#endif  
    
    ModbusInit(tmpModbusId, u8serno, u8txenpin);
}


/**
 * @brief
 * Initialize class object.
 *
 * Sets up the serial port using specified baud rate.
 * Call once class has been instantiated, typically within setup().
 *
 * @see http://arduino.cc/en/Serial/Begin#.Uy4CJ6aKlHY
 * @param speed   baud rate, in standard increments (300..115200)
 * @param config  data frame settings (data length, parity and stop bits)
 * @ingroup setup
 */
#ifdef ARDUINO

void Modbus::begin(long u32speed)
{

    switch (u8serno)
    {
#if defined(UBRR1H)
        case 1:
            port = &Serial1;
            break;
#endif

#if defined(UBRR2H)
        case 2:
            port = &Serial2;
            break;
#endif

#if defined(UBRR3H)
        case 3:
            port = &Serial3;
            break;
#endif
        case 0:
        default:
            port = &Serial;
            break;
    }

    // port->begin(u32speed, u8config);
    port->begin(u32speed);
    if (u8txenpin > 1)
    { // pin 0 & pin 1 are reserved for RX/TX
        // return RS485 transceiver to transmit mode
        pinMode(u8txenpin, OUTPUT);
        digitalWrite(u8txenpin, LOW);
    }

    port->flush();
    u8lastRec = u8BufferSize = 0;
    u16InCnt = u16OutCnt = u16errCnt = 0;


}
#elif __XCf 

void ModbusBegin()
{
    //PortBegin();
}
#endif
/**
 * @brief
 * Initialize default class object.
 *
 * Sets up the serial port using 19200 baud.
 * Call once class has been instantiated, typically within setup().
 *
 * @overload Modbus::begin(uint16_t u16BaudRate)
 * @ingroup setup
 */
#ifdef ARDUINO

void Modbus::begin()
{
    begin(19200);
}
#endif
/**
 * @brief
 * Method to write a new slave ID address
 *
 * @param 	u8id	new slave address between 1 and 247
 * @ingroup setup
 */
/*
void ModbusSetID( uint8_t u8id_) 
{
  if (( u8id_ != 0) && (u8id_ <= 247)) 
  {
    u8id = u8id_;
  }
}
 */

/**
 * @brief
 * Method to read current slave ID address
 *
 * @return u8id	current slave address between 1 and 247
 * @ingroup setup
 */
/*
uint8_t ModbusGetID()
{
    return _u8id;
}
*/
/**
 * @brief
 * Initialize time-out parameter
 *
 * Call once class has been instantiated, typically within setup().
 * The time-out timer is reset each time that there is a successful communication
 * between Master and Slave. It works for both.
 *
 * @param time-out value (ms)
 * @ingroup setup
 */
/*
void ModbusSetTimeOut(uint16_t u16timeOut)
{
    _u16timeOut = u16timeOut;
}
*/
/**
 * @brief
 * Return communication Watchdog state.
 * It could be usefull to reset outputs if the watchdog is fired.
 *
 * @return TRUE if millis() > u32timeOut
 * @ingroup loop
 */
/*
boolean ModbusGetTimeOutState()
{
    return (millis() > _u32timeOut);
}
*/
/**
 * @brief
 * Get input messages counter value
 * This can be useful to diagnose communication
 *
 * @return input messages counter
 * @ingroup buffer
 */
/*
uint16_t ModbusGetInCnt()
{
    return _u16InCnt;
}
*/
/**
 * @brief
 * Get transmitted messages counter value
 * This can be useful to diagnose communication
 *
 * @return transmitted messages counter
 * @ingroup buffer
 */
/*
uint16_t ModbusGetOutCnt()
{
    return _u16OutCnt;
}
*/
/**
 * @brief
 * Get errors counter value
 * This can be useful to diagnose communication
 *
 * @return errors counter
 * @ingroup buffer
 */
/*
uint16_t ModbusGetErrCnt()
{
    return _u16errCnt;
}
*/
/**
 * Get modbus master state
 *
 * @return = 0 IDLE, = 1 WAITING FOR ANSWER
 * @ingroup buffer
 */
/*
uint8_t ModbusGetState()
{
    return _u8state;
}
*/
/**
 * Get the last error in the protocol processor
 *
 * @returnreturn   NO_REPLY = 255      Time-out
 * @return   EXC_FUNC_CODE = 1   Function code not available
 * @return   EXC_ADDR_RANGE = 2  Address beyond available space for Modbus registers
 * @return   EXC_REGS_QUANT = 3  Coils or registers number beyond the available space
 * @ingroup buffer
 */
/*
uint8_t ModbusGetLastError()
{
    return _u8lastError;
}
 
*/






/**
 * @brief
 * *** Only for Modbus Slave ***
 * This method checks if there is any incoming query
 * Afterwards, it would shoot a validation routine plus a register query
 * Avoid any delay() function !!!!
 * After a successful frame between the Master and the Slave, the time-out timer is reset.
 *
 * @param *regs  register table for communication exchange
 * @param u8size  size of the register table
 * @return 0 if no query, 1..4 if communication error, >4 if correct query processed
 * @ingroup loop
 */

int8_t ModbusPoll(uint8_t *discreteInputs, const uint8_t discreteInputCount, 
                      uint8_t *coils, const uint8_t coilsCount, 
                      uint16_t *inputRegs, const uint8_t inputRegsCount, 
                      uint16_t *holdingRegs, const uint8_t holdingRegsCount)
{
    _lastFunction = MB_FC_NONE;
    //bitClear(_exceptionStatus, MB_EXCEPTION_LAST_COMMAND_STATE);
    //_inputRegs = inputRegs;
    //_holdingRegs = holdingRegs;
    _discreteInputCount = discreteInputCount;
    _coilsCount = coilsCount;
    _inputRegsCount = inputRegsCount;
    _holdingRegsCount = holdingRegsCount;


    // check if there is any incoming frame

    uint8_t u8current = PortAvailable();

    if (u8current == 0) 
        return 0;

    // check T35 after frame end or still no frame end
    if (u8current != _u8lastRec)
    {
        _u8lastRec = u8current;
        _u32time = millis() + T35;
        return 0;
    }
    if (millis() < _u32time)
        return 0;

    _u8lastRec = 0;
    int8_t i8state = ModbusGetRxBufferHeader();
    
//#ifdef SERIAL_DEBUG
//    DebugPrintStr("Readed ");
//    DebugPrintNumber(i8state, DEC);
//    DebugPrintStr(" bytes\n");
//#endif     
    
    _u8lastError = i8state;
    if (i8state < 4) // Minimum request len
    {
        PortClearReadBuffer();
        return i8state;
    }
    // check slave id
    if (_au8Buffer[ ID ] != _u8id)
    {
        PortClearReadBuffer();
        return 0;
    }
    i8state = ModbusGetRxBuffer();
    PortClearReadBuffer();
    _u8lastError = i8state;
    

 
    // validate message: CRC, FCT, address and size
    uint8_t u8exception = ModbusValidateRequest();
    if (u8exception > 0)
    {
        if (u8exception != NO_REPLY)
        {
            ModbusBuildException(u8exception);
            ModbusSendTxBuffer();
        }
        _u8lastError = u8exception;
        return u8exception;
    }

    _u32timeOut = millis() + (uint32_t) _u16timeOut;
    _u8lastError = 0;

    // Before read exception ststus not change value
    if(_au8Buffer[ FUNC ] != MB_FC_READ_EXCEPTION_STATUS)
        ModbusSetExceptionStatusBit(MB_EXCEPTION_LAST_COMMAND_STATE, false);

//#ifdef SERIAL_DEBUG
//    DebugPrintStr("Function ");
//    DebugPrintNumber(_au8Buffer[ FUNC ], DEC);
//    DebugPrintStr("\n");
//#endif      
    // process message
    switch (_au8Buffer[ FUNC ])
    {
        case MB_FC_READ_COILS:
            return ModbusProcess_FC1(coils);
        case MB_FC_READ_DISCRETE_INPUT:
            return ModbusProcess_FC1(discreteInputs);
        case MB_FC_READ_REGISTERS:
            return ModbusProcess_FC3(holdingRegs, holdingRegsCount);
        case MB_FC_READ_INPUT_REGISTER:
            return ModbusProcess_FC3(inputRegs, inputRegsCount);
        case MB_FC_WRITE_COIL:
            return ModbusProcess_FC5(coils);
        case MB_FC_WRITE_REGISTER:
            return ModbusProcess_FC6(holdingRegs, holdingRegsCount);
        case MB_FC_READ_EXCEPTION_STATUS:
            return ModbusProcess_FC7();
        case MB_FC_WRITE_MULTIPLE_COILS:
            return ModbusProcess_FC15(coils);
        case MB_FC_WRITE_MULTIPLE_REGISTERS:
            return ModbusProcess_FC16(holdingRegs, holdingRegsCount);
        case MB_FC_REPORT_SLAVE_ID:
            return ModbusProcess_FC17();
        case MB_FC_READ_FILE_RECORD:
            return ModbusProcess_FC20();
        case MB_FC_WRITE_FILE_RECORD:
            return ModbusProcess_FC21();
        case MB_FC_READ_DEVICE_ID:
            return ModbusProcess_FC43();
        case MB_FC_SYSTEM_COMMAND:
            return ModbusProcess_FC100();
        case MB_FC_USER_COMMAND:
            return ModbusProcess_FC101();
        case MB_FC_READ_DEVICE_STATUS:
            return ModbusProcess_FC102();
    
        default:
            break;
    }
    return i8state;
}

/* _____PRIVATE FUNCTIONS_____________________________________________________ */

void ModbusInit(uint8_t u8id, uint8_t u8serno, uint8_t u8txenpin)
{
    ModbusClearDeviceStatus();
    if(DEVICE_NEED_TIME_SET == true)
        ModbusSetDeviceStatusBit(INPUT_NEED_TIME_SET);
    _u8id = u8id;
    _u8serno = (u8serno > 3) ? 0u : u8serno;
    _u8txenpin = u8txenpin;
    _u16timeOut = 1000;
}













uint8_t *ModbusGetLastCommand(uint16_t *fileNum, uint16_t *address, uint16_t *count, uint8_t *command)
{
    if (fileNum != NULL)
        *fileNum = _lastFileNum;    
    if (address != NULL)
        *address = _lastAddress;
    if (count != NULL)
        *count = _lastCount;
    if(command != NULL)
        *command = _lastCommand;
    return &_lastFunction;
}















/**
 * @brief
 * This method processes function 17
 * Report Slave ID
 *
 * @return u8BufferSize Response to master length
 * @ingroup register
 */
int8_t ModbusProcess_FC17()
{
#ifdef SERIAL_DEBUG
    DebugPrintStr("Function ModbusProcess_FC17:\n");
    //DebugPrintNumber(_au8Buffer[ FUNC ], DEC);
    //DebugPrintStr("\n");
#endif      
    
    _au8Buffer[ 2 ] =  4; // 22 Run Indicator Status 1 Byte + Additional Data 1 Byte

    _u8BufferSize = 3;
    _au8Buffer[_u8BufferSize++] = SLAVE_ID_DEVICE_TYPE;
    _au8Buffer[_u8BufferSize++] = SLAVE_ID_DEVICE_SUB_TYPE;
    _au8Buffer[_u8BufferSize++] = SLAVE_ID_DEVICE_REVISION;
    _au8Buffer[_u8BufferSize++] = SLAVE_ID_DEVICE_NUMBER;
    
    _au8Buffer[_u8BufferSize++] = MODBUS_ON;
    uint8_t u8CopyBufferSize = _u8BufferSize;
    ModbusSendTxBuffer();

    return u8CopyBufferSize;
}











// =========== MASTER ==========================================================
uint16_t *au16regs;

/**
 * �������� ����� ������
 * @param isMaster
 */
void ModbusChangeMode(bool isMaster)
{
    if(isMaster)
    {
        PortClearReadBuffer();
        _u8state = COM_IDLE;
    }
    else
    {
        
    }
}
/**
 * @brief
 * *** Only Modbus Master ***
 * Generate a query to an slave with a modbus_t telegram structure
 * The Master must be in COM_IDLE mode. After it, its state would be COM_WAITING.
 * This method has to be called only in loop() section.
 *
 * @see modbus_t
 * @param modbus_t  modbus telegram structure (id, fct, ...)
 * @ingroup loop
 * @todo finish function 15
 */
int8_t ModbusQuery(modbus_t *telegram )
{
    uint8_t u8regsno, u8bytesno;
    if (_u8id != 0) return -2;
    if (_u8state != COM_IDLE) return -1;

    if ((telegram->u8id == 0) || (telegram->u8id > 247)) 
        return -3;

    au16regs = telegram->au16reg;

    // telegram header
    _au8Buffer[ ID ]         = telegram->u8id;
    _au8Buffer[ FUNC ]       = telegram->u8fct;
    _au8Buffer[ ADD_HI ]     = HIGH_BYTE(telegram->u16RegAdd );
    _au8Buffer[ ADD_LO ]     = LOW_BYTE( telegram->u16RegAdd );

    switch( telegram->u8fct )
    {
    case MB_FC_READ_COILS:
    case MB_FC_READ_DISCRETE_INPUT:
    case MB_FC_READ_REGISTERS:
    case MB_FC_READ_INPUT_REGISTER:
        _au8Buffer[ NB_HI ]      = HIGH_BYTE(telegram->u16CoilsNo );
        _au8Buffer[ NB_LO ]      = LOW_BYTE( telegram->u16CoilsNo );
        _u8BufferSize = 6;
        break;
    case MB_FC_WRITE_COIL:
        _au8Buffer[ NB_HI ]      = ((au16regs[0] > 0) ? 0xff : 0);
        _au8Buffer[ NB_LO ]      = 0;
        _u8BufferSize = 6;
        break;
    case MB_FC_WRITE_REGISTER:
        _au8Buffer[ NB_HI ]      = HIGH_BYTE(au16regs[0]);
        _au8Buffer[ NB_LO ]      = LOW_BYTE(au16regs[0]);
        _u8BufferSize = 6;
        break;
    case MB_FC_WRITE_MULTIPLE_COILS: // TODO: implement "sending coils"
        u8regsno = telegram->u16CoilsNo / 16;
        u8bytesno = u8regsno * 2;
        if ((telegram->u16CoilsNo % 16) != 0)
        {
            u8bytesno++;
            u8regsno++;
        }

        _au8Buffer[ NB_HI ]      = HIGH_BYTE(telegram->u16CoilsNo );
        _au8Buffer[ NB_LO ]      = LOW_BYTE( telegram->u16CoilsNo );
        _au8Buffer[ NB_LO + 1 ]    = u8bytesno;
        _u8BufferSize = 7;

        u8regsno = u8bytesno = 0; // now auxiliary registers
        for (uint16_t i = 0; i < telegram->u16CoilsNo; i++)
        {


        }
        break;

    case MB_FC_WRITE_MULTIPLE_REGISTERS:
        _au8Buffer[ NB_HI ]      = HIGH_BYTE(telegram->u16CoilsNo );
        _au8Buffer[ NB_LO ]      = LOW_BYTE( telegram->u16CoilsNo );
        _au8Buffer[ NB_LO + 1 ]    = (uint8_t) ( telegram->u16CoilsNo * 2 );
        _u8BufferSize = 7;

        for (uint16_t i=0; i< telegram->u16CoilsNo; i++)
        {
            _au8Buffer[ _u8BufferSize ] = HIGH_BYTE( au16regs[ i ] );
            _u8BufferSize++;
            _au8Buffer[ _u8BufferSize ] = LOW_BYTE( au16regs[ i ] );
            _u8BufferSize++;
        }
        break;
    }

    ModbusSendTxBuffer();
    _u8state = COM_WAITING;
    return 0;
}





/**
 * This method processes functions 1 & 2 (for master)
 * This method puts the slave answer into master data buffer
 *
 * @ingroup register
 * TODO: finish its implementation
 */
void ModbusGet_FC1()
{
    uint8_t u8byte, i;
    u8byte = 0;

    //  for (i=0; i< au8Buffer[ 2 ] /2; i++) {
    //    au16regs[ i ] = word(
    //    au8Buffer[ u8byte ],
    //    au8Buffer[ u8byte +1 ]);
    //    u8byte += 2;
    //  }
}

/**
 * This method processes functions 3 & 4 (for master)
 * This method puts the slave answer into master data buffer
 *
 * @ingroup register
 */
void ModbusGet_FC3()
{
    uint8_t u8byte, i;
    u8byte = 3;

    for (i = 0; i < _au8Buffer[ 2 ] / 2; i++)
    {
        au16regs[ i ] = word(
                            _au8Buffer[ u8byte ],
                            _au8Buffer[ u8byte +1 ]);
        u8byte += 2;
    }
}


/**
 * @brief *** Only for Modbus Master ***
 * This method checks if there is any incoming answer if pending.
 * If there is no answer, it would change Master state to COM_IDLE.
 * This method must be called only at loop section.
 * Avoid any delay() function.
 *
 * Any incoming data would be redirected to au16regs pointer,
 * as defined in its modbus_t query telegram.
 *
 * @params	nothing
 * @return errors counter
 * @ingroup loop
 */
int8_t ModbusPollMaster()
{
    _lastFunction = MB_FC_NONE;
    // check if there is any incoming frame
    uint8_t u8current = PortAvailable();
        
        

    if (millis() > _u32time)
    {
        _u8state = COM_IDLE;
        _u8lastError = NO_REPLY;
        _u16errCnt++;
        return 0;
    }

    if (u8current == 0) return 0;

    // check T35 after frame end or still no frame end
    if (u8current != _u8lastRec)
    {
        _u8lastRec = u8current;
        _u32time = millis() + T35;
        return 0;
    }
    if (millis() < _u32time) return 0;

    // transfer Serial buffer frame to auBuffer
    _u8lastRec = 0;
    int8_t i8state = ModbusGetRxBuffer();
    if (i8state < 7)
    {
        _u8state = COM_IDLE;
        _u16errCnt++;
        return i8state;
    }

    // validate message: id, CRC, FCT, exception
    uint8_t u8exception = ModbusValidateAnswer();
    if (u8exception != 0)
    {
        _u8state = COM_IDLE;
        return u8exception;
    }

    // process answer
    switch( _au8Buffer[ FUNC ] )
    {
    case MB_FC_READ_COILS:
    case MB_FC_READ_DISCRETE_INPUT:
        // call get_FC1 to transfer the incoming message to au16regs buffer
        ModbusGet_FC1( );
        break;
    case MB_FC_READ_INPUT_REGISTER:
    case MB_FC_READ_REGISTERS :
        // call get_FC3 to transfer the incoming message to au16regs buffer
        ModbusGet_FC3( );
        break;
    case MB_FC_WRITE_COIL:
    case MB_FC_WRITE_REGISTER :
    case MB_FC_WRITE_MULTIPLE_COILS:
    case MB_FC_WRITE_MULTIPLE_REGISTERS :
        // nothing to do
        break;
    default:
        break;
    }
    _u8state = COM_IDLE;
    return _u8BufferSize;
}