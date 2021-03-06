/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "system.h"
#include "user.h"
#include "buttons.h"
#include "LCD/xlcd.h"
#include "interrupts.h"
#include "MODBUS/ModbusRtu.h"
#include "i2c/i2c.h"
#ifdef SERIAL_DEBUG
#include "LCD/Print.h"
#endif

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

#define BAUDRATE    9600
#define	UBRG	( (((SYS_FREQ / BAUDRATE) / 8) - 1) / 2 )

time_t currentTime = 0;
bool _isMaster = false;

uint8_t ledAlarmState;
uint8_t ledFireState;
uint8_t ledFailureState;
uint8_t ledCrashState;
uint8_t ledWorkState;

uint8_t ledAlarmBlink;
uint8_t ledFireBlink;
uint8_t ledFailureBlink;
uint8_t ledCrashBlink;
uint8_t ledWorkBlink;


void PortBegin()
{
    TXSTA = 0;
    TXSTAbits.TXEN = 1;
    TXSTAbits.BRGH = 1;
    
    SPBRG = UBRG;
    RCSTA = 0;
    RCSTAbits.SPEN = 1;
    RCSTAbits.CREN = 1;
    
    TRISCbits.RC5 = 0;
    LATCbits.LATC5 = 0;

#ifdef SERIAL_DEBUG
    SPBRG2 = UBRG;
    //RCSTA2bits.SYNC = 0;
    RCSTA2 = 0;
    RCSTA2bits.SPEN = 1;
    RCSTA2bits.CREN = 1;
    TXSTA2 = 0;
    TXSTA2bits.TXEN = 1;   
    TXSTA2bits.BRGH = 1;
#endif    
    
}


uint8_t Char0[] = 
{
    0b00000001,
    0b00000011,
    0b00000111,
    0b00010011,
    0b00011001,
    0b00011100,
    0b00011000,
    0b00010000,
};

void InitBacklight()
{
    // LCD Backlight
    //RC2|CPP1
    #define CCP1    TRISCbits.TRISC2
    #define CCP4    TRISGbits.TRISG3

    T2CONbits.TMR2ON = 1;
    // Set CCP1 to PWM mode
    CCP1CONbits.CCP1M = 0x0f;
    CCP4CONbits.CCP4M = 0x0f;
    // Set PR2
    // Period = 4 * (1/SYS_FREQ) * 16 * (scaling value + 1) 
    // PWM period=[(PR2)+1]*4*Tosc*(TMR2 preScalevalue)
    // 0x90 3229 ??
    // [144 + 1] * 4/10 000 000 * 16 = 0,000928 = 1/1077  1/3229
    // [0 + 1] * 4 / 9 216 000 * 16 = 1/144000
    // 
    //PR2 = 255;
    PR2 = 0;
    CCPR1L = 0;
    CCPR4L = 0;
    
    // Set the prescaler to 4
    T2CONbits.T2CKPS1 = 0;
    T2CONbits.T2CKPS0 = 1;

    
    SetBakLightDuty(0);
    SetKbBakLightDuty(0);
    
    // Set the PWM pin to be an output
    CCP1 = 0; 
    CCP4 = 0;
}

#ifdef SERIAL_DEBUG
#define	TXE_DELAY 	10
uint8_t DebugWrite(uint8_t *buf, uint8_t buflen)
{
    return DebugWriteField(buf, buflen, 0);
    /*__delay_us(TXE_DELAY);
    for(uint8_t i = 0; i < buflen; i++)
    {
        while(!TXSTA2bits.TRMT);//TRMT
        TXREG2 = buf[i];
    }
    while(!TXSTA2bits.TRMT);//TRMT
    return buflen;
    */
}

uint8_t DebugWriteField(uint8_t *buf, uint8_t buflen, uint8_t fieldWidth)
{
    __delay_us(TXE_DELAY);
    for(uint8_t i = 0; i < buflen; i++)
    {
        while(!TXSTA2bits.TRMT);//TRMT
        TXREG2 = buf[i];
    }
    if(fieldWidth > buflen)
    {
        for(uint8_t i = buflen; i < fieldWidth; i++)
        {
            while(!TXSTA2bits.TRMT);//TRMT
            TXREG2 = ' ';
        }
        buflen = fieldWidth;
    }
    while(!TXSTA2bits.TRMT);//TRMT
    return buflen;
    
}

