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
uint16_t _mSecondsToScreenSave = 30000; // До минуты



  




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
    
    TRISDbits.RD0 = 0;
    TRISDbits.RD1 = 0;
    TRISDbits.RD2 = 0;
    TRISDbits.RD3 = 0;
    TRISDbits.RD4 = 0;
    
    LATDbits.LD0 = 0;
    LATDbits.LD1 = 1;
    LATDbits.LD2 = 0;
    
    
    
    

    /*
     
     Function Set 0 0    0 0 1 DL N F * *
        Set interface data length
        (DL:8-bit/4-bit), numbers of
        display line (N:2-line/1-line)and,
        display font type (F:5?11 dots/5?
        8 dots) 
     
     */
    //int8_t res = -3;
    //DisplayPrintInt(res, DEC);
    
   
    //WriteCmdXLCD(SHIFT_DISP_LEFT);
    //while(BusyXLCD());
    
    //WriteCmdXLCD(DON);
    //while(BusyXLCD());
 
    /*WriteDataXLCD('A');
    while(BusyXLCD());

    WriteDataXLCD('t');
    while(BusyXLCD());

    WriteDataXLCD(' ');
    while(BusyXLCD());*/
    
    
    // 100 kbps
    // 2 k for 400 kHz and 1 MHz
    OpenI2C(MASTER, SLEW_OFF);// Initialize I2C module
    // I2C Master mode, clock = FOSC/(4 * (SSPADD + 1)) = 9216000 /(4 * (SSPADD + 1))
    SSPADD = 22; // 1MHz Baud clock(1) @9MHz
                //400kHz Baud clock(4) @9MHz
                //100kHz Baud clock(22) @9MHz
    

    /*eeprom_write(20, 123);
    while(EECON1bits.WR)
        continue;
    DisplayPrintInt(eeprom_read(20), DEC);*/
    
    
    //DisplayPrintStr( "яюёжлфыпэцщ" );
    //while(BusyXLCD());

    //WriteCmdXLCD(0xC0);
    //while(BusyXLCD());

    //putrsXLCD( "thanks Ian" );
    //while(BusyXLCD());
    
    
    
    

    LATDbits.LD3 = 1;
    LATDbits.LD4 = 0;
    
    
    TRISAbits.RA4 = 1;
    
    
    // i2c WP
    //TRISCbits.RC1 = 0;
    //LATCbits.LC1 = 0;
    
    
    _currentSection = SECTION_IDLE;
    IdleStart();
    
    //DisplayPrintChar(':');
    //int8_t res = EEByteWrite(0x00, 0x01, 0xA5);
    //DisplayPrintInt(res, DEC);    
    
    
    
    //SetParameter(0, 30);
    //uint16_t par = GetParameter(0);
    
    
    //DisplayPrintProgress(4, 10, 1, 35);
    

    
    
    
    
    
    
    
    
