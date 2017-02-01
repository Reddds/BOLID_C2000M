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
};



typedef struct 
{
    uint8_t Type;
    uint16_t Value;
}ParameterTag;

void InitParameters();

/**
 * Вывод параметра на экран
 * @param paramId   ID параметра
 * @param col       Колонка (-1 - в текущую позицию)
 * @param row       Ряд (-1 - в текущую позицию)
 */
void PrintParameter(uint8_t paramId, uint8_t col, uint8_t row);

#endif