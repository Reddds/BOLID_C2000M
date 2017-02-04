#include "ParametersController.h"
#include "LCD/xlcd.h"





uint8_t _paramCount = 8;


typedef struct
{
    char Name[10];
    uint8_t Type;
}Param;

const Param Params[] =
{
    // Спальня
    //{.ParamId, .Name,     .Type,          .Value}, 
    {"Темпер.",     PT_TEMP,        }, //   0
    {"Влажность",   PT_HYM,         }, //   1
    // Ванная
    {"Свет",        PT_LIGHT,       }, //   2 
    {"Дверь",       PT_DOOR_OPEN,   }, //   3 
    // Коридор
    {"Свет",        PT_LIGHT,       }, //   4 
    // Улица
    {"Темпер.",     PT_TEMP,        }, //   5 
    {"Влажность",   PT_HYM,         }, //   6 
    {"Давление",    PT_PRESS,       }, //   7 
};

/**
 * Список всех параметров. Ограничен 256
 */
uint16_t _parameters[256];

void InitParameters()
{
    _parameters[0] = 22;
    _parameters[1] = 54;
    
    _parameters[2] = true;   
    _parameters[3] = false;
    
    _parameters[4] = false;
    
    _parameters[5] = -12;
    _parameters[6] = 96;
    _parameters[7] = 446;
    
}





uint8_t GetParamCount()
{
    return _paramCount;
}

bool SetParameter(uint8_t id, uint16_t value)
{
    if(id >= _paramCount)
        return false;
    _parameters[id] = value;
    return true;
}

uint16_t GetParameter(uint8_t id)
{
    if(id >= _paramCount)
        return 0;
    return _parameters[id];
}

void PrintParameter(uint8_t paramId, int8_t col, int8_t row, PrintParamName printParamName)
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
            int16_t t = (int16_t)(_parameters[paramId]);
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
            DisplayPrintUInt(_parameters[paramId], DEC);
            DisplayPrintChar('%');
        }
            break;
        case PT_PRESS:
        {
            if(printParamName == PPN_SHORT)
                DisplayPrintStr("p ");
            DisplayPrintUInt(_parameters[paramId], DEC);
            DisplayPrintStr("mm");
        }
            break;  
        case PT_LIGHT:
        {
            if(printParamName == PPN_SHORT)
                DisplayPrintStr("с ");
            if(_parameters[paramId] != 0)
                DisplayPrintStr("Вкл");
            else
                DisplayPrintStr("Выкл");
        }
            break;  
        case PT_DOOR_OPEN:
        {
            if(printParamName == PPN_SHORT)
                DisplayPrintStr("д ");
            if(_parameters[paramId] != 0)
                DisplayPrintStr("Отк");
            else
                DisplayPrintStr("Закр");
        }
            break;  
            
    }
}