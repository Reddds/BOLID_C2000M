#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "SectionIdle.h"
#include "../ModbusRtu.h"
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


typedef struct
{
    Buttons Button;
    uint8_t ParamId;
    // Количество значений, которые будут переключаться по кругу 1-2-3
    // 0 - кнопка ничего не делает
    uint8_t ValuesCount;
    uint16_t Value1;
    uint16_t Value2;
    uint16_t Value3;
}QuickButtonParam;


#define QUICK_BUTTON_COUNT 15
QuickButtonParam QuickButtonParams[] = 
{
    {BTN_ARM,    4, 1,  MODBUS_TRUE,            0, 0}, // 0
    {BTN_DISARM, 4, 1, MODBUS_FALSE,            0, 0}, // 1
    {BTN_BPS,    4, 2,  MODBUS_TRUE, MODBUS_FALSE, 0}, // 2
    {BTN_TRBL,   0, 0,            0,            0, 0}, // 3
    {BTN_MEM,    0, 0,            0,            0, 0}, // 4
    {BTN_1,      0, 0,            0,            0, 0}, // 5
    {BTN_2,      0, 0,            0,            0, 0}, // 6
    {BTN_3,      0, 0,            0,            0, 0}, // 7
    {BTN_4,      0, 0,            0,            0, 0}, // 8
    {BTN_5,      0, 0,            0,            0, 0}, // 9
    {BTN_6,      0, 0,            0,            0, 0}, // 10
    {BTN_7,      0, 0,            0,            0, 0}, // 11
    {BTN_8,      0, 0,            0,            0, 0}, // 12
    {BTN_9,      0, 0,            0,            0, 0}, // 13
    {BTN_0,      0, 0,            0,            0, 0}, // 14
};



typedef enum 
{
    VS_ROOT,
    VS_PRESS_BUTTON, // Предлагает нажать на кнопку, чтобы посмотреть события на ней        
    VS_BUTTON_INFO, // Информация о кнопках     
}ViewStates;

ViewStates _currentSiState;
uint8_t _currentButtonInfo;



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

void IdleDisplayRedraw()
{
    DisplayClear();
    
    
    
    switch(_currentSiState)
    {
        case VS_ROOT:
        {
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
        }
        break;
        case VS_PRESS_BUTTON:
        {
            DisplayPrintStr("Нажми на кнопку,");
            DisplaySetCursorPos(0, 1);
            DisplayPrintStr("покажет событие");
        }
        break;
        case VS_BUTTON_INFO:
        {
            DisplayPrintSymbol(CH_LEFT_RIGHT);
            DisplayPrintStr(ButtonNames[QuickButtonParams[_currentButtonInfo].Button]);
            DisplayPrintStr(": ");
            if(QuickButtonParams[_currentButtonInfo].ValuesCount == 0)
            {
                DisplayPrintStr("Пусто");
                break;
            }
            char buf[9];
            GetParameterName(QuickButtonParams[_currentButtonInfo].ParamId, buf);
            DisplayPrintStr(buf);
            
            DisplaySetCursorPos(0, 1);
            
            PrintParameterByValue(QuickButtonParams[_currentButtonInfo].ParamId, QuickButtonParams[_currentButtonInfo].Value1, -1, -1, PPN_NONE);
            if(QuickButtonParams[_currentButtonInfo].ValuesCount > 1)
            {
                DisplayPrintStr(" - ");
                PrintParameterByValue(QuickButtonParams[_currentButtonInfo].ParamId, QuickButtonParams[_currentButtonInfo].Value2, -1, -1, PPN_NONE);
                
                if(QuickButtonParams[_currentButtonInfo].ValuesCount > 2)
                {
                    DisplayPrintStr(" - ");
                    PrintParameterByValue(QuickButtonParams[_currentButtonInfo].ParamId, QuickButtonParams[_currentButtonInfo].Value3, -1, -1, PPN_NONE);                    
                }
            }
        }
        break;
    }
    
    

}

