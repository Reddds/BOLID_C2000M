/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif

#include <eeprom_routines.h>

#include "i2c/i2c.h"
//#include <delays.h>
#include "LCD/xlcd.h"

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "interrupts.h"
#include "buttons.h"
#include "MODBUS/ModbusRtu.h"
#include "ParametersController.h"

#include "Sections/SectionIdle.h"
#include "Sections/SectionRooms.h"
#include "Sections/SectionSettings.h"






#include "SettingsController.h"


#define RESET_TIMEOUT_MS 5000

//**** Delay functions for xlcd.h **************************************************************************

void DelayFor18TCY(void) // dalay for 20 TCY
{                             
    __delay_us(18);
}
  
void DelayPORXLCD()// delay for 15 ms
{                                  
    __delay_ms(15);
}
 
void DelayXLCD()// delay for 5 ms
{                                     
    __delay_ms(5);
}


/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/


enum 
{
    SECTION_IDLE,
    SECTION_ROOMS,
    SECTION_SETTINGS    
};
void ShowTimeScreen();
void io_poll();

uint8_t _currentSection;





// ���������    
// ������� ����������� �� ��������� ������
//uint16_t _mSecondsToScreenSave = 30000; // �� ������

int8_t initRes = 0;

  
void LoadParamsFromEeprom()
{
    DisplayClear();
    initRes = InitParameters();//!!!!
    if(initRes != 0)
    {        
        LED_FAILURE_ON;
        DisplayPrintInt(initRes, DEC);
        DisplaySetCursorPos(0, 1);
        DisplayPrintStr("������ EEPROM!");
    }
    else
    {
        LED_FAILURE_OFF;
        _currentSection = SECTION_IDLE;
        IdleStart();
    }
}

uint16_t _heartBeat = 500;
void SetHeartBeat(uint8_t value)
{
    _heartBeat = value * 10;
}

/*
 * �������� ��������� - �������� �� ������� ������� 
 * 
 * 
 * ARM - ��� (1 - �������� ��������) / (ID ���������) | ()
 * 
 * 
 * 
 * 
 * 
 ����������� �� ��������� ������
 * ________________
 * ��:  � -12�� 67%|         
 * ���:   +22�� 35%|
 * ~~~~~~~~~~~~~~~~
 * 
 * ������� �����:
 * 
 * ������ �������� ������
 * 
 * ������� (���, ���) / ��� / ��������
 * 
 * ����: 
 *  0 - ������ (0 ��� - �����)
 *  1 - ��������
 * 
 * 
 * ������:
 * <,> - ������� � /���� �� ��������/���������
 * 
 * 
 * 
 * ����� �������:
 * ________________
 * ����� �������   |         
 * 1 �������       |
 * ~~~~~~~~~~~~~~~~ 
 * <,> - ����� �������
 * 
 * 
 * ���� �� �������:
 * ________________
 * � ����. ������� |         
 * ��������: 440�� |
 * ~~~~~~~~~~~~~~~~
 * <,> - ����� ���������
 * 
 
 
 */





uint16_t modbusState;
bool screenSaverShown = false;


unsigned long idleScreenRotateTimeout;
bool needIdleScreenRotate;
unsigned long nextIdleScreen;


void ResetIdleScreenTimeout(unsigned long *curMs)
{
    idleScreenRotateTimeout = GetSettingValue(SETTING_IDLE_SCREEN_ROTATE_TIMEOUT) * 100;
    needIdleScreenRotate = idleScreenRotateTimeout > 0;
    nextIdleScreen = *curMs + idleScreenRotateTimeout;    
}

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();


    
    /* TODO <INSERT USER APPLICATION CODE HERE> */
    
    Modbus(0, 0);
    
    LED_ALARM_OFF;
    LED_FIRE_OFF;
    LED_FAILURE_OFF;
    LED_CRASH_OFF;
    
    TRISDbits.RD0 = 0;
    TRISDbits.RD1 = 0;
    TRISDbits.RD2 = 0;
    TRISDbits.RD3 = 0;
    TRISDbits.RD4 = 0;

    LED_WORK_ON;
    

    
    // 100 kbps
    // 2 k for 400 kHz and 1 MHz
    OpenI2C(MASTER, SLEW_OFF);// Initialize I2C module
    // I2C Master mode, clock = FOSC/(4 * (SSPADD + 1)) = 9216000 /(4 * (SSPADD + 1))
    SSPADD = 22; // 1MHz Baud clock(1) @9MHz
                //400kHz Baud clock(4) @9MHz
                //100kHz Baud clock(22) @9MHz
    
    
    TRISAbits.RA4 = 1;
    
    
    InitSettings();
    
    
    
    LoadParamsFromEeprom();
    
    //DisplayPrintUInt(3, DEC | SHOW_USE_FIELD_SIZE | FIELD_SIZE(4));
    //DisplayPrintFloat(-35 * 0.1, 1 | SHOW_USE_FIELD_SIZE | FIELD_SIZE(4));
    
