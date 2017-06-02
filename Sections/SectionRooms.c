#include "SectionRooms.h"
#include "../MODBUS/ModbusRtu.h"
#include "../LCD/xlcd.h"
#include "../buttons.h"
#include "../ParametersController.h"





// Заготовки данных, которые потом будут в EEPROM

//char *roomNames[] = 
//{
//    "Спальня",
//    "Ванная",
//    "Коридор",
//    "Улица"
//};







/*typedef struct
{
    char Name[10];
    uint8_t Type;
}Param;*/

//uint8_t ParamCount;// = DUMMY_PARAMS_COUNT;
/*const Param Params[] =
{
    // Спальня
    //{.ParamId, .Name,     .Type,          .Value}, 
    {"Темпер.",     PT_TEMP,        }, 
    {"Влажность",   PT_HYM,         }, 
    // Ванная
    {"Свет",        PT_LIGHT,       }, 
    {"Дверь",       PT_DOOR_OPEN,   }, 
    // Коридор
    {"Свет",        PT_LIGHT,       }, 
    // Улица
    {"Темпер.",     PT_TEMP,        }, 
    {"Влажность",   PT_HYM,         }, 
    {"Давление",    PT_PRESS,       }, 
};*/






uint8_t _currentRoom;
uint8_t _currentParam;
uint8_t _currentRoomParamCount;

typedef enum 
{
    VS_ROOT,
    VS_SELECT_ROOM,
    VS_SHOW_PARAMS,
    VS_EDIT_PARAM        
}ViewStates;

ViewStates _currentSrState;

void RoomDisplayRedraw();

//bool inited = false;
bool tempParamIs16bit;
uint16_t tempParam;
bool tempBoolParam;

void RoomsStart()
{
//    if(!inited)
//    {
//        InitParameters();//!!!!
//        inited = true;
//    }
    
    _currentSrState = VS_ROOT;
    //DisplayClear();
    //DisplayPrintChar(CH_LEFT_RIGHT);
    //DisplayPrintStr("Выбор комнаты");
    
//    DisplayNoBlink();
//    DisplayNoCursor();
    
    _currentRoom = 0;
    RoomDisplayRedraw();
    //DisplayHome();
}


void RoomDisplayRedraw()
{
    DisplayClear();
    char buf[9];
    GetRoomName(_currentRoom, buf);
    switch(_currentSrState)
    {
        case VS_ROOT:
        case VS_SELECT_ROOM:
        {
//            if(_currentSrState == VS_ROOT)
//            DisplayPrintChar(CH_LEFT_RIGHT);
//            else
//                DisplayPrintChar(' ');
            DisplayPrintStr("Выбор комнаты");
            DisplaySetCursorPos(0, 1);
            if(_currentSrState == VS_SELECT_ROOM)
                DisplayPrintChar(CH_LEFT_RIGHT);
            if(_currentRoom >= RoomsCount)
            {
                DisplayPrintStr("Ошибка");
                return;
            }
            DisplayPrintStr((const char *)buf);
            
            if(_currentSrState == VS_ROOT)
                DisplaySetCursorPos(0, 0);
            else
                DisplaySetCursorPos(0, 1);

        }
        break;
        case VS_SHOW_PARAMS:
        {
            // Первая строка - название комнаты
            DisplayPrintStr((const char *)buf);
            // Вторая строка название параметра и значение
            DisplaySetCursorPos(0, 1);
//            DisplayPrintChar(CH_LEFT_RIGHT);
            
            PrintParameterByRoom(_currentRoom, _currentParam, -1, -1, PPN_FULL);
            if(IsParamEditable(_currentRoom, _currentParam, &tempParamIs16bit))
            {
                DisplayPrintChar('*');
            }
            DisplaySetCursorPos(0, 1);
        }
        break;
        case VS_EDIT_PARAM:
        {
            // Первая строка - название комнаты  и параметра
            DisplayPrintStr((const char *)buf);
            DisplayPrintChar(' ');
            //char buf[9];
            GetParameterNameByRoom(_currentRoom, _currentParam, buf);
            DisplayPrintStr((const char *)buf);
            // Вторая строка -название параметра и- значение
            DisplaySetCursorPos(0, 1);
            //DisplayPrintSymbol(CH_LEFT_RIGHT);
            
            
            if(tempParamIs16bit)
            {
                PrintParameterByRoomAndValue(_currentRoom, _currentParam, tempParam, -1, -1, PPN_NONE);
                DisplayPrintProgress(8, 8, 1, (uint8_t)((tempParam - GetParameterMaxByRoom(_currentRoom, _currentParam)) / (float)(GetParameterMaxByRoom(_currentRoom, _currentParam) - GetParameterMinByRoom(_currentRoom, _currentParam)) * 100));
            }
            else
            {
                PrintDiscreteParameterByRoomAndValue(_currentRoom, _currentParam, tempBoolParam, -1, -1, PPN_NONE);
            }
            DisplaySetCursorPos(0, 1);
        }
        break;
    }
    
    
    DisplayCursor();
    DisplayBlink();
}

void RoomsUpdateView()
{
    RoomDisplayRedraw();
}

