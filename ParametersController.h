#ifndef PARAMETERSCONTROLLER_H
#define PARAMETERSCONTROLLER_H

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */


typedef enum 
{
    PT_INT,
    PT_UINT,
    PT_FLOAT_1, // значение параметра делим на 10
    PT_FLOAT_2, // значение параметра делим на 100
    
    PT_TEMP, // Температура
    PT_HYM, // Влажность
    PT_PRESS, // Давление
    PT_LIGHT, // Свет вкл-выкл
    PT_DOOR_OPEN, // Дверь откр-закр
    PT_YES_NO // Да или нет
}ParamTypes;

// Печать названия параметра перед значением
typedef enum
{
    PPN_NONE, // Не печатать
    PPN_FULL, // Полное имя
    PPN_SHORT // Короткое имя  
}PrintParamName;

#define DUMMY_ROOM_COUNT 4
char *roomNames[] = 
{
    "Спальня",
    "Ванная",
    "Коридор",
    "Улица"
};

const uint16_t ParamAddresses_0[] = {0, 1};
const uint16_t ParamAddresses_1[] = {2, 3, 4};
const uint16_t ParamAddresses_2[] = {5};
const uint16_t ParamAddresses_3[] = {6, 7, 8};

typedef struct
{
    uint8_t Count;
    uint16_t *ParamAddresses;// Адрес в EEPROM, где расположена структура с параметром
}RoomParams;
const RoomParams roomParams[] =
{
    // Спальня
    //{.Count, .ParamAddresses},
    {2, ParamAddresses_0},
    // Ванная
    {3, ParamAddresses_1},
    // Коридор
    {1, ParamAddresses_2}, 
    // Улица
    {3, ParamAddresses_3}
};

#define DUMMY_PARAMS_COUNT 9


/*typedef struct 
{
    uint8_t Type;
    uint16_t Value;
}ParameterTag;*/

void InitParameters();

uint8_t GetParamCount();
bool SetParameterValue(uint8_t id, uint16_t value);
void SetParameterValueByRoom(uint8_t room, uint8_t param, uint16_t value);
void GetParameterName(uint8_t id, char* buf);
void GetParameterNameByRoom(uint8_t room, uint8_t param, char* buf);
uint16_t GetParameterValue(uint8_t id);
ParamTypes GetParameterTypeByRoom(uint8_t room, uint8_t param);
uint16_t GetParameterValueByRoom(uint8_t room, uint8_t param);
uint16_t GetParameterMinByRoom(uint8_t room, uint8_t param);
uint16_t GetParameterMaxByRoom(uint8_t room, uint8_t param);
uint16_t GetParameterStepByRoom(uint8_t room, uint8_t param);




#define GetParamAddress(room, param) (roomParams[room].ParamAddresses[param])
bool IsParamEditable(uint8_t room, uint8_t param); 

/**
 * Вывод параметра на экран
 * @param paramId           ID параметра
 * @param col               Колонка (-1 - в текущую позицию)
 * @param row               Ряд (-1 - в текущую позицию)
 * @param printParamName    Печатать ли название параметра
 */
void PrintParameter(uint8_t paramId, int8_t col, int8_t row, PrintParamName printParamName);

void PrintParameterByRoom(uint8_t room, uint8_t param, int8_t col, int8_t row, PrintParamName printParamName);
void PrintParameterByRoomAndValue(uint8_t room, uint8_t param, uint16_t value, int8_t col, int8_t row, PrintParamName printParamName);
void PrintParameterByValue(uint8_t paramId, uint16_t value, int8_t col, int8_t row, PrintParamName printParamName);
#endif