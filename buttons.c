#include <pic18f6720.h>


#include "buttons.h"

#define BTN_LAT_COL1 LATAbits.LA1
#define BTN_LAT_COL2 LATAbits.LA2
#define BTN_LAT_COL3 LATAbits.LA3
#define BTN_LAT_COL4 LATCbits.LC0



const char *ButtonNames[] = 
{
    "ARM",
    "DISARM",
    "BPS",
    "TRBL",
    "MEM",
    "LEFT",
    "1",
    "4",
    "7",
    "CLR",
    "PRG",
    "2",
    "5",
    "8",
    "0",                
    "RIGHT",
    "3",
    "6",
    "9",
    "ENT",
    "Нет"           
};
void InitButtons()
{
    // Button scaner
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
    TRISBbits.RB2 = 1;
    TRISBbits.RB3 = 1;
    TRISBbits.RB4 = 1;
    
    INTCON2bits.RBPU = 0;
    
    TRISAbits.RA1 = 0;
    TRISAbits.RA2 = 0;
    TRISAbits.RA3 = 0;
    TRISCbits.RC0 = 0;
    
    
    for(uint8_t i = 0; i < BUTTONS_COUNT; i++)
        ButtonStates[i] = BUTTON_RELEASED;
}

char* GetButtonName(Buttons button)
{
    return ButtonNames[button];
}

void SetColumnPin(uint8_t col)
{
    switch(col)
    {
        case 0:
            BTN_LAT_COL1 = 0;
            BTN_LAT_COL2 = 1;
            BTN_LAT_COL3 = 1;
            BTN_LAT_COL4 = 1;  
            break;
        case 1:
            BTN_LAT_COL1 = 1;
            BTN_LAT_COL2 = 0;
            BTN_LAT_COL3 = 1;
            BTN_LAT_COL4 = 1;  
            break;
        case 2:
            BTN_LAT_COL1 = 1;
            BTN_LAT_COL2 = 1;
            BTN_LAT_COL3 = 0;
            BTN_LAT_COL4 = 1;  
            break;
        case 3:
            BTN_LAT_COL1 = 1;
            BTN_LAT_COL2 = 1;
            BTN_LAT_COL3 = 1;
            BTN_LAT_COL4 = 0;  
            break;
    }
}

uint8_t CheckRow(uint8_t col, uint8_t row)
{
    uint8_t btnId = col * BUTTONS_ROWS + row;
    uint8_t btnVal = PORTB & (1 << row);
    if(btnVal != ButtonStates[btnId])
    {
        ButtonStates[btnId] = btnVal;
        return btnId;
    }
    return BTN_NONE;
}

uint8_t IsButtonChanged()
{
    for(uint8_t col = 0; col < BUTTONS_COLS; col++)
    {
        SetColumnPin(col);

        for(uint8_t row = 0; row < BUTTONS_ROWS; row++)
        {
            uint8_t butChanged = CheckRow(col, row);
            if(butChanged != BTN_NONE)
                return butChanged;
        }
        
        
    
    }
    return BTN_NONE;    
}