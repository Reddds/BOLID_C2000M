#include "ParametersController.h"
#include "ModbusRtu.h"
#include "LCD/xlcd.h"





uint8_t _paramCount = 8;


typedef struct
{
    char Name[10];
    uint8_t Type;
    bool editable; // Возможность изменения
    uint16_t min;  // Минимальное значение при возможности изменения
    uint16_t max;  // Максимальное знавчение при возможности изменения
    uint16_t step; // Шаг изменения
}Param;

const Param Params[] =
{
    // Спальня
    //{.ParamId, .Name,     .Type,          .Value}, 
    // макс 8 символов
    {"Темпер. ", PT_TEMP,      false, 0, 0, 0}, //   0
    {"Влажн.  ", PT_HYM,       false, 0, 0, 0}, //   1
    // Ванная
    {"Свет    ", PT_LIGHT,     false, 0, 0, 0}, //   2 
    {"Дверь   ", PT_DOOR_OPEN, false, 0, 0, 0}, //   3 
    {"Игн.дв. ", PT_YES_NO,    true,  0, 1, 1}, //   3 
    // Коридор
    {"Свет    ", PT_LIGHT,     false, 0, 0, 0}, //   4 
    // Улица
    {"Темпер. ", PT_TEMP,      false, 0, 0, 0}, //   5 
    {"Влажн.  ", PT_HYM,       false, 0, 0, 0}, //   6 
    {"Давление", PT_PRESS,     false, 0, 0, 0}, //   7 
};


/**
 * Список всех параметров. Ограничен 256
 */
uint16_t _parameters[256];

void InitParameters()
{
    _parameters[0] = 22;
    _parameters[1] = 54;
    
    _parameters[2] = MODBUS_TRUE;   
    _parameters[3] = MODBUS_FALSE;
    _parameters[4] = MODBUS_FALSE;
    
    _parameters[5] = MODBUS_FALSE;
    
    _parameters[6] = -12;
    _parameters[7] = 96;
    _parameters[8] = 446;
    
}



uint8_t GetParamCount()
{
    return _paramCount;
}

bool IsParamEditable(uint8_t room, uint8_t param)
{
    return Params[roomParams[room].ParamAddresses[param]].editable;
}

bool SetParameterValue(uint8_t id, uint16_t value)
{
    if(id >= _paramCount)
        return false;
    _parameters[id] = value;
    return true;
}

void SetParameterValueByRoom(uint8_t room, uint8_t param, uint16_t value)
{
    _parameters[roomParams[room].ParamAddresses[param]] = value;
}

uint16_t GetParameterValue(uint8_t id)
{
    if(id >= _paramCount)
        return 0;
    return _parameters[id];
}

/**
 * Заполнение массива именем параметра
 * @param buf Массив [9]: 8 букв + 1 последний ноль
 */
void GetParameterNameByRoom(uint8_t room, uint8_t param, char* buf)
{
    GetParameterName(roomParams[room].ParamAddresses[param], buf);
}

void GetParameterName(uint8_t id, char* buf)
{
    //Пока тупо, потом сделать заполнение массива из еепром
    uint8_t i;
    for(i = 0; i < 8; i++)
        buf[i] = Params[id].Name[i];
    buf[i] = 0;    
}

uint16_t GetParameterValueByRoom(uint8_t room, uint8_t param)
{
    return _parameters[roomParams[room].ParamAddresses[param]];
}
ParamTypes GetParameterTypeByRoom(uint8_t room, uint8_t param)
{
    return Params[roomParams[room].ParamAddresses[param]].Type;
}
uint16_t GetParameterMinByRoom(uint8_t room, uint8_t param)
{
    return Params[roomParams[room].ParamAddresses[param]].min;
}
uint16_t GetParameterMaxByRoom(uint8_t room, uint8_t param)
{
    return Params[roomParams[room].ParamAddresses[param]].max;
}
uint16_t GetParameterStepByRoom(uint8_t room, uint8_t param)
{
    return Params[roomParams[room].ParamAddresses[param]].step;
}

void PrintParameterByRoom(uint8_t room, uint8_t param, int8_t col, int8_t row, PrintParamName printParamName)
{
    PrintParameter(roomParams[room].ParamAddresses[param], col, row, printParamName);
}

void PrintParameter(uint8_t paramId, int8_t col, int8_t row, PrintParamName printParamName)
{
    PrintParameterByValue(paramId, _parameters[paramId], col, row, printParamName);
}

void PrintParameterByRoomAndValue(uint8_t room, uint8_t param, uint16_t value, int8_t col, int8_t row, PrintParamName printParamName)
{
    PrintParameterByValue(roomParams[room].ParamAddresses[param], value, col, row, printParamName);
}

void PrintParameterByValue(uint8_t paramId, uint16_t value, int8_t col, int8_t row, PrintParamName printParamName)
{
    if(col >= 0 && row >= 0)
        DisplaySetCursorPos(col, row);
    
    
    switch(printParamName)
    {
        case PPN_FULL:
        {
            DisplayPrintStr(Params[paramId].Name);
            DisplayPrintChar(' ');
        }
            break;
        case PPN_SHORT:
        {
            
        }
            break;
    }
    
    switch(Params[paramId].Type)
    {
        case PT_TEMP:
        {
            if(printParamName == PPN_SHORT)
                DisplayPrintStr("t ");
            int16_t t = value;
            if(t > 0)
                DisplayPrintChar('+');
            DisplayPrintInt(t, DEC);
            DisplayPrintSymbol(CH_GRADUS_C);
            
        }
            break;
        case PT_HYM:
        {
            if(printParamName == PPN_SHORT)
                DisplayPrintStr("h ");
            DisplayPrintUInt(value, DEC);
            DisplayPrintChar('%');
        }
            break;
        case PT_PRESS:
        {
            if(printParamName == PPN_SHORT)
                DisplayPrintStr("p ");
            DisplayPrintUInt(value, DEC);
            DisplayPrintStr("mm");
        }
            break;  
        case PT_LIGHT:
        {
            if(printParamName == PPN_SHORT)
                DisplayPrintStr("с ");
            if(value != MODBUS_FALSE)
                DisplayPrintStr("Вкл");
            else
                DisplayPrintStr("Выкл");
        }
            break;  
        case PT_DOOR_OPEN:
        {
            if(printParamName == PPN_SHORT)
                DisplayPrintStr("д ");
            if(value != MODBUS_FALSE)
                DisplayPrintStr("Отк");
            else
                DisplayPrintStr("Закр");
        }
            break;  
        case PT_YES_NO:
        {
            if(printParamName == PPN_SHORT)
                DisplayPrintStr("? ");
            if(value != MODBUS_FALSE)
                DisplayPrintStr("Да");
            else
                DisplayPrintStr("Нет");
        }
            break;      
    }    
}