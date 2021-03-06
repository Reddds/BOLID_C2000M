#ifndef __XLCD_H
#define __XLCD_H
#include "p18cxxx.h"
#include "Print.h"
/* PIC18 XLCD peripheral routines.
 *
 *   Notes:
 *      - These libraries routines are written to support the
 *        Hitachi HD44780 LCD controller.
 *      - The user must define the following items:
 *          - The LCD interface type (4- or 8-bits)
 *          - If 4-bit mode
 *              - whether using the upper or lower nibble
 *          - The data port
 *              - The tris register for data port
 *              - The control signal ports and pins
 *              - The control signal port tris and pins
 *          - The user must provide three delay routines:
 *              - DelayFor18TCY() provides a 18 Tcy delay
 *              - DelayPORXLCD() provides at least 15ms delay
 *              - DelayXLCD() provides at least 5ms delay
 */

#define SCREEN_WIDTH 16u
/* Interface type 8-bit or 4-bit
 * For 8-bit operation uncomment the #define BIT8
 */
#define BIT8

/* When in 4-bit interface define if the data is in the upper
 * or lower nibble.  For lower nibble, comment the #define UPPER
 */
/* #define UPPER */

/* DATA_PORT defines the port to which the LCD data lines are connected */
#define DATA_PORT           PORTF
#define TRIS_DATA_PORT 		TRISF

/* CTRL_PORT defines the port where the control lines are connected.
 * These are just samples, change to match your application.
 */
#define RW_PIN              LATDbits.LATD6          /* PORT for RW */
#define TRIS_RW             TRISDbits.TRISD6        /* TRIS for RW */

#define RS_PIN              LATDbits.LATD5   		/* PORT for RS */
#define TRIS_RS             TRISDbits.TRISD5    	/* TRIS for RS */

#define E_PIN               LATDbits.LATD7  		/* PORT for D  */
#define TRIS_E              TRISDbits.TRISD7    	/* TRIS for E  */ 

/* Display ON/OFF Control defines */
#define DON         0b00001111  /* Display on      */
#define DOFF        0b00001011  /* Display off  0b00001011   */
#define DISPLAY_CLEAR 0b00000001
#define CURSOR_ON   0b00001111  /* Cursor on       */
#define CURSOR_OFF  0b00001101  /* Cursor off      */
#define BLINK_ON    0b00001111  /* Cursor Blink    */
#define BLINK_OFF   0b00001110  /* Cursor No Blink */

/* Cursor or Display Shift defines */
#define SHIFT_CUR_LEFT    0b00000100  /* Cursor shifts to the left   */
#define SHIFT_CUR_RIGHT   0b00000101  /* Cursor shifts to the right  */
#define SHIFT_DISP_LEFT   0b00000110  /* Display shifts to the left  */
#define SHIFT_DISP_RIGHT  0b00000111  /* Display shifts to the right */

/* Function Set defines */
#define FOUR_BIT   0b00101100  /* 4-bit Interface               */
#define EIGHT_BIT  0b00111100  /* 8-bit Interface               */
#define LINE_5X7   0b00110000  /* 5x7 characters, single line   */
#define LINE_5X10  0b00110100  /* 5x10 characters               */
#define LINES_5X7  0b00111000  /* 5x7 characters, multiple line */
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// commands
#define LCD_CLEARDISPLAY    0x01u
#define LCD_RETURNHOME      0x02u
#define LCD_ENTRYMODESET    0x04u
#define LCD_DISPLAYCONTROL  0x08u
#define LCD_CURSORSHIFT     0x10u
#define LCD_FUNCTIONSET     0x20u
#define LCD_SETCGRAMADDR    0x40u
#define LCD_SETDDRAMADDR    0x80u



#define CH_LEFT_RIGHT 0x00
#define CH_GRADUS_C 0x01

