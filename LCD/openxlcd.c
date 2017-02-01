#include <p18cxxx.h>
#include <stdint.h>        /* For uint8_t definition */
#include "delays.h"
#include "xlcd.h"

// flags for function set
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00


// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

uint8_t _initialized;

uint8_t _numlines;
uint8_t _row_offsets[4];

void SetRowOffsets(int row0, int row1, int row2, int row3)
{
  _row_offsets[0] = row0;
  _row_offsets[1] = row1;
  _row_offsets[2] = row2;
  _row_offsets[3] = row3;
}
/********************************************************************
*       Function Name:  OpenXLCD                                    *
*       Return Value:   void                                        *
*       Parameters:     lcdtype: sets the type of LCD (lines)       *
*       Description:    This routine configures the LCD. Based on   *
*                       the Hitachi HD44780 LCD controller. The     *
*                       routine will configure the I/O pins of the  *
*                       microcontroller, setup the LCD for 4- or    *
*                       8-bit mode and clear the display. The user  *
*                       must provide three delay routines:          *
*                       DelayFor18TCY() provides a 18 Tcy delay     *
*                       DelayPORXLCD() provides at least 15ms delay *
*                       DelayXLCD() provides at least 5ms delay     *
********************************************************************/
void OpenXLCD(unsigned char lcdtype, uint8_t cols, uint8_t lines)
{
    uint8_t _displayfunction = 0;
    if (lines > 1) {
      _displayfunction |= LCD_2LINE;
    }    
    _numlines = lines;

    SetRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);      
    
    
    
    
        // The data bits must be either a 8-bit port or the upper or
        // lower 4-bits of a port. These pins are made into inputs
#ifdef BIT8                             // 8-bit mode, use whole port
        DATA_PORT = 0;
        TRIS_DATA_PORT = 0x00;
#else                                   // 4-bit mode
#ifdef UPPER                            // Upper 4-bits of the port
        DATA_PORT &= 0x0f;
        TRIS_DATA_PORT &= 0x0F;
#else                                   // Lower 4-bits of the port
        DATA_PORT &= 0xf0;
        TRIS_DATA_PORT &= 0xF0;
#endif
#endif
        TRIS_RW = 0;                    // All control signals made outputs
        TRIS_RS = 0;
        TRIS_E = 0;
        RW_PIN = 0;                     // R/W pin made low
        RS_PIN = 0;                     // Register select pin made low
        E_PIN = 0;                      // Clock pin made low

        // Delay for 15ms to allow for LCD Power on reset
        DelayPORXLCD();
 //-------------------reset procedure through software----------------------       
		 WriteCmdXLCD(0x30);
			Delay10KTCYx(0x05);

		 WriteCmdXLCD(0x30);
			Delay10KTCYx(0x01);


		 WriteCmdXLCD(0x32);
		while( BusyXLCD() );
//------------------------------------------------------------------------------------------


        // Set data interface width, # lines, font
        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(lcdtype);          // Function set cmd

        // Turn the display on then off



        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(DOFF&CURSOR_OFF&BLINK_OFF);        // Display OFF/Blink OFF
        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(DON&CURSOR_ON&BLINK_ON);           // Display ON/Blink ON
        //WriteCmdXLCD(0b00000110);

        // Clear display
        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(LCD_CLEARDISPLAY);             // Clear display

        // Set entry mode inc, no shift
        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(SHIFT_DISP_LEFT);   // Entry Mode SHIFT_CUR_LEFT

        // Set DD Ram address to 0
        while(BusyXLCD());              // Wait if LCD busy
        SetDDRamAddr(LCD_SETDDRAMADDR);                // Set Display data ram address to 0

        return;
}

void DisplaySetCursorPos(uint8_t col, uint8_t row)
{
    const uint8_t max_lines = sizeof(_row_offsets) / sizeof(*_row_offsets);
    if ( row >= max_lines ) 
    {
      row = max_lines - 1;    // we count rows starting w/0
    }
    if ( row >= _numlines ) 
    {
      row = _numlines - 1;    // we count rows starting w/0
    }

    SetDDRamAddr(col + _row_offsets[row]);
}


// These commands scroll the display without changing the RAM
void DisplayScrollLeft(void) 
{
  WriteCmdXLCD(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void DisplayScrollRight(void) 
{
  WriteCmdXLCD(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}


// Allows us to fill the first 8 CGRAM locations
// with custom characters
void DisplayCreateChar(uint8_t location, uint8_t charmap[]) 
{
    location &= 0x7; // we only have 8 locations 0-7
    SetCGRamAddr(location << 3);
    for (int i=0; i<8; i++) 
    {
        WriteDataXLCD(charmap[i]);
    }
}

char RecodeSymbol(char c)
{
    if(c <= 0x7f)
        return c;
    switch(c)
    {
        
        case '�':
            return 'A';
        case '�':
            return 0xA0;
        case '�':
            return 'B';
        case '�':
            return 0xA1;
        case '�':
            return 0xE0;
        case '�':
            return 'E';
        case '�':
            return 0xA2;
        case '�':
            return 0xA3;
        case '�':
            return 0xA4;
        case '�':
            return 0xA5;
        case '�':
            return 0xA6;            
        case '�':
            return 'K';
        case '�':
            return 0xA7;
        case '�':
            return 'M';
        case '�':
            return 'H';
        case '�':
            return 'O';
        case '�':
            return 0xA8;
        case '�':
            return 'P';
        case '�':
            return 'C';
        case '�':
            return 'T';
        case '�':
            return 0xA9;
        case '�':
            return 0xAA;
        case '�':
            return 'X';
        case '�':
            return 0xE1;
        case '�':
            return 0xAB;
        case '�':
            return 0xAC;
        case '�':
            return 0xE2;
        case '�':
            return 0xAD;
        case '�':
            return 0xAE;
        case '�':
            return 'b';
        case '�':
            return 0xAF;
        case '�':
            return 0xB0;
        case '�':
            return 0xB1;
            
        case '�': 
            return 'a';
        case '�':
            return 0xB2;
        case '�':
            return 0xB3;
        case '�':
            return 0xB4;
        case '�':
            return 0xE3;
        case '�':
            return 'e';
        case '�':
            return 0xB5;
        case '�':
            return 0xB6;
        case '�':
            return 0xB7;
        case '�':
            return 0xB8;
        case '�':
            return 0xB9;
        case '�':
            return 0xBA;
        case '�':
            return 0xBB;
        case '�':
            return 0xBC;
        case '�':
            return 0xBD;
        case '�':
            return 'o';
        case '�':
            return 0xBE;
        case '�':
            return 'p';
        case '�':
            return 'c';
        case '�':
            return 0xBF;
        case '�':
            return 'y';
        case '�':
            return 0xE4;
        case '�':
            return 'x';
        case '�':
            return 0xE5;
        case '�':
            return 0xC0;
        case '�':
            return 0xC1;
        case '�':
            return 0xE6;
        case '�':
            return 0xC2;
        case '�':
            return 0xC3;
        case '�':
            return 0xC4;
        case '�':
            return 0xC5;
        case '�':
            return 0xC6;
        case '�':
            return 0xC7;
            
        case '�':
            return 0xC8;
        case '�':
            return 0xC9;
              
            
            
        case '�':
            return 0xFD;       
        case '�':
            return 0xFE;        
            
            
        case '�':
            return 0xCA;       
        case '�':
            return 0xCB;    
            
        default:
            return c;
    }
}