//    DisplaySetCursorPos(0x3e, 1);
//    while(BusyXLCD());
//    uint8_t aa = ReadAddrXLCD();
//    DisplaySetCursorPos(0, 1);
//    DisplayPrintUInt(aa, DEC);
    
    
    
    
//    while(BusyXLCD());
//    DisplayPrintUInt(ReadAddrXLCD(), DEC);
//    while(BusyXLCD());
//    DisplayPrintUInt(ReadAddrXLCD(), DEC);
//    PrintParameterByValue(10, 1030, 4, 0, PPN_NONE);
    //uint16_t val = GetSettingsValue(0);
    
    
    //initRes = 1;////!!!!!!!!!
    
 //   while(1);
    
    uint32_t curMs = millis();
    uint32_t nextSec = curMs + 1000;
    uint32_t nextModbusQuery = curMs;
    uint32_t screenSaveStart = curMs + GetSettingValue(SETTING_SAVESCREEN_TIMEOUT) * 1000;
    
    ResetIdleScreenTimeout(&curMs);
    uint32_t nextKeyPressAvailable = 0;
    
    
    // ���� ����� (5�) ������� CLR, �� ���������������
    unsigned long timeToReset;
  
#ifdef SERIAL_DEBUG
    //DebugPrintValue("Second controller rate", GetControllerRate(1));
    
    
    DebugPrintStrLn("Start loop!");
    //ModbusChangeMode(true);
    /*modbus_t tt;
    tt.u8id = 10;
    tt.u8fct = 1;
    tt.u16CoilsNo = 1;
    tt.u16RegAdd = 0;
    tt.au16reg = NULL;
    ModbusQuery(&tt);*/
    
    
