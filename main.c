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

#include <plib/i2c.h>
//#include <delays.h>
#include "LCD/xlcd.h"

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "interrupts.h"
#include "buttons.h"


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
uint8_t _currentSection;









// 0 .. 3FF
void SetBakLightDuty(uint16_t dc) 
{
    // PWM duty cycle = (CCPR1L:CCP1CON<5:4>) *
    // TOSC * (TMR2 prescale value)
    //u16 tempValue = 0;
    CCP1CONbits.DC1B = dc & 0x03;
    CCPR1L = (uint8_t)(dc >> 2);
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
void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();


    
    
    /* TODO <INSERT USER APPLICATION CODE HERE> */
    TRISDbits.RD0 = 0;
    TRISDbits.RD1 = 0;
    TRISDbits.RD2 = 0;
    TRISDbits.RD3 = 0;
    TRISDbits.RD4 = 0;
    
    LATDbits.LD0 = 0;
    LATDbits.LD1 = 1;
    LATDbits.LD2 = 0;
    
    
    
    // LCD Backlight
    //RC2|CPP1
    #define CCP1				TRISCbits.TRISC2
    CCP1 = 0; 
    T2CONbits.TMR2ON = 1;
    // Set CCP1 to PWM mode
    CCP1CONbits.CCP1M = 0x0f;
    // Set PR2
    //Period = 4 * (1/SYS_FREQ) * 16 * (scaling value + 1)
    //PWM period=[(PR2)+1]*4*Tosc*(TMR2 preScalevalue)
    // 0x90 3229 ??
    // [144 + 1] * 4/10 000 000 * 16 = 0,000928 = 1/1077  1/3229
    // 
    // 
    PR2 = 255;
    
    // Set the prescaler to 16
    T2CONbits.T2CKPS1 = 1;
    T2CONbits.T2CKPS0 = 0;

    // Set the PWM pin to be an output
    TRISCbits.RC2 = 0;

    /*
     
     Function Set 0 0    0 0 1 DL N F * *
        Set interface data length
        (DL:8-bit/4-bit), numbers of
        display line (N:2-line/1-line)and,
        display font type (F:5?11 dots/5?
        8 dots) 
     
     */
    
    
   
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
    
    
    OpenI2C(MASTER, SLEW_ON);// Initialize I2C module
    
    

    DisplayPrintStr( "АБВГОДЁЖДИЙКЛМНО" );
    DisplaySetCursorPos(0, 1);
    
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
    
    
    
    
    
    
    
    _currentSection = SECTION_IDLE;
    IdleStart();
    
    
    
    unsigned long lastMs = millis();
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
        
        
        
        
        
        
    }

}