#define CH_PROGRESS_LEFT 0x02
#define CH_PROGRESS_FULL 0x03
#define CH_PROGRESS_MIDDLE 0x04
#define CH_PROGRESS_EMPTY 0x05
#define CH_PROGRESS_RIGHT 0x06

#define CH_CUSTOM_SYMBOL 0x07

#define CH_ARROW_LEFT_TOP 0x80
#define CH_ARROW_RIGHT_TOP 0x81
#define CH_ARROW_LEFT_BOTTOM 0x82
#define CH_ARROW_RIGHT_BOTTOM 0x83

#define CH_10 0x7B
#define CH_12 0x7C
#define CH_15 0x7D
#define CH_ENTER 0x7E
#define CH_1_4 0xF0
#define CH_1_3 0xF1
#define CH_1_2 0xF2
#define CH_3_4 0xF3
#define CH_ARROW_UP 0xD9
#define CH_ARROW_DOWN 0xDA

#define CH_HOME 0xF4



#ifdef _OMNI_CODE_
#define PARAM_SCLASS
#else
#define PARAM_SCLASS auto
#endif

#ifndef MEM_MODEL
#ifdef _OMNI_CODE_
#define MEM_MODEL
#else
#define MEM_MODEL far  /* Change this to near for small memory model */
#endif
#endif

/* OpenXLCD
 * Configures I/O pins for external LCD cols, lines
 */
void OpenXLCD(PARAM_SCLASS unsigned char, PARAM_SCLASS unsigned char, PARAM_SCLASS unsigned char, uint8_t dotsize);

/* SetCGRamAddr
 * Sets the character generator address
 */
void SetCGRamAddr(PARAM_SCLASS unsigned char);

/* SetDDRamAddr
 * Sets the display data address
 */
void SetDDRamAddr(PARAM_SCLASS unsigned char);

/* BusyXLCD
 * Returns the busy status of the LCD
 */
unsigned char BusyXLCD(void);

/* ReadAddrXLCD
 * Reads the current address
 */
unsigned char ReadAddrXLCD(void);

/* ReadDataXLCD
 * Reads a byte of data
 */
char ReadDataXLCD(void);

/* WriteCmdXLCD
 * Writes a command to the LCD
 */
void WriteCmdXLCD(PARAM_SCLASS unsigned char);

/* WriteDataXLCD
 * Writes a data byte to the LCD
 */
void WriteDataXLCD(PARAM_SCLASS char);

/* putcXLCD
 * A putc is a write
 */
#define putcXLCD(c) WriteDataXLCD(c)

/* putsXLCD
 * Writes a string of characters to the LCD
 */
uint8_t putsXLCD(PARAM_SCLASS const char *);

/* putrsXLCD
 * Writes a string of characters in ROM to the LCD
 */
void putrsXLCD(const char *);

void InitSymbol(uint8_t id);


void DisplayCreateChar(uint8_t location, uint8_t charmap[]);

/**
 * Set cursor pos 
 * @param column
 * @param row
 */
void DisplaySetCursorPos(PARAM_SCLASS unsigned char, PARAM_SCLASS unsigned char);


void DisplayScrollLeft(void);
void DisplayScrollRight(void);

#define DisplayClear() WriteCmdXLCD(LCD_CLEARDISPLAY)
#define DisplayHome() WriteCmdXLCD(LCD_RETURNHOME)

char RecodeSymbol(char c);

void DisplayOff();
void DisplayOn();
void DisplayNoBlink();
void DisplayBlink();
void DisplayNoCursor();
void DisplayCursor();

/**
 * ������ ����� ���������
 * @param colStart  ��������� �������
 * @param len       ������
 * @param row       ���
 * @param percent   �������� � ���������
 */
void DisplayPrintProgress(uint8_t colStart, uint8_t len, uint8_t row, uint8_t percent);

/* User defines these routines according to the oscillator frequency */
extern void DelayFor18TCY(void);
extern void DelayPORXLCD(void);
extern void DelayXLCD(void);


#endif
