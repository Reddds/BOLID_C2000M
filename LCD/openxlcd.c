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
        
        case 'À':
            return 'A';
        case 'Á':
            return 0xA0;
        case 'Â':
            return 'B';
        case 'Ã':
            return 0xA1;
        case 'Ä':
            return 0xE0;
        case 'Å':
            return 'E';
        case '¨':
            return 0xA2;
        case 'Æ':
            return 0xA3;
        case 'Ç':
            return 0xA4;
        case 'È':
            return 0xA5;
        case 'É':
            return 0xA6;            
        case 'Ê':
            return 'K';
        case 'Ë':
            return 0xA7;
        case 'Ì':
            return 'M';
        case 'Í':
            return 'H';
        case 'Î':
            return 'O';
        case 'Ï':
            return 0xA8;
        case 'Ð':
            return 'P';
        case 'Ñ':
            return 'C';
        case 'Ò':
            return 'T';
        case 'Ó':
            return 0xA9;
        case 'Ô':
            return 0xAA;
        case 'Õ':
            return 'X';
        case 'Ö':
            return 0xE1;
        case '×':
            return 0xAB;
        case 'Ø':
            return 0xAC;
        case 'Ù':
            return 0xE2;
        case 'Ú':
            return 0xAD;
        case 'Û':
            return 0xAE;
        case 'Ü':
            return 'b';
        case 'Ý':
            return 0xAF;
        case 'Þ':
            return 0xB0;
        case 'ß':
            return 0xB1;
            
        case 'à': 
            return 'a';
        case 'á':
            return 0xB2;
        case 'â':
            return 0xB3;
        case 'ã':
            return 0xB4;
        case 'ä':
            return 0xE3;
        case 'å':
            return 'e';
        case '¸':
            return 0xB5;
        case 'æ':
            return 0xB6;
        case 'ç':
            return 0xB7;
        case 'è':
            return 0xB8;
        case 'é':
            return 0xB9;
        case 'ê':
            return 0xBA;
        case 'ë':
            return 0xBB;
        case 'ì':
            return 0xBC;
        case 'í':
            return 0xBD;
        case 'î':
            return 'o';
        case 'ï':
            return 0xBE;
        case 'ð':
            return 'p';
        case 'ñ':
            return 'c';
        case 'ò':
            return 0xBF;
        case 'ó':
            return 'y';
        case 'ô':
            return 0xE4;
        case 'õ':
            return 'x';
        case 'ö':
            return 0xE5;
        case '÷':
            return 0xC0;
        case 'ø':
            return 0xC1;
        case 'ù':
            return 0xE6;
        case 'ú':
            return 0xC2;
        case 'û':
            return 0xC3;
        case 'ü':
            return 0xC4;
        case 'ý':
            return 0xC5;
        case 'þ':
            return 0xC6;
        case 'ÿ':
            return 0xC7;
            
        case '«':
            return 0xC8;
        case '»':
            return 0xC9;
              
            
            
        case '§':
            return 0xFD;       
        case '¶':
            return 0xFE;        
            
            
        case '“':
            return 0xCA;       
        case '”':
            return 0xCB;    
            
        default:
            return c;
    }
}