#endif    
    
    //bool isTimerOverflow = false; // ����� curMs ������������ �� ������������ ��������
    
    while(1)
    {
        __delay_ms(5);
        uint32_t tmpMs = millis();
        if(tmpMs < curMs) // ������������
        {// ����� ����������� ��� ����������, ��������� �� �������
            // ���� ���������� ��� ������ ������� �����, ��������� �
            if(nextIdleScreen > tmpMs)
                nextIdleScreen = 0;
            if(screenSaveStart > tmpMs)
                screenSaveStart = 0;
            if(nextSec > tmpMs)
            {    nextSec = 1000 - (UINT32_MAX - nextSec);
                if(nextSec > 1000)
                    nextSec = 1000;
            }
            if(nextModbusQuery > tmpMs)
                nextModbusQuery = _heartBeat;
            
            for(uint8_t i = 0; i < ControllersCount; i++)
            {
                if(ControllersNextRequest[i].nextRequest > tmpMs)
                    ControllersNextRequest[i].nextRequest = GetControllerRate(i) * 1000UL;
            }
        }
                
        curMs = tmpMs;
        
        
        if(CASE_OPEN)
            LED_ALARM_ON; 
        else
            LED_ALARM_OFF; 
        
        
        

        if(initRes == 0)
        {
            // buttons
            while(1) // ����� break'��� ��������
            {
                uint8_t butChanged = IsButtonChanged();
                // TODO: <������� ����� CLR �������� ��� �������� �� ������� ������>
                // TODO: <������� ���������������� ������������ ������� � �������� ��������>
                //curMs >= nextKeyPressAvailable
                if(butChanged != BTN_NONE)
                {

                    if(ButtonStates[butChanged] == BUTTON_PRESSED)
                    {
                        if(screenSaverShown)
                        {
                            //if(butChanged == BTN_CLR)
                            //    break;

                            screenSaveStart = curMs + GetSettingValue(SETTING_SAVESCREEN_TIMEOUT) * 1000;
                            SetBakLightDuty(GetSettingValue(SETTING_LCD_BK) / 50);
                            SetKbBakLightDuty(GetSettingValue(SETTING_KB_BK) / 50);
                            screenSaverShown = false;
                            //IdleStart();
                            //nextKeyPressAvailable = curMs + INTERVAL_BETWEEN_KEYPRESS_AFTER_SCREENSAVER_MS;
                            //break;
                        }
    //                    else
    //                        nextKeyPressAvailable = curMs + INTERVAL_BETWEEN_KEYPRESS_MS;
                        ResetIdleScreenTimeout(&curMs);
                        screenSaveStart = curMs + GetSettingValue(SETTING_SAVESCREEN_TIMEOUT) * 1000;
                        switch(butChanged)
                        {
                            case BTN_PRG:
                            {
                                switch(_currentSection)
                                {
                                    case SECTION_IDLE:
                                    {
                                        if(IdleIsRoot()) // ��������� � ����� ������������ ��������
                                        {
                                            _currentSection = SECTION_ROOMS;
                                            RoomsStart();
                                        }
                                    }
                                    break;
                                }
                            }
                            break;



                            case BTN_LEFT:
                                switch(_currentSection)
                                {
                                    case SECTION_IDLE:
                                        IdleOnButton(butChanged);
    //                                    if(IdleIsRoot())
    //                                    {
    //                                        _currentSection = SECTION_SETTINGS;
    //                                        SettingsStart();
    //                                    }
    //                                    else
    //                                        IdleOnButton(butChanged);
                                        break;
                                    case SECTION_SETTINGS:
                                        if(SettingsIsRoot())
                                        {
                                            _currentSection = SECTION_ROOMS;
                                            RoomsStart();
                                        }
                                        else
                                            SettingsOnButton(butChanged);        
                                        break;
                                    case SECTION_ROOMS:
                                        if(RoomsIsRoot())
                                        {
                                            _currentSection = SECTION_SETTINGS;
                                            SettingsStart();
                                        }
                                        else
                                            RoomsOnButton(butChanged);       
                                        break;
                                }                    
                                break;
                            case BTN_RIGHT:
                                switch(_currentSection)
                                {
                                    case SECTION_IDLE:
    //                                    if(IdleIsRoot())
    //                                    {
    //                                        _currentSection = SECTION_ROOMS;
    //                                        RoomsStart();
    //                                    }
    //                                    else
                                            IdleOnButton(butChanged);
                                        break;
                                    case SECTION_ROOMS:
                                        if(RoomsIsRoot())
                                        {
                                            _currentSection = SECTION_SETTINGS;
                                            SettingsStart();
                                        }
                                        else
                                            RoomsOnButton(butChanged);    
                                        break;
                                    case SECTION_SETTINGS:
                                        if(SettingsIsRoot())
                                        {
                                            _currentSection = SECTION_ROOMS;
                                            RoomsStart();
                                        }
                                        else
                                            SettingsOnButton(butChanged);       
                                        break;
                                }
                                break;
                            case BTN_CLR: // ��������� � ��������� �����
                                timeToReset = curMs + RESET_TIMEOUT_MS;
                                switch(_currentSection)
                                {
                                    case SECTION_IDLE:
    //                                    if(IdleIsRoot())
    //                                    {
    //                                        screenSaveStart = curMs;
    //                                        SetBakLightDuty(GetSettingValue(SETTING_SAVESCREEN_BK) / 50);
    //                                        SetKbBakLightDuty(GetSettingValue(SETTING_SAVESCREEN_KB_BK) / 50);
    //                                        ShowTimeScreen();
    //                                    }
    //                                    else
                                            IdleOnButton(butChanged);
                                        break;
                                    case SECTION_ROOMS:
                                        if(RoomsIsRoot())
                                        {
                                            _currentSection = SECTION_IDLE;
                                            IdleStart();
                                        }
                                        else
                                            RoomsOnButton(butChanged);    
                                        break;
                                    case SECTION_SETTINGS:
                                        if(SettingsIsRoot())
                                        {
                                            _currentSection = SECTION_IDLE;
                                            IdleStart();
                                        }
                                        else
                                            SettingsOnButton(butChanged);       
                                        break;


                                }
                            break;
                            default:
                                switch(_currentSection)
                                {
                                    case SECTION_IDLE:
                                        IdleOnButton(butChanged);
                                        break;
                                    case SECTION_ROOMS:
                                        RoomsOnButton(butChanged);
                                        break;
                                    case SECTION_SETTINGS:
                                        SettingsOnButton(butChanged);    
                                        break;
                                }
                                break;
                        }


                    }
                    else
                    {
                        timeToReset = UINT32_MAX;
                    }
                }
                break;
            }

                
            if(curMs > timeToReset && ButtonStates[BTN_CLR] == BUTTON_PRESSED)  
            {
                Reset();
            }
                
            if(_currentSection == SECTION_IDLE && needIdleScreenRotate && curMs >= nextIdleScreen)
            {                
                ResetIdleScreenTimeout(&curMs);
                IdleNextScreen();
                
            }
            

            if(curMs >= nextSec)
            {            
                nextSec += 1000; 
                //lastMs = curMs;
                AddSecond();


                // ����� �������� �� ��������
                if(curMs >= screenSaveStart)
                {
                    if(!screenSaverShown)
                    {
                        
                        screenSaverShown = true;
                        SetBakLightDuty(GetSettingValue(SETTING_SAVESCREEN_BK) / 50);
                        SetKbBakLightDuty(GetSettingValue(SETTING_SAVESCREEN_KB_BK) / 50);

                        if(_currentSection != SECTION_IDLE)
                        {
                            _currentSection = SECTION_IDLE;
                            ResetIdleScreenTimeout(&curMs);
                            IdleStart(); // ������������ �� ��������� �����                    
                        }
                    }
                    //ShowTimeScreen();
                }




//                // measure 12V
//               ADCON0bits.GO = 1;          //start the conversion
//                while(ADCON0bits.GO == 1){};  //wait for the conversion to end
//
//                uint16_t result = (ADRESH << 8)+ADRESL;	//combine the 10 bits of the conversion
//                double voltage = result * 0.00047169811320754716981132075471698;// 2120.0;
//                DisplayClear();
//                DisplayPrintFloat(voltage, 2);
//                
//
//                
//                 12.4 - 26368 --- 2126,4516129032258064516129032258
//                 * 12 - 25472 --- 2122,6666666666666666666666666667
//                 * 14 - 29632 --- 2116,5714285714285714285714285714
//                 * 13 - 27648 --- 2126,7692307692307692307692307692

                 
            }
        }
        
        //������ �� ��������� ��������
        // 0x7f 0x03 0xFF 0x00 0x00 0x08
        // ������ � ������� (�� �������� 1)
        // 0x7f 0x06 0xff 0x00 0x00 0x10
        
        if(ModbusIsMasterMode())
        {          
            
            if(ModbusGetState() == COM_WAITING)
            {
                modbusState = ModbusPollMaster(); 
                bool anyBanned = false;
                for(uint8_t i = 0; i < ControllersCount; i++)
                {
                    if(ControllersNextRequest[i].banned != CB_NONE)
                    {
                        anyBanned = true;
                        break;
                    }
                }
                SetCrashLed(anyBanned);
                
            }
            if(ModbusGetState() == COM_IDLE && nextModbusQuery < curMs)
            {
                for(uint8_t i = 0; i < ControllersCount; i++)
                {
                    if(ControllersNextRequest[i].banned == CB_COMPLETE_BAN)
                        continue;
                    if(ControllersNextRequest[i].nextRequest < curMs)
                    {
                        modbus_t tt;
                        tt.u8id = GetControllerAddress(i);
#ifdef SERIAL_DEBUG
                        DebugPrintValue("Send query", tt.u8id);
#endif
                        tt.u8fct = MB_FC_READ_INPUT_REGISTER;
                        tt.u16CoilsNo = 2 + HOLDING_REGS_SIMPLE_COUNT + INPUT_REGS_SIMPLE_COUNT;
                        tt.u16RegAdd = 0;
                        tt.au16reg = NULL;
                        tt.curControllerIdInEe = i;
                        ModbusQuery(&tt);
                        
                        switch(ControllersNextRequest[i].banned)
                        {
                            case CB_NONE:
                            {
                                uint8_t rate = GetControllerRate(i);
                                if(rate> 0)
                                    ControllersNextRequest[i].nextRequest = curMs + rate * 1000UL;
                                else
                                    ControllersNextRequest[i].nextRequest = curMs + _heartBeat;
                            }
                            break;
                            case CB_FIRST_BAN:
                                ControllersNextRequest[i].nextRequest = curMs + 5 * 60 * 1000UL; // 5 ����� 5 * 60
                                break;
                            case CB_SECOND_BAN:
                                ControllersNextRequest[i].nextRequest = curMs + 30 * 60 * 1000UL; // 30 ����� 30 * 60
                                break;
                        }
                        // ������� ����� ������� �������, ��� ���� ��������� ������
                        break;
                    }
                }
                
                
                
                nextModbusQuery = curMs + _heartBeat;
            }
        }
        else
        {
            modbusState = ModbusPoll(DiscreteParameters, DiscreteParamsCount, DiscreteParameters, DiscreteParamsCount, _MODBUSInputRegs, modbusInputBufLen, _parameters, ParamCount);
            io_poll();
        }
        
        
    }

}



