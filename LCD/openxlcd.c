#include <p18cxxx.h>
#include <stdint.h>        /* For uint8_t definition */
#include "delays.h"
#include "xlcd.h"

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00



// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00


uint8_t CharLeftRight[] = 
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

uint8_t CharGradusC[] = 
{
    0b00011000,
    0b00011000,
    0b00000110,
    0b00001001,
    0b00001000,
    0b00001001,
    0b00000110,
    0b00000000,
};


uint8_t Progress[][8] =
{
    // ==== LEFT =======
    { // 0 left empty
        0b00011111,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00011111,
        0b00000000,
    },
    
     { // 1 left 1
        0b00011111,
        0b00010000,
        0b00010100,
        0b00010100,
        0b00010100,
        0b00010000,
        0b00011111,
        0b00000000,
    },
    { // 2 left 2
        0b00011111,
        0b00010000,
        0b00010110,
        0b00010110,
        0b00010110,
        0b00010000,
        0b00011111,
        0b00000000,
    },
    { // 3 left full
        0b00011111,
        0b00010000,
        0b00010111,
        0b00010111,
        0b00010111,
        0b00010000,
        0b00011111,
        0b00000000,
    },
   
    // ==== FULL =======
    
    { // 4 full
        0b00011111,
        0b00000000,
        0b00011111,
        0b00011111,
        0b00011111,
        0b00000000,
        0b00011111,
        0b00000000,
    },
    
    // ==== MIDDLE =======
    { // 5 middle 1
        0b00011111,
        0b00000000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00000000,
        0b00011111,
        0b00000000,
    },    
    { // 6 middle 2
        0b00011111,
        0b00000000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00000000,
        0b00011111,
        0b00000000,
    },    
    { // 7 middle 3
        0b00011111,
        0b00000000,
        0b00011100,
        0b00011100,
        0b00011100,
        0b00000000,
        0b00011111,
        0b00000000,
    },    
    { // 8 middle 4
        0b00011111,
        0b00000000,
        0b00011110,
        0b00011110,
        0b00011110,
        0b00000000,
        0b00011111,
        0b00000000,
    },    
    
    // ==== EMPTY =======
    
      
    { // 9 empty
        0b00011111,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00011111,
        0b00000000,
    },
    
    // ==== RIGHT =======
    
    { // 10 right empty
        0b00011111,
        0b00000001,
        0b00000001,
        0b00000001,
        0b00000001,
        0b00000001,
        0b00011111,
        0b00000000,
    },
    { // 11 right 1
        0b00011111,
        0b00000001,
        0b00010001,
        0b00010001,
        0b00010001,
        0b00000001,
        0b00011111,
        0b00000000,
    },
    { // 12 right 2
        0b00011111,
        0b00000001,
        0b00011001,
        0b00011001,
        0b00011001,
        0b00000001,
        0b00011111,
        0b00000000,
    },
    { // 13 right full
        0b00011111,
        0b00000001,
        0b00011101,
        0b00011101,
        0b00011101,
        0b00000001,
        0b00011111,
        0b00000000,
    },
    
};




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

uint8_t _displayfunction = 0;
uint8_t _displaycontrol = 0;
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
void OpenXLCD(unsigned char lcdtype, uint8_t cols, uint8_t lines, uint8_t dotsize)
{
    // 0b00111100 0x3C

    if (lines > 1) 
    {
      _displayfunction |= LCD_2LINE; // 0x08 0x00001000
    }    
    _numlines = lines;

    SetRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);      
    
      // for some 1 line displays you can select a 10 pixel high font
    if ((dotsize != LCD_5x8DOTS) && (lines == 1)) 
    {
      _displayfunction |= LCD_5x10DOTS;
    }
    
    
    
    
        // The data bits must be either a 8-bit port or the upper or
        // lower 4-bits of a port. These pins are made into inputs
