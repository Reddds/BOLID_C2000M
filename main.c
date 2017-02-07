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
#include "ModbusRtu.h"
#include "ParametersController.h"

#include "Sections/SectionIdle.h"
#include "Sections/SectionRooms.h"
#include "Sections/SectionSettings.h"






#include "SettingsController.h"




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





// Настройки    
// Сколько миллисекунд до хранителя экрана
//uint16_t _mSecondsToScreenSave = 30000; // До минуты

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
        DisplayPrintStr("Ошибка EEPROM!");
    }
    else
    {
        LED_FAILURE_OFF;
        _currentSection = SECTION_IDLE;
        IdleStart();
    }
}



/*
 * Основные настройки - действия по быстрым кнопкам 
 * 
 * 
 * ARM - Тип (1 - Изменить параметр) / (ID параметра) | ()
 * 
 * 
 * 
 * 
 * 
 Отображение на начальном экране
 * ________________
 * Ул:  ¤ -12°С 67%|         
 * Дом:   +22°С 35%|
 * ~~~~~~~~~~~~~~~~
 * 
 * ГЛАВНЫЙ ЭКРАН:
 * 
 * Конфиг главного экрана
 * 
 * Позиция (Кол, ряд) / Тип / Значение
 * 
 * Типы: 
 *  0 - Строка (0 поз - длина)
 *  1 - Параметр
 * 
 * 
 * Кнопки:
 * <,> - Переход в /Инфа по комнатам/Настройки
 * 
 * 
 * 
 * ВЫБОР КОМНАТЫ:
 * ________________
 * Выбор комнаты   |         
 * 1 Спальня       |
 * ~~~~~~~~~~~~~~~~ 
 * <,> - выбор комнаты
 * 
 * 
 * ИНФА ПО КОМНАТЕ:
 * ________________
 * № Назв. комнаты |         
 * Давление: 440мм |
 * ~~~~~~~~~~~~~~~~
 * <,> - выбор параметра
 * 
 
 
 */





uint16_t modbusState;
bool timeScreenShown = false;

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
    //uint16_t val = GetSettingsValue(0);
    
    
    //initRes = 1;////!!!!!!!!!
    
    //while(1);
    
    unsigned long curMs = millis();
    unsigned long nextSec = curMs + 1000;
    unsigned long screenSaveStart = curMs + GetSettingValue(SETTING_SAVESCREEN_TIMEOUT) * 1000;
    unsigned long nextKeyPressAvailable = 0;
    
    
    
    
    
    while(1)
    {
        __delay_ms(5);
        
        curMs = millis();
        
        
        if(CASE_OPEN)
            LED_ALARM_ON; 
        else
            LED_ALARM_OFF; 
        
        
        

        if(initRes == 0)
        {
            // buttons
            while(1) // Чтобы break'ами выходить
            {
                uint8_t butChanged = IsButtonChanged();
                if(curMs >= nextKeyPressAvailable
                        && butChanged != BTN_NONE && ButtonStates[butChanged] == BUTTON_PRESSED)
                {


                    if(timeScreenShown)
                    {
                        if(butChanged == BTN_CLR)
                            break;
                        screenSaveStart = curMs + GetSettingValue(SETTING_SAVESCREEN_TIMEOUT) * 1000;
                        SetBakLightDuty(GetSettingValue(SETTING_LCD_BK) / 50);
                        SetKbBakLightDuty(GetSettingValue(SETTING_KB_BK) / 50);
                        timeScreenShown = false;
                        IdleStart();
                        nextKeyPressAvailable = curMs + INTERVAL_BETWEEN_KEYPRESS_AFTER_SCREENSAVER_MS;
                        break;
                    }
                    else
                        nextKeyPressAvailable = curMs + INTERVAL_BETWEEN_KEYPRESS_MS;
                    screenSaveStart = curMs + GetSettingValue(SETTING_SAVESCREEN_TIMEOUT) * 1000;
                    switch(butChanged)
                    {
                        case BTN_LEFT:
                            switch(_currentSection)
                            {
                                case SECTION_IDLE:
                                    if(IdleIsRoot())
                                    {
                                        _currentSection = SECTION_SETTINGS;
                                        SettingsStart();
                                    }
                                    else
                                        IdleOnButton(butChanged);
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
                                        _currentSection = SECTION_IDLE;
                                        IdleStart();
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
                                    if(IdleIsRoot())
                                    {
                                        _currentSection = SECTION_ROOMS;
                                        RoomsStart();
                                    }
                                    else
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
                                        _currentSection = SECTION_IDLE;
                                        IdleStart();
                                    }
                                    else
                                        SettingsOnButton(butChanged);       
                                    break;
                            }
                            break;
                        case BTN_CLR: // Переходим в начальный экран
                            switch(_currentSection)
                            {
                                case SECTION_IDLE:
                                    if(IdleIsRoot())
                                    {
                                        screenSaveStart = curMs;
                                        SetBakLightDuty(GetSettingValue(SETTING_SAVESCREEN_BK) / 50);
                                        SetKbBakLightDuty(GetSettingValue(SETTING_SAVESCREEN_KB_BK) / 50);
                                        ShowTimeScreen();
                                    }
                                    else
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
                break;
            }


            if(curMs >= nextSec)
            {            
                nextSec += 1000; 
                //lastMs = curMs;
                AddSecond();


                // Показ заставки со временем
                if(curMs >= screenSaveStart)
                {
                    if(!timeScreenShown)
                    {
                        _currentSection = SECTION_IDLE;
                        SetBakLightDuty(GetSettingValue(SETTING_SAVESCREEN_BK) / 50);
                        SetKbBakLightDuty(GetSettingValue(SETTING_SAVESCREEN_KB_BK) / 50);

                        IdleStart(); // Перекидываем на начальный экран                    
                    }
                    ShowTimeScreen();
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
        
        //Чтение из регистров хранения
        // 0x7f 0x03 0xFF 0x00 0x00 0x08
        // Запись в нулевой (до прошивки 1)
        // 0x7f 0x06 0xff 0x00 0x00 0x10
        
        
        modbusState = ModbusPoll(_MODBUSDiscreteInputs, &_MODBUSCoils, _MODBUSInputRegs, modbusInputBufLen, _MODBUSHoldingRegs, modbusHoldingBufLen);
        io_poll();

        
        
    }

}

uint8_t oldMin = 0xff;

void ShowTimeScreen()
{
    uint8_t hour, min;
    bool getTimeRes = getHourMin(&hour, &min);
    
    if(timeScreenShown && (min == oldMin))
        return;
    timeScreenShown = true;
    
    oldMin = min;
    
    
    DisplayClear();
    DisplayPrintStr("Время: ");
    
    
    
    
    if(getTimeRes)
    {
        DisplayPrintUInt(hour, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
        DisplayPrintChar(':');
        DisplayPrintUInt(min, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
    }
    else
    {
        DisplayPrintStr("!!");
        DisplayPrintUInt(hour, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
        DisplayPrintChar(':');
        DisplayPrintUInt(min, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
    }
    DisplaySetCursorPos(0, 1);
    DisplayPrintStr("Дата: ");
    struct tm *timeStruct = localtime(GetTime());
    DisplayPrintUInt(timeStruct->tm_mday, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
    DisplayPrintChar('.');
    DisplayPrintUInt(timeStruct->tm_mon, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
    DisplayPrintChar('.');
    DisplayPrintUInt(timeStruct->tm_year + 1900, DEC);
    
}


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