uint8_t DebugPrintNumber(unsigned long n, uint16_t options)
{
    char buf[16]; //8 * sizeof(long) + 1 Assumes 8-bit chars plus zero byte.
    uint8_t printedCharCount = DisplaySprint(n, options, buf, sizeof(buf));
    DebugWrite((const char *)(&(buf[sizeof(buf) - printedCharCount - 1])), printedCharCount);
}
#endif


//-- 0 .. 3FF
//++ 0..3
void SetBakLightDuty(uint16_t dc) 
{
    // PWM duty cycle = (CCPR1L:CCP1CON<5:4>) *
    // TOSC * (TMR2 prescale value)
    //u16 tempValue = 0;
  
    CCP1CONbits.DC1B = dc & 0x03;
    //CCPR1L = (uint8_t)(dc >> 2);
    
    
}  

void SetKbBakLightDuty(uint16_t dc) 
{
    // PWM duty cycle = (CCPR1L:CCP1CON<5:4>) *
    // TOSC * (TMR2 prescale value)
    //u16 tempValue = 0;
  
    CCP4CONbits.DC4B = dc & 0x03;
    //CCPR1L = (uint8_t)(dc >> 2);
}

void SetMODBUSMode(uint16_t isMaster)
{
    ModbusChangeMode(isMaster > 0);
}

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */
    
    
     /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    BOR = 1;
    POR = 1;
    
    /* ????????? ?????????? */
    INTCONbits.PEIE = 1; // Peripheral Interrupt Enable
    ei(); // Global Interrupt Enable
    RCONbits.IPEN   = 1; // Interrupt Priority Enable
    
    /* Enable interrupts */
    
    // Init Timer 1 ------------------------------------------------------------
    T1CONbits.RD16 = 1;
    T1CONbits.T1SYNC = 0;
    T1CONbits.TMR1CS = 0;
    // FCY = 2 500 000
    T1CONbits.T1CKPS = 0; // Prescaler 1
    
    
    
    PIE1bits.TMR1IE   = 1;  // Enable interrupt by tomer 1 (interrupt) TMR1
    IPR1bits.TMR1IP   = 1;  // Enable interrupt priority TMR1
    WRITETIMER1(TIMER_TICKS_IN_1_MS);
    //TMR1L              = TIMER_TICKS_IN_1_MS_L; // ???? ???? ?? ????? ??????????? ? ???? ??????? ?? 0xFFFF
    //TMR1H              = TIMER_TICKS_IN_1_MS_H;
    PIR1bits.TMR1IF   = 0; // ??????? ???? ?????????? (????? ????? ?? ????????? ? ??????????)
    
    T1CONbits.TMR1ON = 1; // Switch on timer
    //--------------------------------------------------------------------------
    
    // Init Timer 0 (6 sec) ----------------------------------------------------
    T0CONbits.T08BIT = 0; // 16 bit
    T0CONbits.T0CS = 0; //Internal instruction cycle clock (CLKO)
    // FCY = 2 500 000
    T0CONbits.PSA = 0; //Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output
    /*
    111 = 1:256 prescale value
    110 = 1:128 prescale value
    101 = 1:64 prescale value
    100 = 1:32 prescale value
    011 = 1:16 prescale value
    010 = 1:8 prescale value
    001 = 1:4 prescale value
    000 = 1:2 prescale value
     */
    T0CONbits.T0PS = 7;
    
    
    
    INTCONbits.TMR0IE   = 1;  // Enable interrupt by tomer 1 (interrupt) TMR1
    INTCON2bits.TMR0IP   = 1;  // Enable interrupt priority TMR1
    WRITETIMER0(WATCH_TIMER_TICKS_TO_END_6S);
    //TMR1L              = TIMER_TICKS_IN_1_MS_L; // ???? ???? ?? ????? ??????????? ? ???? ??????? ?? 0xFFFF
    //TMR1H              = TIMER_TICKS_IN_1_MS_H;
    //INTCONbits.TMR0IF   = 0; // ��������� 6-���������� �������
    
    //T0CONbits.TMR0ON = 1; // Switch on timer
    //--------------------------------------------------------------------------
    InitBacklight();
    
    // Usart
    InitUartBuffer();   
    
    PortBegin();
    PIE1bits.RCIE = 1; // 
    /* Make receive interrupt low priority */
    IPR1bits.RCIP = 0;
    
    
    	// Clearing buffers
	for (unsigned char i = 0; i < modbusInputBufLen; i++)
		_MODBUSInputRegs[i] = 0;
