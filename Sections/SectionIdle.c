#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "SectionIdle.h"
#include "../i2c/i2c.h"
#include "../LCD/xlcd.h"
#include "../buttons.h"
#include "../interrupts.h"
#include "../ParametersController.h"


// Конфиг

//Конфиг главного экрана
// * 
// * Позиция (Кол, ряд) / Тип / Значение

typedef enum
{
    MIT_LITERAL, // Строка текста
    MIT_PARAM, // Значение параметра
    MIT_SHORT, // Значение параметра с коротким названием
    MIT_FULL, // Значение параметра с длинным названием        
}MainItemTypes;

//typedef enum 
//{
//    VS_ROOT,
//    VS_TIME
//}ViewStates;
//ViewStates _currentState;

typedef struct 
{
    uint8_t Column;
    uint8_t Row;
    MainItemTypes Type;
//    void* Value;
    union Value
    {
        const char* str;
        uint8_t paramId;
    }Value;

}MainScreenItem;


uint8_t mainParamCount = 5;

MainScreenItem MainConfig[]=
{
    {1, 0, MIT_LITERAL, {"Улица:"}},
    {8, 0, MIT_PARAM, {5}},
    
    {1, 1, MIT_LITERAL, {"Дом:"}},
    {6, 1, MIT_PARAM, {0}},
    {11, 1, MIT_PARAM, {1}},
    
};


bool isRoot = false;



#define RBUF_LEN 0x20


unsigned char arrayrd[RBUF_LEN];

void IdleStart()
{
//    MainConfig[0].Column = 1;
//    MainConfig[0].Row = 0;
//    MainConfig[0].Type = MIT_LITERAL;
//    MainConfig[0].Value.str = "Улица:";
    
    //= {1, 0, MIT_LITERAL};
    
    
    
    isRoot = true;
    
    DisplayClear();
    DisplayPrintSymbol(CH_HOME);
    
    for(uint8_t i = 0; i < mainParamCount; i++)
    {
        DisplaySetCursorPos(MainConfig[i].Column, MainConfig[i].Row);
        switch(MainConfig[i].Type)
        {
            case MIT_LITERAL:
            {
                DisplayPrintStr(MainConfig[i].Value.str);
            }
                break;
            case MIT_PARAM:               
            {
                PrintParameter(MainConfig[i].Value.paramId, -1, -1, PPN_NONE);
            }
                break;
            case MIT_SHORT:               
            {
                PrintParameter(MainConfig[i].Value.paramId, -1, -1, PPN_SHORT);
            }
                break;
            case MIT_FULL:               
            {
                PrintParameter(MainConfig[i].Value.paramId, -1, -1, MIT_FULL);
            }
                break;
        }
    }
    
    
    //DisplayPrintStr("Главный");
    //DisplayHome();
    //DisplayBlink();
    //DisplayCursor();
}


#define EXT_MEM_CHIP_SIZE 0x10000

uint8_t curRow = 0;
uint8_t curCol = 0;
bool curBlink = false;
bool curCur = false;

//unsigned char arraywr[] = {1,2,3,4,5,6,7,8,0};

void IdleOnButton(uint8_t button)
{
    if (ButtonStates[button] != BUTTON_PRESSED)
        return;
    switch (button)
    {
        case BTN_PRG: // Слив памяти 
        {
            int8_t res = EESequentialRead(0xA0, 0x00, arrayrd, 5);

            DisplayClear();
            DisplayPrintInt(-3, DEC);
            DisplayPrintChar(':');
            DisplayPrintInt(res, DEC);
            DisplayPrintChar(':');
            for (uint8_t i = 0; i < 5; i++)
            {
                DisplayPrintUInt(arrayrd[i], DEC);
                DisplayPrintChar(' ');
            }

            //DisplayPrintStr( "АБВГОДЁЖДИЙКЛМНО" );
            DisplaySetCursorPos(0, 1);

            for (uint8_t i = 0; i < 5; i++)
            {
                DisplayPrintUInt(arrayrd[i], HEX);
                DisplayPrintChar(' ');
            }









            //PortWrite(arraywr, 9);
            for (uint24_t i = 0; i < EXT_MEM_CHIP_SIZE; i += RBUF_LEN)
            {

                EESequentialRead(0xA1, i, arrayrd, RBUF_LEN);
                PortWrite(arrayrd, RBUF_LEN);
            }
        }
            break;
        case BTN_2: // курсор вверх
        {
            if(curRow == 0)
                break;
            curRow--;
            DisplaySetCursorPos(curCol, curRow);
        }
            break;
        case BTN_8: // курсор Вниз
        {
            if(curRow == 1)
                break;
            curRow++;
            DisplaySetCursorPos(curCol, curRow);
        }
            break;
        case BTN_4: // курсор влево
        {
            if(curCol == 0)
                break;
            curCol--;
            DisplaySetCursorPos(curCol, curRow);
        }
            break;
        case BTN_6: // курсор вправо
        {
            if(curCol == 15)
                break;
            curCol++;
            DisplaySetCursorPos(curCol, curRow);
        }
            break;
            
            
        case BTN_5: // Мигание вкл-выкл
        {
            if(curBlink)
            {
                DisplayNoBlink();
                curBlink = false;
            }
            else                
            {
                DisplayBlink();
                curBlink = true;
            }
        }
            break;
        case BTN_BPS: // Курсор вкл-выкл
        {
            if(curCur)
            {
                DisplayNoCursor();
                curCur = false;
            }
            else                
            {
                DisplayCursor();
                curCur = true;
            }
        }
            break;
            
    }
}

bool IdleIsRoot()
{
    return true;
}