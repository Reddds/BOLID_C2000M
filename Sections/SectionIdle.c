#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include <time.h>

#include "SectionIdle.h"
#include "../MODBUS/ModbusRtu.h"
//#include "../i2c/i2c.h"
#include "../LCD/xlcd.h"
#include "../buttons.h"
#include "../interrupts.h"
#include "../ParametersController.h"


// Конфиг

//Конфиг главного экрана
// * 
// * Позиция (Кол, ряд) / Тип / Значение





//#define QUICK_BUTTON_COUNT 15
//QuickButtonParam QuickButtonParams[] = 
//{
//    {BTN_ARM,    4, 1,  MODBUS_TRUE,            0, 0}, // 0
//    {BTN_DISARM, 4, 1, MODBUS_FALSE,            0, 0}, // 1
//    {BTN_BPS,    4, 2,  MODBUS_TRUE, MODBUS_FALSE, 0}, // 2
//    {BTN_TRBL,   0, 0,            0,            0, 0}, // 3
//    {BTN_MEM,    0, 0,            0,            0, 0}, // 4
//    {BTN_1,      0, 0,            0,            0, 0}, // 5
//    {BTN_2,      0, 0,            0,            0, 0}, // 6
//    {BTN_3,      0, 0,            0,            0, 0}, // 7
//    {BTN_4,      0, 0,            0,            0, 0}, // 8
//    {BTN_5,      0, 0,            0,            0, 0}, // 9
//    {BTN_6,      0, 0,            0,            0, 0}, // 10
//    {BTN_7,      0, 0,            0,            0, 0}, // 11
//    {BTN_8,      0, 0,            0,            0, 0}, // 12
//    {BTN_9,      0, 0,            0,            0, 0}, // 13
//    {BTN_0,      0, 0,            0,            0, 0}, // 14
//};

typedef enum
{
    VS_ROOT,
    VS_PRESS_BUTTON, // Предлагает нажать на кнопку, чтобы посмотреть события на ней        
    VS_BUTTON_INFO, // Информация о кнопках     
} ViewStates;

ViewStates _currentSiState;
uint8_t _currentButtonInfo;

uint8_t _currentIdleScreen;




bool isRoot = false;

void PrintOnlyValue(uint8_t qpid, uint16_t value)
{
    if (QuickButtonParams[qpid].Is16Bit)
        PrintParameterByValue(QuickButtonParams[qpid].ParamId, value, -1, -1, PPN_NONE);
    else
        PrintDiscreteParameterByValue(QuickButtonParams[qpid].ParamId, value == MODBUS_TRUE, -1, -1, PPN_NONE);
}

//#define RBUF_LEN 0x20
//
//
//unsigned char arrayrd[RBUF_LEN];

/**
 * Печать времени в текущую позицию
 * @param type
 */