void IdleStart()
{
//    MainConfig[0].Column = 1;
//    MainConfig[0].Row = 0;
//    MainConfig[0].Type = MIT_LITERAL;
//    MainConfig[0].Value.str = "Улица:";
    
    //= {1, 0, MIT_LITERAL};
    
    
    
    _currentSiState = VS_ROOT;
    IdleDisplayRedraw();
    
    
    
    //DisplayPrintStr("Главный");
    //DisplayHome();
    //DisplayBlink();
    //DisplayCursor();
}




uint8_t curRow = 0;
uint8_t curCol = 0;
bool curBlink = false;
bool curCur = false;

//unsigned char arraywr[] = {1,2,3,4,5,6,7,8,0};

void QuickButtonPress(uint8_t id)
{
    if(QuickButtonParams[id].ValuesCount == 0)
        return;
    
    DisplayClear();
    char buf[9];
    GetParameterName(QuickButtonParams[id].ParamId, buf);
    DisplayPrintStr(" = ");
                       
    
    if(QuickButtonParams[id].ValuesCount == 1)
    {
        SetParameterValue(QuickButtonParams[id].ParamId, QuickButtonParams[id].Value1);
        PrintParameter(QuickButtonParams[id].ParamId, -1, -1, PPN_NONE); 
        return;
    }
//    if(QuickButtonParams[id].ValuesCount >= 2)
//    {
        if(GetParameterValue(QuickButtonParams[id].ParamId) == QuickButtonParams[id].Value1)
        {
            SetParameterValue(QuickButtonParams[id].ParamId, QuickButtonParams[id].Value2);
            PrintParameter(QuickButtonParams[id].ParamId, -1, -1, PPN_NONE); 
            return;
        }
        if(GetParameterValue(QuickButtonParams[id].ParamId) == QuickButtonParams[id].Value2)
        {
            if(QuickButtonParams[id].ValuesCount == 2)
                SetParameterValue(QuickButtonParams[id].ParamId, QuickButtonParams[id].Value1);
            else // 3
                SetParameterValue(QuickButtonParams[id].ParamId, QuickButtonParams[id].Value3);
            PrintParameter(QuickButtonParams[id].ParamId, -1, -1, PPN_NONE); 
            return;
        }
        if(QuickButtonParams[id].ValuesCount == 3 
                && GetParameterValue(QuickButtonParams[id].ParamId) == QuickButtonParams[id].Value3)
        {
            SetParameterValue(QuickButtonParams[id].ParamId, QuickButtonParams[id].Value1);
            PrintParameter(QuickButtonParams[id].ParamId, -1, -1, PPN_NONE); 
            return;
        }
        SetParameterValue(QuickButtonParams[id].ParamId, QuickButtonParams[id].Value1);
        PrintParameter(QuickButtonParams[id].ParamId, -1, -1, PPN_NONE); 
//    }

}