//	for (unsigned char i = 0; i < modbusHoldingBufLen; i++)
//		_MODBUSHoldingRegs[i] = 0;
        //TRISB = 0xC0;
   
    
    
    
    
    // measure 12V
    TRISAbits.TRISA0 = 1;
    ADCON0bits.CHS = 0; // 0000 = Channel 0 (AN0)
    ADCON1bits.VCFG = 0; //00 AVDD AVSS
    ADCON1bits.PCFG = 0b1110;
    
    ADCON2bits.ADCS = 0b100;// = FOSC/4
    ADCON0bits.ADON = 1;
    
    
    
    // ����������
    LATDbits.LATD0 = 1;
    LATDbits.LATD1 = 1;
    LATDbits.LATD2 = 1;
    LATDbits.LATD3 = 1;
    LATDbits.LATD4 = 1;
    
    TRISDbits.RD0 = 0;
    TRISDbits.RD1 = 0;
    TRISDbits.RD2 = 0;
    TRISDbits.RD3 = 0;
    TRISDbits.RD4 = 0;
    
    
    
    InitButtons();
    // LCD
    OpenXLCD(0b00111100, 16, 2, LCD_5x8DOTS); //LINES_5X8
    while(BusyXLCD());
    //DisplayCreateChar(0x00, Char0);
    
    
    WP_LATCH = 1;
    WP_TRIS = 1;
    
    // To configure PORTF as digital I/O, turn off
    // comparators and set ADCON1 value.
    /*
     MOVLW 0x07 ;
    MOVWF CMCON ; Turn off comparators
    MOVLW 0x0F ;
    MOVWF ADCON1 ; Set PORTF as digital I/O
     
     */
    CMCONbits.CM = 0x07;//Turn off comparators
    ADCON1bits.PCFG = 0x0F;//Set PORTF as digital I/O
    
    
    
    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */
}

void SetTime(time_t *newTime)
{
    currentTime = *newTime;
}
//void SetHourMin(int *newHour, int *newMin, int *seconds)
//{
//    currentHour = *newHour;
//    currentMinute = *newMin;
//    nextMinuteSeconds = currentTime + (60 - *seconds);
//}

void AddSecond()
{
    currentTime++;
//    if(currentTime >= nextMinuteSeconds)
//    {
//        nextMinuteSeconds = currentTime + 60;
//        currentMinute++;
//        if(currentMinute >= 60)
//        {
//            currentMinute = 0;
//            currentHour++;
//            if(currentHour >= 24)
//                currentHour = 0;
//        }
//    }
}

//uint8_t *GetHour()
//{
//    return &currentHour;
//}
//
//uint8_t *GetMinute()
//{
//    return &currentMinute;
//}
//
time_t *GetTime()
{
    return &currentTime;
}

// ======================= ���������� =============================

void SetAlarmState(uint8_t state, uint8_t blink)
{
    if(ledAlarmState == state && ledAlarmBlink == blink)
        return;
    ledAlarmState = state;
    ledAlarmBlink = blink;
    
    LATDbits.LATD0 = !ledAlarmState;
}
void SetFireState(uint8_t state, uint8_t blink)
{
    if(ledFireState == state && ledFireBlink == blink)
        return;
    ledFireState = state;
    ledFireBlink = blink;
    LATDbits.LATD1 = ledFireState ? 0 : 1;
}
void SetFailureState(uint8_t state, uint8_t blink)
{
    if(ledFailureState == state && ledFailureBlink == blink)
        return;
    ledFailureState = state;
    ledFailureBlink = blink;
    LATDbits.LATD2 = !ledFailureState;
}
void SetCrashState(uint8_t state, uint8_t blink)
{
    if(ledCrashState == state && ledCrashBlink == blink)
        return;
    ledCrashState = state;
    ledCrashBlink = blink;
    LATDbits.LATD3 = !ledCrashState;
}
void SetWorkState(uint8_t state, uint8_t blink)
{
    if(ledWorkState == state && ledWorkBlink == blink)
        return;
    ledWorkState = state;
    ledWorkBlink = blink;
    LATDbits.LATD4 = !ledWorkState;
}

void UpdateBlink(uint8_t globalBlink)
{
    if(ledAlarmState && ledAlarmBlink)
        LATDbits.LATD0 = !globalBlink;
    if(ledFireState && ledFireBlink)
        LATDbits.LATD1 = !globalBlink;
    if(ledFailureState && ledFailureBlink)
        LATDbits.LATD2 = !globalBlink;
    if(ledCrashState && ledCrashBlink)
        LATDbits.LATD3 = !globalBlink;
    if(ledWorkState && ledWorkBlink)
        LATDbits.LATD4 = !globalBlink;
}