void RoomsOnButton(uint8_t button)
{
    if (ButtonStates[button] != BUTTON_PRESSED)
        return;
    switch (button)
    {
        case BTN_LEFT:
        {
            switch(_currentSrState)
            {
                case VS_SELECT_ROOM:// выход в корень
                {
                    if(_currentRoom == 0)
                        _currentRoom = RoomsCount - 1u;
                    else
                        _currentRoom--;
                    _currentParam = 0;
                }
                break;
                case VS_SHOW_PARAMS:
                {
                    if(_currentParam == 0)
                        _currentParam = _currentRoomParamCount - 1u;
                    else
                        _currentParam--;
                }
                break;  
                case VS_EDIT_PARAM:
                {
                    if(tempParamIs16bit)
                    {
                        if(tempParam >= GetParameterMinByRoom(_currentRoom, _currentParam) + GetParameterStepByRoom(_currentRoom, _currentParam))
                        {
                            tempParam -= GetParameterStepByRoom(_currentRoom, _currentParam);                        
                        }
                        else
                            tempParam = GetParameterStepByRoom(_currentRoom, _currentParam);
                    }
                    else
                    {
                        tempBoolParam = !tempBoolParam;
                    }
//                    switch(GetParameterTypeByRoom(_currentRoom, _currentParam))
//                    {
//                        case PT_LIGHT:
//                        case PT_DOOR_OPEN:
//                        case PT_YES_NO:
//                        {
//                            if(tempParam == MODBUS_TRUE)
//                                tempParam = MODBUS_FALSE;
//                            else
//                                tempParam = MODBUS_TRUE;
//                        }
//                        break;
//                        default:
//                        {
//                            if(tempParam >= GetParameterMinByRoom(_currentRoom, _currentParam) + GetParameterStepByRoom(_currentRoom, _currentParam))
//                            {
//                                tempParam -= GetParameterStepByRoom(_currentRoom, _currentParam);                        
//                            }
//                            else
//                                tempParam = GetParameterStepByRoom(_currentRoom, _currentParam);
//                            
//                        }
//                    }
                }
                break;
            }
            RoomDisplayRedraw();
        }
        break;
        case BTN_RIGHT:
        {
            switch(_currentSrState)
            {
                case VS_SELECT_ROOM:// выход в корень
                {
                    if(_currentRoom == RoomsCount - 1)
                        _currentRoom = 0;
                    else
                        _currentRoom++;
                    _currentParam = 0;
                }
                break;
                case VS_SHOW_PARAMS:
                {
                    if(_currentParam == _currentRoomParamCount - 1)
                        _currentParam = 0;
                    else
                        _currentParam++;
                }
                break;  
                case VS_EDIT_PARAM:
                {
                    if(tempParamIs16bit)
                    {
                        if(tempParam <= GetParameterMaxByRoom(_currentRoom, _currentParam) - GetParameterStepByRoom(_currentRoom, _currentParam))
                            tempParam += GetParameterStepByRoom(_currentRoom, _currentParam);  
                        else
                            tempParam = GetParameterMaxByRoom(_currentRoom, _currentParam);                        
                    }
                    else
                    {
                        tempBoolParam = !tempBoolParam;
                    }
                    
                    
//                    switch(GetParameterTypeByRoom(_currentRoom, _currentParam))
//                    {
//                        case PT_LIGHT:
//                        case PT_DOOR_OPEN:
//                        case PT_YES_NO:
//                        {
//                            if(tempParam == MODBUS_TRUE)
//                                tempParam = MODBUS_FALSE;
//                            else
//                                tempParam = MODBUS_TRUE;
//                        }
//                        break;
//                        default:
//                        {
//                            if(tempParam <= GetParameterMaxByRoom(_currentRoom, _currentParam) - GetParameterStepByRoom(_currentRoom, _currentParam))
//                                tempParam += GetParameterStepByRoom(_currentRoom, _currentParam);  
//                            else
//                                tempParam = GetParameterMaxByRoom(_currentRoom, _currentParam);
//                        }
//                    }
                }
                break;
            }
            RoomDisplayRedraw();
        }
        break;   
        
        
        case BTN_ENT: 
        {
            switch(_currentSrState)
            {
                case VS_ROOT:// Вход в режим выбора комнат
                {
                    _currentSrState = VS_SELECT_ROOM;
                }
                break;
                case VS_SELECT_ROOM:
                {
                    _currentSrState = VS_SHOW_PARAMS;
                    _currentRoomParamCount = GetRoomParamsCount(_currentRoom);
                }
                break;
                case VS_SHOW_PARAMS:
                {
                    if(!IsParamEditable(_currentRoom, _currentParam, &tempParamIs16bit))
                        break;
                    _currentSrState = VS_EDIT_PARAM;
                    if(tempParamIs16bit)
                        tempParam = GetParameterValueByRoom(_currentRoom, _currentParam);
                    else
                       tempBoolParam = GetDiscreteParameterValueByRoom(_currentRoom, _currentParam);
                }
                break;
                case VS_EDIT_PARAM: // Сохраняем параметр
                {
                    _currentSrState = VS_SHOW_PARAMS;
                    if(tempParamIs16bit)
                        SetParameterValueByRoom(_currentRoom, _currentParam, tempParam);
                    else
                        SetDiscreteParameterValueByRoom(_currentRoom, _currentParam, tempBoolParam);
                }               
                break;
            }
            RoomDisplayRedraw();
        }
            break;
        case BTN_CLR:
        {
            switch(_currentSrState)
            {
                case VS_SELECT_ROOM:// выход в корень
                {
                    _currentSrState = VS_ROOT;
                }
                break;
                case VS_SHOW_PARAMS:
                {
                    _currentSrState = VS_SELECT_ROOM;
                }
                break;
                case VS_EDIT_PARAM: // Отменяем изменения
                {
                    _currentSrState = VS_SHOW_PARAMS;
                }               
                break;
            }
            RoomDisplayRedraw();
        }
            break;
    }
}

bool RoomsIsRoot()
{
    return _currentSrState == VS_ROOT;
}