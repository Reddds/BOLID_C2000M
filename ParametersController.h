#ifndef PARAMETERSCONTROLLER_H
#define PARAMETERSCONTROLLER_H

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */


enum 
{
    PT_INT,
    PT_UINT,
    PT_FLOAT_1, // значение параметра делим на 10
    PT_FLOAT_2, // значение параметра делим на 100
    
    PT_TEMP, // Температура
    PT_HYM, // Влажность
    PT_PRESS, // Давление
    PT_LIGHT, // Свет вкл-выкл
    PT_DOOR_OPEN // Дверь откр-закр
};

// Печать названия параметра перед значением
typedef enum
{
    PPN_NONE, // Не печатать
    PPN_FULL, // Полное имя
    PPN_SHORT // Короткое имя  
}PrintParamName;


/*typedef struct 
{
    uint8_t Type;
    uint16_t Value;
}ParameterTag;*/

void InitParameters();

uint8_t GetParamCount();
bool SetParameter(uint8_t id, uint16_t value);
uint16_t GetParameter(uint8_t id);

/**
 * Вывод параметра на экран
 * @param paramId           ID параметра
 * @param col               Колонка (-1 - в текущую позицию)
 * @param row               Ряд (-1 - в текущую позицию)
 * @param printParamName    Печатать ли название параметра
 */
void PrintParameter(uint8_t paramId, int8_t col, int8_t row, PrintParamName printParamName);

#endif