//uint8_t oldMin = 0xff;
//
//void ShowTimeScreen()
//{
//    uint8_t hour, min;
//    bool getTimeRes = getHourMin(&hour, &min);
//    
//    if(screenSaverShown && (min == oldMin))
//        return;
//    screenSaverShown = true;
//    
//    oldMin = min;
//    
//    struct tm *timeStruct = localtime(GetTime());    
//    DisplayClear();
//    //DisplayPrintStr("�����: ");
//    DisplayPrintStr(daysOfWeek[timeStruct->tm_wday]);
//    
//    
//    DisplaySetCursorPos(8, 0);
//    if(getTimeRes)
//    {
//        DisplayPrintUInt(hour, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
//        DisplayPrintChar(':');
//        DisplayPrintUInt(min, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
//    }
//    else
//    {
//        DisplayPrintStr("!!");
//        DisplayPrintUInt(hour, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
//        DisplayPrintChar(':');
//        DisplayPrintUInt(min, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
//    }
//    DisplaySetCursorPos(0, 1);
//    DisplayPrintUInt(timeStruct->tm_mday, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
//    DisplaySetCursorPos(3, 1);
////    DisplayPrintStr("����: ");
//    DisplayPrintStr(monthes[timeStruct->tm_mon]);
//    DisplaySetCursorPos(12, 1);
//    DisplayPrintUInt(timeStruct->tm_year + 1900, DEC);
//    
//}