#ifdef BIT8                             // 8-bit mode, use whole port
        _displayfunction |= LCD_8BITMODE; // = 0x00011000
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
        WriteCmdXLCD(LCD_FUNCTIONSET | _displayfunction);          // Function set cmd lcdtype

        // Turn the display on then off



        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(DOFF&CURSOR_OFF&BLINK_OFF);        // Display OFF/Blink OFF
        while(BusyXLCD());              // Wait if LCD busy
        _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;  
        DisplayOn();
        //WriteCmdXLCD(DON&CURSOR_ON&BLINK_ON);           // Display ON/Blink ON
        //WriteCmdXLCD(0b00000110);

        // Clear display
        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(LCD_CLEARDISPLAY);             // Clear display

        // Set entry mode inc, no shift
        while(BusyXLCD());              // Wait if LCD busy
        WriteCmdXLCD(SHIFT_DISP_LEFT);   // Entry Mode SHIFT_CUR_LEFT

        // Set DD Ram address to 0
        while(BusyXLCD());              // Wait if LCD busy
        
        DisplayCreateChar(CH_LEFT_RIGHT, CharLeftRight);
        DisplayCreateChar(CH_GRADUS_C, CharGradusC);
        
        
        while(BusyXLCD()); 
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
    while(BusyXLCD()); 
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
        
        case 'А':
            return 'A';
        case 'Б':
            return 0xA0;
        case 'В':
            return 'B';
        case 'Г':
            return 0xA1;
        case 'Д':
            return 0xE0;
        case 'Е':
            return 'E';
        case 'Ё':
            return 0xA2;
        case 'Ж':
            return 0xA3;
        case 'З':
            return 0xA4;
        case 'И':
            return 0xA5;
        case 'Й':
            return 0xA6;            
        case 'К':
            return 'K';
        case 'Л':
            return 0xA7;
        case 'М':
            return 'M';
        case 'Н':
            return 'H';
        case 'О':
            return 'O';
        case 'П':
            return 0xA8;
        case 'Р':
            return 'P';
        case 'С':
            return 'C';
        case 'Т':
            return 'T';
        case 'У':
            return 0xA9;
        case 'Ф':
            return 0xAA;
        case 'Х':
            return 'X';
        case 'Ц':
            return 0xE1;
        case 'Ч':
            return 0xAB;
        case 'Ш':
            return 0xAC;
        case 'Щ':
            return 0xE2;
        case 'Ъ':
            return 0xAD;
        case 'Ы':
            return 0xAE;
        case 'Ь':
            return 'b';
        case 'Э':
            return 0xAF;
        case 'Ю':
            return 0xB0;
        case 'Я':
            return 0xB1;
            
        case 'а': 
            return 'a';
        case 'б':
            return 0xB2;
        case 'в':
            return 0xB3;
        case 'г':
            return 0xB4;
        case 'д':
            return 0xE3;
        case 'е':
            return 'e';
        case 'ё':
            return 0xB5;
        case 'ж':
            return 0xB6;
        case 'з':
            return 0xB7;
        case 'и':
            return 0xB8;
        case 'й':
            return 0xB9;
        case 'к':
            return 0xBA;
        case 'л':
            return 0xBB;
        case 'м':
            return 0xBC;
        case 'н':
            return 0xBD;
        case 'о':
            return 'o';
        case 'п':
            return 0xBE;
        case 'р':
            return 'p';
        case 'с':
            return 'c';
        case 'т':
            return 0xBF;
        case 'у':
            return 'y';
        case 'ф':
            return 0xE4;
        case 'х':
            return 'x';
        case 'ц':
            return 0xE5;
        case 'ч':
            return 0xC0;
        case 'ш':
            return 0xC1;
        case 'щ':
            return 0xE6;
        case 'ъ':
            return 0xC2;
        case 'ы':
            return 0xC3;
        case 'ь':
            return 0xC4;
        case 'э':
            return 0xC5;
        case 'ю':
            return 0xC6;
        case 'я':
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

