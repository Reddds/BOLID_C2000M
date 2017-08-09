#include "internal.h"

#define ERROR_COUNT_FOR_BAN 5 // Количество ошибко чтения, чтобы бан перешёл на новый уровень

uint16_t *au16regs;
uint8_t _masterState;
uint8_t _isTimeSyncRequest;

bool _isMaster;

uint8_t _curControllerIdInEe;

void SetTimeFromResponse(uint8_t *hour, uint8_t *min, uint8_t *day, uint8_t *sec, uint8_t *year, uint8_t *mon);
/**
 * Get modbus master state
 *
 * @return = 0 IDLE, = 1 WAITING FOR ANSWER
 * @ingroup buffer
 */
uint8_t ModbusGetState()
{
    return _masterState;
}

bool ModbusIsMasterMode()
{
    return _isMaster;
}
/**
 * Изменяет режим работы
 * @param isMaster
 */
void ModbusChangeMode(bool isMaster)
{
    PortClearReadBuffer();
    if(isMaster)
    {
        //_u8id = 0;
        _masterState = COM_IDLE;  
        SetWorkState(true, true);
    }
    else
    {
        SetWorkState(true, false);
    }
    _isMaster = isMaster;
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
    //if (_u8id != 0) 
    //    return -2;
    if (_masterState != COM_IDLE) 
        return -1;

    if ((telegram->u8id == 0) || (telegram->u8id > 247)) 
        return -3;

    _curControllerIdInEe = telegram->curControllerIdInEe;
    au16regs = telegram->au16reg;

    _isTimeSyncRequest = telegram->isTimeSync;
    
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
    _masterState = COM_WAITING;
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

#if HOLDING_REGS_SIMPLE_COUNT + INPUT_REGS_SIMPLE_COUNT > CTRL_REG_BUF_COUNT || CTRL_REG_BUF_COUNT < 16
#error "Number of holding and input regs greater then buffer len. Or buffwr len less then 16!"
#endif

#define COIL_BUF_POS 3
#define DISCRETE_BUF_POS 5
#define REG_BUF_POS 7
/**
 * This method processes function 4 (for master)
 * This method puts the slave answer into master data buffer
 *  0 reg - coils
 *  1 reg - discrete
 *  2+ (HOLDING_REGS_SIMPLE_COUNT) regs - holding
 *  n+ (INPUT_REGS_SIMPLE_COUNT) regs - inputs 
 * 
 * @ingroup register
 */
void ModbusGet_FC4()
{
#ifdef SERIAL_DEBUG
    //DebugPrintValue("Second controller rate", GetControllerRate(1));
    DebugPrintStrLn("+============================================+");
    DebugPrintStrLn("|           ModbusGet_FC4 start!             |");
    DebugPrintStrLn("+--------------------------------------------+");
#endif

    uint8_t u8byte, i;
    uint16_t tmpReg;
    u8byte = 3;
    
    RegInfoTag regInfo[CTRL_REG_BUF_COUNT];

    // Катушки
    uint8_t cnt = GetCtrlRegCount(_curControllerIdInEe, MRT_COIL);
    if(cnt > 0)
    {
#ifdef SERIAL_DEBUG
        DebugPrintValueTbl("Coils count", cnt);
#endif        
        tmpReg = word(_au8Buffer[COIL_BUF_POS], _au8Buffer[COIL_BUF_POS + 1]);
        cnt = FillCtrlRegInfo(_curControllerIdInEe, MRT_COIL, regInfo);
        // Проверяем, изменились ли значения параметров
        for(i = 0; i < cnt; i++)
        {
            bool newVal = bitRead(tmpReg, regInfo[i].rgId);
            if(GetDiscreteParameterValue(regInfo[i].paramId) != newVal)
                SetDiscreteParameterValue(regInfo[i].paramId, newVal);
        }
    }
    
    // Дискретные
    cnt = GetCtrlRegCount(_curControllerIdInEe, MRT_DISCRETE);
    if(cnt > 0)
    {
#ifdef SERIAL_DEBUG
        DebugPrintValueTbl("Discrete count", cnt);
#endif        
        tmpReg = word(_au8Buffer[DISCRETE_BUF_POS], _au8Buffer[DISCRETE_BUF_POS + 1]);
        cnt = FillCtrlRegInfo(_curControllerIdInEe, MRT_DISCRETE, regInfo);
        // Проверяем, изменились ли значения параметров
        for(i = 0; i < cnt; i++)
        {
            bool newVal = bitRead(tmpReg, regInfo[i].rgId);
            if(GetDiscreteParameterValue(regInfo[i].paramId) != newVal)
                SetDiscreteParameterValue(regInfo[i].paramId, newVal);
        }
    }
    
    // Регистры хранения
    cnt = GetCtrlRegCount(_curControllerIdInEe, MRT_HOLDING);
    if(cnt > 0)
    {
#ifdef SERIAL_DEBUG
        DebugPrintValueTbl("Holding count", cnt);
#endif        
        cnt = FillCtrlRegInfo(_curControllerIdInEe, MRT_HOLDING, regInfo);
        // Проверяем, изменились ли значения параметров
        for(i = 0; i < cnt; i++)
        {
            uint16_t newVal = word(_au8Buffer[REG_BUF_POS + regInfo[i].rgId * 2], 
                                   _au8Buffer[REG_BUF_POS + regInfo[i].rgId * 2 + 1]);
            if(GetParameterValue(regInfo[i].paramId) != newVal)
                SetParameterValue(regInfo[i].paramId, newVal);
        }
    }
 
    // Регистры только для чтения
    cnt = GetCtrlRegCount(_curControllerIdInEe, MRT_INPUT);
    if(cnt > 0)
    {
#ifdef SERIAL_DEBUG
        DebugPrintValueTbl("Input regs count", cnt);
#endif        
        cnt = FillCtrlRegInfo(_curControllerIdInEe, MRT_INPUT, regInfo);
#ifdef SERIAL_DEBUG
        DebugPrintValueTbl("Reginfo filled count", cnt);
#endif      
        // Установка времени, если надо
        if(_isTimeSyncRequest)
        {
            SetTimeFromResponse(_au8Buffer + (REG_BUF_POS + HOLDING_REGS_SIMPLE_COUNT * 2 + GetTimeInfo.RegHourMin * 2),
                                _au8Buffer + (REG_BUF_POS + HOLDING_REGS_SIMPLE_COUNT * 2 + (GetTimeInfo.RegHourMin) * 2 + 1),
                                _au8Buffer + (REG_BUF_POS + HOLDING_REGS_SIMPLE_COUNT * 2 + GetTimeInfo.RegDaySec * 2),
                                _au8Buffer + (REG_BUF_POS + HOLDING_REGS_SIMPLE_COUNT * 2 + (GetTimeInfo.RegDaySec) * 2 + 1),
                                _au8Buffer + (REG_BUF_POS + HOLDING_REGS_SIMPLE_COUNT * 2 + GetTimeInfo.RegYearMon * 2),
                                _au8Buffer + (REG_BUF_POS + HOLDING_REGS_SIMPLE_COUNT * 2 + (GetTimeInfo.RegYearMon) * 2 + 1));
        }
        
        
        // Проверяем, изменились ли значения параметров
        for(i = 0; i < cnt; i++)
        {
            uint8_t pos = REG_BUF_POS + HOLDING_REGS_SIMPLE_COUNT * 2 + regInfo[i].rgId * 2;
            uint16_t newVal = word(_au8Buffer[pos], 
                                   _au8Buffer[pos + 1]);
#ifdef SERIAL_DEBUG
            DebugPrintValueTbl("rgId", regInfo[i].rgId);
            DebugPrintValueTbl("Calculated rgId", pos);
            DebugPrintValueTbl("paramId", regInfo[i].paramId);
            DebugPrintValueTbl("newVal", newVal);    
#endif        
            
            if(GetParameterValue(regInfo[i].paramId) != newVal)
                SetParameterValue(regInfo[i].paramId, newVal);
        }
    }

#ifdef SERIAL_DEBUG
    //DebugPrintValue("Second controller rate", GetControllerRate(1));
    DebugPrintStrLn("+============================================+");
#endif
    
    
}


void SetTimeFromResponse(uint8_t *hour, uint8_t *min, uint8_t *day, uint8_t *sec, uint8_t *year, uint8_t *mon)
{
#ifdef SERIAL_DEBUG
    DebugPrintStrLn("+==========  Setting time.  =================+");
    DebugPrintValueTbl("Hour", *hour);
    DebugPrintValueTbl("Minute", *min);
    DebugPrintValueTbl("Day", *day);
    DebugPrintValueTbl("Second", *sec);
    DebugPrintValueTbl("Year", *year);
    DebugPrintValueTbl("Month", *mon);

    DebugPrintStrLn("+============================================+");
#endif            
    SetHourMin(hour, min, sec);
            //----------------
    struct tm newTime;
    newTime.tm_year = *year + 100; // since 1900
    newTime.tm_mon  = *mon;
    newTime.tm_mday = *day;
    newTime.tm_hour = *hour;
    newTime.tm_min  = *min;
    newTime.tm_sec  = *sec;
    time_t newRawTime = mktime(&newTime);
    SetTime(&newRawTime);
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
        
        

    if (millis() > _u32timeOut)
    {
        _masterState = COM_IDLE;
        _u8lastError = NO_REPLY;
        _u16errCnt++;
#ifdef SERIAL_DEBUG
        uint8_t caddr = GetControllerAddress(_curControllerIdInEe);
        DebugPrintValue("TimeOut! for controllerId", caddr);
#endif          
        // Будем банить
        ControllersNextRequest[_curControllerIdInEe].continousErrors++;
#ifdef SERIAL_DEBUG
        DebugPrintValue("continousErrors", ControllersNextRequest[_curControllerIdInEe].continousErrors);
#endif          
        if(ControllersNextRequest[_curControllerIdInEe].continousErrors > ERROR_COUNT_FOR_BAN)
        {
            ControllersNextRequest[_curControllerIdInEe].continousErrors = 0;
            ControllersNextRequest[_curControllerIdInEe].banned++;
#ifdef SERIAL_DEBUG
            DebugPrintValue("Controller ban level", ControllersNextRequest[_curControllerIdInEe].banned);
#endif          
            
        }
        return 0;
    }
//#ifdef SERIAL_DEBUG
//    DebugPrintValue("PortAvailable", u8current);
//    //DebugPrintStr("ModbusGet_FC4 start!\n");
//#endif  
    if (u8current == 0) 
        return 0;

    // check T35 after frame end or still no frame end
    // TODO переделать в ожидание вычисленной длины или ошибки
    if (u8current != _u8lastRec)
    {
        _u8lastRec = u8current;
        _u32time = millis() + T35;
        return 0;
    }
    
    if (millis() < _u32time) 
        return 0;

    uint8_t oldId = _au8Buffer[ID];
    uint8_t oldFunc = _au8Buffer[FUNC];
    
    int8_t i8state = ModbusGetRxBufferHeader();
    _u8lastError = i8state;
    if (i8state < 4) // Minimum request len
    {
        _masterState = COM_IDLE;
        PortClearReadBuffer();
        _u16errCnt++;
        return i8state;
    }
    
    if(_au8Buffer[ID] != oldId)
    {
        _masterState = COM_IDLE;
        PortClearReadBuffer();
        _u16errCnt++;
#ifdef SERIAL_DEBUG
    DebugPrintValue("Exception! Eror id!", _au8Buffer[ID]);
#endif        
        return EXC_NOT_EXP_ID;
    }
    
    if(_au8Buffer[FUNC] != oldFunc)
    {
        _masterState = COM_IDLE;
        PortClearReadBuffer();
        _u16errCnt++;
#ifdef SERIAL_DEBUG
    DebugPrintValue("Exception! Eror function!", _au8Buffer[FUNC]);
#endif 
        return EXC_SLAVE_EXC;
    }
    // transfer Serial buffer frame to auBuffer
    _u8lastRec = 0;
    int8_t i8state = ModbusGetRxBuffer();
    if (i8state < 7)
    {
        _masterState = COM_IDLE;
        PortClearReadBuffer();
        _u16errCnt++;
        return i8state;
    }

    // validate message: id, CRC, FCT, exception
    uint8_t u8exception = ModbusValidateAnswer();
    if (u8exception != 0)
    {
        _masterState = COM_IDLE;
#ifdef SERIAL_DEBUG
    DebugPrintValue("Master validation error!", u8exception);
#endif 
        return u8exception;
    }
    
    _u32timeOut = millis() + _u16timeOut;
    _u8lastError = 0;
    // Разбаниваем, если нужно
    if(ControllersNextRequest[_curControllerIdInEe].banned > CB_NONE 
            || ControllersNextRequest[_curControllerIdInEe].continousErrors > 0)
    {
        ControllersNextRequest[_curControllerIdInEe].continousErrors = 0;
        ControllersNextRequest[_curControllerIdInEe].banned = CB_NONE;
#ifdef SERIAL_DEBUG
        DebugPrintValue("Controller unbanned!", _curControllerIdInEe);
#endif         
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
        ModbusGet_FC4();
        break;
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
    _masterState = COM_IDLE;
    return _u8BufferSize;
}