void io_poll() 
{
    uint16_t lastFileNum;
    uint16_t lastAddress;
    uint16_t lastEndAddress;
    uint8_t lastCommand;
    //uint16_t lastCount;
    uint8_t *lastFunction = ModbusGetLastCommand(&lastFileNum, &lastAddress, &lastEndAddress, &lastCommand);
    if(*lastFunction == MB_FC_NONE)
        return;
    
    lastEndAddress += lastAddress - 1;
    /*
    uint8_t v1;
    if(*lastFunction == MB_FC_SYSTEM_COMMAND)
    {
        if(lastCommand == MB_COMMAND_SET_TIME)
        {
            LightStatusLed(LED_STATUS_BLOCKING, false, false);
            LoadNextEvent();
        }        
        return;
    }
    if(*lastFunction == MB_FC_USER_COMMAND)
    {
        ProcessUserCommands();
        return;
    }
    */
    if(*lastFunction == MB_FC_WRITE_REGISTER || *lastFunction == MB_FC_WRITE_MULTIPLE_REGISTERS)
    {
        switch(_currentSection)
         {
            case SECTION_IDLE:
                IdleUpdateView();        
                break;
            case SECTION_SETTINGS:
                //SettingsUpdateView();        
                break;
            case SECTION_ROOMS:    
                RoomsUpdateView();        
                break;
        }     
    }
    
    
    if(*lastFunction == MB_FC_WRITE_FILE_RECORD)
    {
        if(lastFileNum == 1) // nternal EEPROM settings
        {
            InitSettings();
            ModbusSetExceptionStatusBit(MB_EXCEPTION_LAST_COMMAND_STATE, true);
            switch(_currentSection)
            {
                case SECTION_IDLE:
                    break;
                case SECTION_SETTINGS:
                    SettingsUpdateView();        
                    break;
                case SECTION_ROOMS:    
                    break;
            }                 
        }
        // TODO: <������������� ������ ������������, ���� �� ��������� ��� ����������>
        // �������� � ������ ������ ������ ���������� � ������ 0xFF ����� �� ������������ ������
        // � � ����� ���������� ������ 2 ����� ��� ����
        else if(lastFileNum > 1) // External EEPROM param settings 
        {
            LoadParamsFromEeprom();
            ModbusSetExceptionStatusBit(MB_EXCEPTION_LAST_COMMAND_STATE, true);
            switch(_currentSection)
            {
                case SECTION_IDLE:
                    IdleStart();
                    break;
                case SECTION_SETTINGS:
//                    SettingsUpdateView();        
                    break;
                case SECTION_ROOMS:
                    RoomsStart();
                    break;
            }    
        }
        
//        for(uint8_t i = 0; i < eventCount && i < MAX_EVENTS; i++)
//            LightLed(i + 1, LED_GREEN, false);
        return;
    }
}