//            struct tm newTime;
//            newTime.tm_year = 17 + 100; // since 1900
//            newTime.tm_mon = 2;
//            newTime.tm_mday = 4;
//            newTime.tm_hour = 11;
//            newTime.tm_min = 45;
//            newTime.tm_sec = 30;
//            time_t newRawTime = mktime(&newTime);
//            SetTime(&newRawTime);
//  
//    
//    
//    struct tm *timeStruct = localtime(GetTime());
//    DisplayPrintUInt(timeStruct->tm_mday, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
//    DisplayPrintChar('/');
//    DisplayPrintUInt(timeStruct->tm_mon, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
//    DisplayPrintChar('/');
//    DisplayPrintUInt(timeStruct->tm_year, DEC);   
    
    
    
    
    
    
    
    
    
    
    
    
    unsigned long lastMs = millis();
    unsigned long screenSaveStart = lastMs + _mSecondsToScreenSave;

    while(1)
    {
        //__delay_us(5);
        
        unsigned long curMs = millis();
        
        
        if(PORTAbits.RA4 == 0)
            LATDbits.LD1 = 0; 
        else
            LATDbits.LD1 = 1; 
        
        
        

        
        // buttons
        uint8_t butChanged = IsButtonChanged();
        if(butChanged != BTN_NONE && ButtonStates[butChanged] == BUTTON_PRESSED)
        {
            screenSaveStart = curMs + _mSecondsToScreenSave;
            timeScreenShown = false;
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
                            screenSaveStart = curMs;
                            ShowTimeScreen();
                            
                            //IdleOnButton(butChanged);
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
            
            
            /*char c = 'Z';
            switch(butChanged)
            {
                case BTN_ARM:
                    c = '0';
                    break;
                case BTN_DISARM:
                    c = '1';
                    break;
                case BTN_BPS:
                    c = '2';
                    break;
                case BTN_TRBL:
                    c = '3';
                    break;
                case BTN_MEM:
                    c = '4';
                    break;
                case BTN_LEFT:
                    c = '5';
                    DisplayScrollLeft();
                    break;
                case BTN_1:
                    c = '6';
                    break;
                case BTN_4:
                    c = '7';
                    break;
                case BTN_7:
                    c = '8';
                    break;
                case BTN_CLR:
                    c = '9';
                    DisplayClear();
                    break;
                case BTN_PRG:
                    c = 'A';
                    break;
                case BTN_2:
                    c = 'B';
                    break;
                case BTN_5:
                    c = 'C';
                    break;
                case BTN_8:
                    c = 'D';
                    break;
                case BTN_0:
                    c = 'E';
                    break;                
                case BTN_RIGHT:                    
                    c = 'F';
                    DisplayScrollRight();
                    break;
                case BTN_3:
                    c = 'G';
                    break;
                case BTN_6:
                    c = 'H';
                    break;
                case BTN_9:
                    c = 'I';
                    break;
                case BTN_ENT:
                    c = 'J';
                    break;
            }
            WriteDataXLCD(c);
            while(BusyXLCD());*/
            
        }
        
        
        if(curMs - lastMs >= 1000)
        {            
            lastMs = curMs;
            AddSecond();
            
            
            // Показ заставки со временем
            if(curMs >= screenSaveStart)
            {
                if(!timeScreenShown)
                {
                    _currentSection = SECTION_IDLE;
                    IdleStart(); // Перекидываем на начальный экран                    
                }
                ShowTimeScreen();
            }
            
            
            
            
            // measure 12V
            /*ADCON0bits.GO = 1;          //start the conversion
            while(ADCON0bits.GO == 1){};  //wait for the conversion to end

            uint16_t result = (ADRESH << 8)+ADRESL;	//combine the 10 bits of the conversion
            double voltage = result * 0.00047169811320754716981132075471698;// 2120.0;
            DisplayClear();
            DisplayPrintFloat(voltage, 2);
            */
            
            /*
             12.4 - 26368 --- 2126,4516129032258064516129032258
             * 12 - 25472 --- 2122,6666666666666666666666666667
             * 14 - 29632 --- 2116,5714285714285714285714285714
             * 13 - 27648 --- 2126,7692307692307692307692307692
             
             */
        }
        
        //Чтение из регистров хранения
        // 0x7f 0x03 0xFF 0x00 0x00 0x08
        // Запись в нулевой (до прошивки 1)
        // 0x7f 0x06 0xff 0x00 0x00 0x10
        
        
        modbusState = ModbusPoll(_MODBUSDiscreteInputs, &_MODBUSCoils, _MODBUSInputRegs, modbusInputBufLen, _MODBUSHoldingRegs, modbusHoldingBufLen);
        io_poll();

        
        
    }

}

void ShowTimeScreen()
{
    timeScreenShown = true;
    DisplayClear();
    DisplayPrintStr("Время: ");
    
    
    uint8_t hour, min;
    if(getHourMin(&hour, &min))
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
    uint16_t lastAddress;
    uint16_t lastEndAddress;
    uint8_t lastCommand;
    //uint16_t lastCount;
    uint8_t *lastFunction = ModbusGetLastCommand(&lastAddress, &lastEndAddress, &lastCommand);
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
    
    if(*lastFunction == MB_FC_WRITE_REGISTER || *lastFunction == MB_FC_WRITE_MULTIPLE_REGISTERS)
    {

    }
    

    if(*lastFunction == MB_FC_WRITE_FILE_RECORD)
    {
        InitFromEeprom();
        ModbusSetExceptionStatusBit(MB_EXCEPTION_LAST_COMMAND_STATE, true);
//        for(uint8_t i = 0; i < eventCount && i < MAX_EVENTS; i++)
//            LightLed(i + 1, LED_GREEN, false);
        return;
    }*/
}
