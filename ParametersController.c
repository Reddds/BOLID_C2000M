#include "ParametersController.h"
#include "LCD/xlcd.h"

/**
 * Список всех параметров. Ограничен 256
 */
ParameterTag _parameters[256];

void InitParameters()
{
    _parameters[0].Type = PT_TEMP;
    _parameters[0].Value = 22;
  
    _parameters[1].Type = PT_HYM;
    _parameters[1].Value = 54;
    


    _parameters[20].Type = PT_TEMP;
    _parameters[20].Value = (int16_t)(-15);   

    _parameters[21].Type = PT_HYM;
    _parameters[21].Value = 96;
    
    _parameters[22].Type = PT_PRESS;
    _parameters[22].Value = 440;
    
    
}

void PrintParameter(uint8_t paramId, uint8_t col, uint8_t row)
{
    if(col >= 0 && row >= 0)
        DisplaySetCursorPos(col, row);
    
    switch(_parameters[paramId].Type)
    {
        case PT_TEMP:
            DisplayPrintInt(_parameters[paramId].Value, DEC);
            DisplayPrintChar(CH_GRADUS);
            break;
        case PT_HYM:
            DisplayPrintUInt(_parameters[paramId].Value, DEC);
            DisplayPrintChar('%');
            break;
        case PT_PRESS:
            DisplayPrintUInt(_parameters[paramId].Value, DEC);
            DisplayPrintStr("mm");
            break;            
    }
}