void IdleOnButton(uint8_t button)
{
    if (ButtonStates[button] != BUTTON_PRESSED)
        return;
    
    //IdleStart();
    
    switch (button)
    {
//        case BTN_PRG: // Слив памяти 
//        {
//            int8_t res = EESequentialRead(0xA0, 0x00, arrayrd, 5);
//
//            DisplayClear();
//            DisplayPrintInt(-3, DEC);
//            DisplayPrintChar(':');
//            DisplayPrintInt(res, DEC);
//            DisplayPrintChar(':');
//            for (uint8_t i = 0; i < 5; i++)
//            {
//                DisplayPrintUInt(arrayrd[i], DEC);
//                DisplayPrintChar(' ');
//            }
//
//            //DisplayPrintStr( "АБВГОДЁЖДИЙКЛМНО" );
//            DisplaySetCursorPos(0, 1);
//
//            for (uint8_t i = 0; i < 5; i++)
//            {
//                DisplayPrintUInt(arrayrd[i], HEX);
//                DisplayPrintChar(' ');
//            }
//
//
//
//
//
//
//
//
//
//            //PortWrite(arraywr, 9);
//            for (uint24_t i = 0; i < EXT_MEM_CHIP_SIZE; i += RBUF_LEN)
//            {
//
//                EESequentialRead(0xA1, i, arrayrd, RBUF_LEN);
//                PortWrite(arrayrd, RBUF_LEN);
//            }
//        }
//            break;
//        case BTN_2: // курсор вверх
//        {
//            if(curRow == 0)
//                break;
//            curRow--;
//            DisplaySetCursorPos(curCol, curRow);
//        }
//            break;
//        case BTN_8: // курсор Вниз
//        {
//            if(curRow == 1)
//                break;
//            curRow++;
//            DisplaySetCursorPos(curCol, curRow);
//        }
//            break;
//        case BTN_4: // курсор влево
//        {
//            if(curCol == 0)
//                break;
//            curCol--;
//            DisplaySetCursorPos(curCol, curRow);
//        }
//            break;
//        case BTN_6: // курсор вправо
//        {
//            if(curCol == 15)
//                break;
//            curCol++;
//            DisplaySetCursorPos(curCol, curRow);
//        }
//            break;
//            
//            
//        case BTN_5: // Мигание вкл-выкл
//        {
//            if(curBlink)
//            {
//                DisplayNoBlink();
//                curBlink = false;
//            }
//            else                
//            {
//                DisplayBlink();
//                curBlink = true;
//            }
//        }
//            break;
//        case BTN_BPS: // Курсор вкл-выкл
//        {
//            if(curCur)
//            {
//                DisplayNoCursor();
//                curCur = false;
//            }
//            else                
//            {
//                DisplayCursor();
//                curCur = true;
//            }
//        }
//            break;
        case BTN_ARM:
        {
            if(_currentSiState != VS_ROOT)
            {
                _currentButtonInfo = 0;
                _currentSiState = VS_BUTTON_INFO;
                IdleDisplayRedraw();
            }
            else 
                QuickButtonPress(0);
        }
        break;
        case BTN_DISARM:
        {
            if(_currentSiState != VS_ROOT)
            {
                _currentButtonInfo = 1;
                _currentSiState = VS_BUTTON_INFO;
                IdleDisplayRedraw();
            }
            else 
                QuickButtonPress(1);
        }
        break;
        case BTN_BPS:
        {
            if(_currentSiState != VS_ROOT)
            {
                _currentButtonInfo = 2;
                _currentSiState = VS_BUTTON_INFO;
                IdleDisplayRedraw();
            }
            else 
                QuickButtonPress(2);
        }
        break;
        case BTN_TRBL:
        {
            if(_currentSiState != VS_ROOT)
            {
                _currentButtonInfo = 3;
                _currentSiState = VS_BUTTON_INFO;
                IdleDisplayRedraw();
            }
            else 
                QuickButtonPress(3);
        }
        break;
        case BTN_MEM:
        {
            if(_currentSiState != VS_ROOT)
            {
                _currentButtonInfo = 4;
                _currentSiState = VS_BUTTON_INFO;
                IdleDisplayRedraw();
            }
            else 
                QuickButtonPress(4);
        }
        break;
        case BTN_1:
        {
            if(_currentSiState != VS_ROOT)
            {
                _currentButtonInfo = 5;
                _currentSiState = VS_BUTTON_INFO;
                IdleDisplayRedraw();
            }
            else 
                QuickButtonPress(5);
        }
        break;
        case BTN_2:
        {
            if(_currentSiState != VS_ROOT)
            {
                _currentButtonInfo = 6;
                _currentSiState = VS_BUTTON_INFO;
                IdleDisplayRedraw();
            }
            else 
                QuickButtonPress(6);
        }
        break;
        case BTN_3:
        {
            if(_currentSiState != VS_ROOT)
            {
                _currentButtonInfo = 7;
                _currentSiState = VS_BUTTON_INFO;
                IdleDisplayRedraw();
            }
            else 
                QuickButtonPress(7);
        }
        break;
        case BTN_4:
        {
            if(_currentSiState != VS_ROOT)
            {
                _currentButtonInfo = 8;
                _currentSiState = VS_BUTTON_INFO;
                IdleDisplayRedraw();
            }
            else 
                QuickButtonPress(8);
        }
        break;
        case BTN_5:
        {
            if(_currentSiState != VS_ROOT)
            {
                _currentButtonInfo = 9;
                _currentSiState = VS_BUTTON_INFO;
                IdleDisplayRedraw();
            }
            else 
                QuickButtonPress(9);
        }
        break;
        case BTN_6:
        {
            if(_currentSiState != VS_ROOT)
            {
                _currentButtonInfo = 10;
                _currentSiState = VS_BUTTON_INFO;
                IdleDisplayRedraw();
            }
            else 
                QuickButtonPress(10);
        }
        break;
        case BTN_7:
        {
            if(_currentSiState != VS_ROOT)
            {
                _currentButtonInfo = 11;
                _currentSiState = VS_BUTTON_INFO;
                IdleDisplayRedraw();
            }
            else 
                QuickButtonPress(11);
        }
        break;
        case BTN_8:
        {
            if(_currentSiState != VS_ROOT)
            {
                _currentButtonInfo = 12;
                _currentSiState = VS_BUTTON_INFO;
                IdleDisplayRedraw();
            }
            else 
                QuickButtonPress(12);
        }
        break;
        case BTN_9:
        {
            if(_currentSiState != VS_ROOT)
            {
                _currentButtonInfo = 13;
                _currentSiState = VS_BUTTON_INFO;
                IdleDisplayRedraw();
            }
            else 
                QuickButtonPress(13);
        }
        break;
        case BTN_0:
        {
            if(_currentSiState != VS_ROOT)
            {
                _currentButtonInfo = 14;
                _currentSiState = VS_BUTTON_INFO;
                IdleDisplayRedraw();
            }
            else 
                QuickButtonPress(14);
        }
        break;
        




        case BTN_LEFT:
        {
            switch(_currentSiState)
            {
                case VS_PRESS_BUTTON:
                {
                    _currentSiState = VS_BUTTON_INFO;
                    _currentButtonInfo = 0;
                }
                break;
                case VS_BUTTON_INFO:// Вход в режим выбора комнат
                {
                    if(_currentButtonInfo > 0)
                        _currentButtonInfo--;
                }
                break;
            }
            IdleDisplayRedraw();
        }
        break;
        case BTN_RIGHT:
        {
            switch(_currentSiState)
            {
                case VS_PRESS_BUTTON:
                {
                    _currentSiState = VS_BUTTON_INFO;
                    _currentButtonInfo = QUICK_BUTTON_COUNT - 1;
                }
                break;
                case VS_BUTTON_INFO:// Вход в режим выбора комнат
                {
                    if(_currentButtonInfo < QUICK_BUTTON_COUNT - 1)
                        _currentButtonInfo++;
                }
                break;
            }
            IdleDisplayRedraw();
        }
        break;           
        case BTN_ENT: 
        {
            switch(_currentSiState)
            {
                case VS_ROOT:// Вход в режим показа информации о кнопках
                {
                    _currentSiState = VS_PRESS_BUTTON;
                }
                break;
                case VS_PRESS_BUTTON:// Вход в режим показа информации о кнопках
                {
                    _currentSiState = VS_BUTTON_INFO;
                    _currentButtonInfo = 0;
                }
                break;
            }
                
            IdleDisplayRedraw();    
            
        }
            break;
        case BTN_CLR:
        {
            switch(_currentSiState)
            {
                 case VS_PRESS_BUTTON:// Вход в режим показа информации о кнопках
                {
                    _currentSiState = VS_ROOT;
                }
                break;               
                case VS_BUTTON_INFO:// Вход в режим выбора комнат
                {
                    _currentSiState = VS_PRESS_BUTTON;

                }
                break;
            }
            IdleDisplayRedraw();
        }
            break;

        default:
            IdleDisplayRedraw();
            break;
    }
}

bool IdleIsRoot()
{
    return _currentSiState == VS_ROOT;
}