void PrintTime(MainItemTypes type)
{
    uint8_t hour, min;
    bool getTimeRes = getHourMin(&hour, &min);

    switch (type)
    {
        
        case MIT_TIME_HOUR: // Текущее время (час)
        {
            DisplayPrintUInt(hour, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
        }
        break;
        case MIT_TIME_MIN: // Текущее время (минуты)      
        {
            DisplayPrintUInt(min, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
        }
            break;
        case MIT_TIME: // Текущее время HH:MM
        {
            DisplayPrintUInt(hour, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
            DisplayPrintChar(':');
            DisplayPrintUInt(min, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
        }
            break;
    }
}


void IdleDisplayRedraw()
{
    DisplayClear();


    switch (_currentSiState)
    {
        case VS_ROOT:
        {
            //DisplayPrintSymbol(CH_HOME);

            for (uint8_t i = 0; i < MainParamCount[_currentIdleScreen]; i++)
            {
                MainScreenItem mainParamData;
                GetMainScreenParam(_currentIdleScreen, i, &mainParamData);
                if (mainParamData.Type == MIT_UNKNOWN)
                    continue;
                DisplaySetCursorPos(mainParamData.Column, mainParamData.Row);
                switch (mainParamData.Type)
                {
                    case MIT_LITERAL:
                    {
                        DisplayPrintStr((const char *)mainParamData.Value.Str.str);
                    }
                        break;
                    case MIT_PARAM:
                    {
                        PrintParameter(mainParamData.Value.ParamNum.paramId, mainParamData.Value.ParamNum.is16Bit, -1, -1, PPN_NONE);
                    }
                        break;
                    case MIT_SHORT:
                    {
                        PrintParameter(mainParamData.Value.ParamNum.paramId, mainParamData.Value.ParamNum.is16Bit, -1, -1, PPN_SHORT);
                    }
                        break;
                    case MIT_FULL:
                    {
                        PrintParameter(mainParamData.Value.ParamNum.paramId, mainParamData.Value.ParamNum.is16Bit, -1, -1, MIT_FULL);
                    }
                        break;
                    case MIT_TIME: // Текущее время HH:MM
                    case MIT_TIME_HOUR: // Текущее время (час)
                    case MIT_TIME_MIN: // Текущее время (минуты)      
                    {
                        PrintTime(mainParamData.Type);
                    }
                        break;
                    case MIT_DATE_LONG: // www dd mmm year         
                    case MIT_DATE_FULL: // dd  month(8)   year 
                    //case MIT_DATE_CAST:
                    case MIT_DATE_NORMAL: // dd.mm.yyyy       
                    case MIT_DATE_SHORT: // dd.mm.yy   
                    case MIT_DATE_DAY:
                    case MIT_DATE_MONTH_STR: // Месяц словом
                    case MIT_DATE_MONTH: // Месяц цифрой
                    case MIT_DATE_YEAR: // yyyy
                    case MIT_DATE_YEAR_SHORT: // yy
                    case MIT_DATE_DAY_OF_WEEK_LONG: // Длинная строка
                    case MIT_DATE_DAY_OF_WEEK_MID: // 3 символа       
                    case MIT_DATE_DAY_OF_WEEK_SHORT: // 2 символа   
                    {
                        PrintDate(mainParamData.Type);
                    }
                        break;
//                    case MIT_CAST_MORNING: // Утро   
//                    {
//                        DisplayPrintStr("Утро");
//                    }
//                    break;
//                    case MIT_CAST_DAY,   // День   
//                    case MIT_CAST_EVENING,  // Вечер    
//                    case MIT_CAST_NIGHT,  // Ночь

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
            DisplayPrintStr((const char *)GetButtonName(QuickButtonParams[_currentButtonInfo].Button));
            DisplayPrintStr(": ");
            if (QuickButtonParams[_currentButtonInfo].ValuesCount == 0)
            {
                DisplayPrintStr("Пусто");
                break;
            }
            char buf[9];
            //bool is16bit;
            GetParameterName(QuickButtonParams[_currentButtonInfo].ParamId, QuickButtonParams[_currentButtonInfo].Is16Bit, buf);
            DisplayPrintStr((const char *)buf);

            DisplaySetCursorPos(0, 1);



            PrintOnlyValue(_currentButtonInfo, QuickButtonParams[_currentButtonInfo].Value1);
            if (QuickButtonParams[_currentButtonInfo].ValuesCount > 1)
            {
                DisplayPrintStr(" - ");
                PrintOnlyValue(_currentButtonInfo, QuickButtonParams[_currentButtonInfo].Value2);

                if (QuickButtonParams[_currentButtonInfo].ValuesCount > 2)
                {
                    DisplayPrintStr(" - ");
                    PrintOnlyValue(_currentButtonInfo, QuickButtonParams[_currentButtonInfo].Value3);
                }
            }
        }
            break;
    }



}

void IdleUpdateView()
{

    IdleDisplayRedraw();
}

void IdleStart()
{
    //    MainConfig[0].Column = 1;
    //    MainConfig[0].Row = 0;
    //    MainConfig[0].Type = MIT_LITERAL;
    //    MainConfig[0].Value.str = "Улица:";

    //= {1, 0, MIT_LITERAL};



    _currentSiState = VS_ROOT;
    _currentIdleScreen = 0;
    
    DisplayNoBlink();
    DisplayNoCursor();
    
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

void QuickSetParam(uint8_t qpid, uint16_t value)
{
    if (QuickButtonParams[qpid].Is16Bit)
        SetParameterValue(QuickButtonParams[qpid].ParamId, value);
    else
        SetDiscreteParameterValue(QuickButtonParams[qpid].ParamId, value == MODBUS_TRUE);
    PrintParameter(QuickButtonParams[qpid].ParamId, QuickButtonParams[qpid].Is16Bit, -1, -1, PPN_NONE);
}

void QuickButtonPress(uint8_t id)
{
    if (QuickButtonParams[id].ValuesCount == 0)
        return;

    DisplayClear();
    char buf[9];
    GetParameterName(QuickButtonParams[id].ParamId, QuickButtonParams[id].Is16Bit, buf);
    DisplayPrintStr((const char *)buf);
    DisplayPrintStr(" = ");


    if (QuickButtonParams[id].ValuesCount == 1)
    {
        QuickSetParam(id, QuickButtonParams[id].Value1);
        return;
    }

    if (QuickButtonParams[id].Is16Bit)
    {
        if (GetParameterValue(QuickButtonParams[id].ParamId) == QuickButtonParams[id].Value1)
        {
            QuickSetParam(id, QuickButtonParams[id].Value2);
            return;
        }
        if (GetParameterValue(QuickButtonParams[id].ParamId) == QuickButtonParams[id].Value2)
        {
            if (QuickButtonParams[id].ValuesCount == 2)
                QuickSetParam(id, QuickButtonParams[id].Value1);
            else // 3
                QuickSetParam(id, QuickButtonParams[id].Value3);
            return;
        }
        if (QuickButtonParams[id].ValuesCount == 3
                && GetParameterValue(QuickButtonParams[id].ParamId) == QuickButtonParams[id].Value3)
        {
            QuickSetParam(id, QuickButtonParams[id].Value1);
            return;
        }
        QuickSetParam(id, QuickButtonParams[id].Value1);

    }
    else
    {
        if (GetDiscreteParameterValue(QuickButtonParams[id].ParamId) == (QuickButtonParams[id].Value1 == MODBUS_TRUE))
        {
            QuickSetParam(id, QuickButtonParams[id].Value2);
            return;
        }
        if (GetDiscreteParameterValue(QuickButtonParams[id].ParamId) == (QuickButtonParams[id].Value2 == MODBUS_TRUE))
        {
            if (QuickButtonParams[id].ValuesCount == 2)
                QuickSetParam(id, QuickButtonParams[id].Value1);
            else // 3
                QuickSetParam(id, QuickButtonParams[id].Value3);
            return;
        }
        if (QuickButtonParams[id].ValuesCount == 3
                && GetDiscreteParameterValue(QuickButtonParams[id].ParamId) == (QuickButtonParams[id].Value3 == MODBUS_TRUE))
        {
            QuickSetParam(id, QuickButtonParams[id].Value1);
            return;
        }
        QuickSetParam(id, QuickButtonParams[id].Value1);
    }

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
            if (_currentSiState != VS_ROOT)
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
            if (_currentSiState != VS_ROOT)
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
            if (_currentSiState != VS_ROOT)
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
            if (_currentSiState != VS_ROOT)
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
            if (_currentSiState != VS_ROOT)
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
            if (_currentSiState != VS_ROOT)
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
            if (_currentSiState != VS_ROOT)
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
            if (_currentSiState != VS_ROOT)
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
            if (_currentSiState != VS_ROOT)
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
            if (_currentSiState != VS_ROOT)
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
            if (_currentSiState != VS_ROOT)
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
            if (_currentSiState != VS_ROOT)
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
            if (_currentSiState != VS_ROOT)
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
            if (_currentSiState != VS_ROOT)
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
            if (_currentSiState != VS_ROOT)
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
            switch (_currentSiState)
            {
                case VS_ROOT:
                {
                    if (_currentIdleScreen > 0)
                        _currentIdleScreen--;
                    else
                        _currentIdleScreen = MainScreenCount - 1;
                }
                break;
                case VS_PRESS_BUTTON:
                {
                    _currentSiState = VS_BUTTON_INFO;
                    _currentButtonInfo = QUICK_BUTTON_COUNT - 1;

                }
                    break;
                case VS_BUTTON_INFO:// Вход в режим выбора комнат
                {
                    if (_currentButtonInfo > 0)
                        _currentButtonInfo--;
                }
                    break;
            }
            IdleDisplayRedraw();
        }
            break;
        case BTN_RIGHT:
        {
            switch (_currentSiState)
            {
                case VS_ROOT:
                {
                    if (_currentIdleScreen < MainScreenCount - 1)
                        _currentIdleScreen++;
                    else
                        _currentIdleScreen = 0;
                }
                break;
                case VS_PRESS_BUTTON:
                {
                    _currentSiState = VS_BUTTON_INFO;
                    _currentButtonInfo = 0;
                }
                    break;
                case VS_BUTTON_INFO:// Вход в режим выбора комнат
                {
                    if (_currentButtonInfo < QUICK_BUTTON_COUNT - 1)
                        _currentButtonInfo++;
                }
                    break;
            }
            IdleDisplayRedraw();
        }
            break;
        case BTN_ENT:
        {
            switch (_currentSiState)
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
            switch (_currentSiState)
            {
//                case VS_ROOT: // Переключаем экраны по кругу
//                {
//                    if (_currentIdleScreen < MainScreenCount - 1)
//                        _currentIdleScreen++;
//                    else
//                        _currentIdleScreen = 0;
//                }
//                    break;
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

void IdleNextScreen()
{
    if (_currentIdleScreen < MainScreenCount - 1)
        _currentIdleScreen++;
    else
        _currentIdleScreen = 0;
    IdleDisplayRedraw();
}


bool IdleIsRoot()
{
    return _currentSiState == VS_ROOT;
}