// Turn the display on/off (quickly)
void DisplayOff() 
{
  _displaycontrol &= ~LCD_DISPLAYON;
  WriteCmdXLCD(LCD_DISPLAYCONTROL | _displaycontrol);
}
void DisplayOn() 
{
  _displaycontrol |= LCD_DISPLAYON;
  WriteCmdXLCD(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void DisplayNoCursor() 
{
  _displaycontrol &= ~LCD_CURSORON;
  WriteCmdXLCD(LCD_DISPLAYCONTROL | _displaycontrol);
}
void DisplayCursor()
{
  _displaycontrol |= LCD_CURSORON;
  WriteCmdXLCD(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void DisplayNoBlink() 
{
  _displaycontrol &= ~LCD_BLINKON;
  WriteCmdXLCD(LCD_DISPLAYCONTROL | _displaycontrol);
}
void DisplayBlink() 
{
  _displaycontrol |= LCD_BLINKON;
  WriteCmdXLCD(LCD_DISPLAYCONTROL | _displaycontrol);
}



void DisplayPrintProgress(uint8_t colStart, uint8_t len, uint8_t row, uint8_t percent)
{
    if(colStart + len > SCREEN_WIDTH)
        len = SCREEN_WIDTH - colStart;
    if(len == 0)
        return;
    
    DisplayCreateChar(CH_PROGRESS_FULL, Progress[4]);    
    DisplayCreateChar(CH_PROGRESS_EMPTY, Progress[9]);    
    
    uint8_t buf[SCREEN_WIDTH + 1];
    //buf[sizeof(buf) - 1] = 0;
    uint8_t *str = buf;

    
    //putcXLCD('*');
    // вычисляем количество точек
    uint8_t dotsAll = (len - 2) * 5 + 6;
    //DisplayPrintUInt(dotsAll, DEC); //!!!
    //putcXLCD(' ');
    if(percent > 100)
        percent = 100;
    uint8_t dotsFill = (percent / 100.) * dotsAll;
    //DisplayPrintUInt(dotsFill, DEC); //!!!
//putcXLCD('*');
    // загружаем в знакогенератор
    
//putcXLCD('*');    
    // Левая граница
    //uint8_t ind = dotsFill < 3 ? dotsFill : 3;    
    //DisplayCreateChar(CH_PROGRESS_LEFT, Progress[ind]);
    
    //putcXLCD(CH_PROGRESS_LEFT);
    // полностью заполненные элементы
    uint8_t cnt;
    if(dotsAll - dotsFill <= 3) // Если всё заполнено кроме концевой
    {
//        putcXLCD('*'); 
//        putcXLCD('1');
        DisplayCreateChar(CH_PROGRESS_LEFT, Progress[3]);
        *str = CH_PROGRESS_LEFT;
        str++;
        //putcXLCD(CH_PROGRESS_LEFT);
        cnt = len - 2;
        for(uint8_t i = 0; i < cnt; i++)
        {
            *str = CH_PROGRESS_FULL;
            str++;
        }
        DisplayCreateChar(CH_PROGRESS_RIGHT, Progress[10 + 3 - (dotsAll - dotsFill)]);
        *str = CH_PROGRESS_RIGHT;
        str++;
    }
    else if(dotsFill <= 3) // Если всё пусто кроме левой границы
    {
        //putcXLCD('*'); 
        //putcXLCD('2');
        DisplayCreateChar(CH_PROGRESS_LEFT, Progress[dotsFill]);
        *str = CH_PROGRESS_LEFT;
        str++;
        
        cnt = len - 2;
        for(uint8_t i = 0; i < cnt; i++)
        {
            *str = CH_PROGRESS_EMPTY;
            str++;
        }
        DisplayCreateChar(CH_PROGRESS_RIGHT, Progress[10]);
        *str = CH_PROGRESS_RIGHT;
        str++;
    }
    else
    {
        
        DisplayCreateChar(CH_PROGRESS_LEFT, Progress[3]);
        *str = CH_PROGRESS_LEFT;
        str++;
        
        
        
        cnt = dotsFill - 3;
        uint8_t printed = 0;

        while(cnt >= 5)
        {
            *str = CH_PROGRESS_FULL;
            str++;
            cnt -= 5;
            printed++;
        }
        if(cnt > 0)
        {
            DisplayCreateChar(CH_PROGRESS_MIDDLE, Progress[5 + cnt - 1]);
            *str = CH_PROGRESS_MIDDLE;
            str++;
            printed++;
        }
        if(printed < len - 2)
        {
            cnt = len - 2 - printed;
            for(uint8_t i = 0; i < cnt; i++)
            {
                *str = CH_PROGRESS_EMPTY;
                str++;
            }
        }
        DisplayCreateChar(CH_PROGRESS_RIGHT, Progress[10]);
        *str = CH_PROGRESS_RIGHT;  
        str++;
             
    } 
    *str = 0;
    DisplaySetCursorPos(colStart, row);
    DisplayPrintStr(buf);
}