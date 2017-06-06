#ifndef PARAMETERSCONTROLLER_H
#define PARAMETERSCONTROLLER_H

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include "LCD/xlcd.h"
#include "buttons.h"


typedef enum
{
    MIT_LITERAL, // Строка текста
    MIT_PARAM, // Значение параметра
    MIT_SHORT, // Значение параметра с коротким названием
    MIT_FULL, // Значение параметра с длинным названием 
            
    MIT_TIME, // Текущее время HH:MM
    MIT_TIME_HOUR,  // Текущее время (час)
    MIT_TIME_MIN,  // Текущее время (минуты)  
            
    MIT_DATE_LONG, // dd  month(8)   year 
    MIT_DATE_FULL, // dow dd mmm year     
    MIT_DATE_CAST, // Для прогноза погоды dd mmm        
    MIT_DATE_NORMAL, // dd.mm.yyyy       
    MIT_DATE_SHORT, // dd.mm.yy             
    MIT_DATE_DAY,
    MIT_DATE_MONTH_STR, // Месяц словом
    MIT_DATE_MONTH, // Месяц цифрой
    MIT_DATE_YEAR, // yyyy
    MIT_DATE_YEAR_SHORT, // yy
    MIT_DATE_DAY_OF_WEEK_LONG, // Длинная строка
    MIT_DATE_DAY_OF_WEEK_MID, // 3 символа       
    MIT_DATE_DAY_OF_WEEK_SHORT, // 2 символа   
            
//    MIT_CAST_MORNING, // Утро   
//    MIT_CAST_DAY,   // День   
//    MIT_CAST_EVENING,  // Вечер    
//    MIT_CAST_NIGHT,  // Ночь
            
    MIT_UNKNOWN = 0xFF      
}MainItemTypes;

typedef enum 
{
    PT_INT,
    PT_UINT,
    PT_FLOAT_1, // значение параметра делим на 10
    PT_FLOAT_2, // значение параметра делим на 100
    
    PT_TEMP, // Температура
    PT_HYM, // Влажность
    PT_PRESS, // Давление
            
    // discrete        
            
    PT_LIGHT, // Свет вкл-выкл
    PT_DOOR_OPEN, // Дверь откр-закр
    PT_YES_NO, // Да или нет
       
    // Прогноз погоды
    PT_CAST_DATE, // Для прогноза погоды dd mmm    HI - mon (0..11) LO - day 1..31      
    PT_CAST_TIME, // 0 - Утро, 1 - День, 2 - вечер, 3 - ночь
    /*
     * Тип погоды, осадки
     * 0 - ясно
     * 1 - облачно
     * 2 - пасмурно
     * 3 - дождь
     * 4 - снег
     * 
    */
    PT_CAST_WEATHER_TYPE, // Тип погоды, осадки
    /*
     * '? ю'
     * '? с'
     * '? з',
     * '? в',
     * ' юз'
     * ' юв'
     * ' сз'
     * ' св'
     */
    PT_CAST_WIND, // Ветер HI - направление, LO - скорость       
            
     
    PT_UNKNOWN = 0xFF        
}ParamTypes;

// Печать названия параметра перед значением
typedef enum
{
    PPN_NONE, // Не печатать
    PPN_FULL, // Полное имя
    PPN_SHORT // Короткое имя  
}PrintParamName;

typedef enum
{
    MRT_COIL,
    MRT_DISCRETE,
    MRT_HOLDING,
    MRT_INPUT        
}RegType;

typedef struct 
{
    uint8_t Column;
    uint8_t Row;
    MainItemTypes Type;
//    void* Value;
    union Value
    {
        struct
        {
            uint8_t strLen;
            char str[SCREEN_WIDTH + 1];
        }Str;
            
        struct
        {
            bool is16Bit;
            uint8_t paramId;
        }ParamNum;
    }Value;

}MainScreenItem;

typedef struct
{
    Buttons Button;
    bool    Is16Bit;
    uint8_t ParamId;
    // Количество значений, которые будут переключаться по кругу 1-2-3
    // 0 - кнопка ничего не делает
    uint8_t ValuesCount;
    uint16_t Value1;
    uint16_t Value2;
    uint16_t Value3;
}QuickButtonParam;


typedef struct
{
    uint8_t rgId;
    uint8_t paramId;
}RegInfoTag;

typedef enum
{
    CB_NONE,        // нормальная работа
    CB_FIRST_BAN,   // первое предупреждение, интервал опроса увеличен
    CB_SECOND_BAN,  // второе предупреждение, большой интервал опроса
    CB_COMPLETE_BAN // сообще не опрашивается TODO надо сделать механизм вытаскивания из бана безе перезагрузки       
}ControllerBan;

typedef struct
{
    uint32_t nextRequest;
    ControllerBan banned;    // Забанен ли контроллер
    uint8_t continousErrors; // Сколько последовательных ошибок запросов было
}ControllerrInterval;


#define QUICK_BUTTON_COUNT 15
QuickButtonParam QuickButtonParams[QUICK_BUTTON_COUNT];


#define DUMMY_ROOM_COUNT 4
uint8_t RoomsCount;// = DUMMY_ROOM_COUNT;
#define MAIN_SCREEN_MAX_COUNT 8
uint8_t MainParamCount[MAIN_SCREEN_MAX_COUNT];
uint8_t MainParamStartAddresses[MAIN_SCREEN_MAX_COUNT];
// Количество главных экранов
uint8_t MainScreenCount;
//uint8_t MainParamCount;



//const uint16_t ParamAddresses_0[] = {0, 1};
//const uint16_t ParamAddresses_1[] = {2, 3, 4};
//const uint16_t ParamAddresses_2[] = {5};
//const uint16_t ParamAddresses_3[] = {6, 7, 8};
//
//typedef struct
//{
//    uint8_t Count;
//    uint16_t *ParamAddresses;// Адрес в EEPROM, где расположена структура с параметром
//}RoomParams;
//const RoomParams roomParams[] =
//{
//    // Спальня
//    //{.Count, .ParamAddresses},
//    {2, ParamAddresses_0},
//    // Ванная
//    {3, ParamAddresses_1},
//    // Коридор
//    {1, ParamAddresses_2}, 
//    // Улица
//    {3, ParamAddresses_3}
//};

//#define DUMMY_PARAMS_COUNT 9
uint16_t ParamCount;// = DUMMY_PARAMS_COUNT;

uint8_t DiscreteParamsCount = 0;
/**
 * Список всех параметров. Ограничен 256
 */
uint16_t _parameters[256];

uint8_t DiscreteParameters[32]; // 256 бит

uint8_t ControllersCount = 0;
#define CONTROLLERS_MAX_COUNT 16
ControllerrInterval ControllersNextRequest[CONTROLLERS_MAX_COUNT];
#define CTRL_REG_BUF_COUNT 16


/*typedef struct 
{
    uint8_t Type;
    uint16_t Value;
}ParameterTag;*/

int8_t InitParameters();


void GetMainScreenParam(uint8_t mainScreenId, uint8_t paramId, MainScreenItem *paramStruct);


//uint8_t GetMainParamCount(uint8_t startScrId);

//Размер буфера 8 = 7 + 1
void GetRoomName(uint8_t room, char* buf);
uint8_t GetRoomParamsCount(uint8_t room);

//uint8_t GetParamCount();
bool SetParameterValue(uint8_t id, uint16_t value);
bool SetDiscreteParameterValue(uint8_t id, bool value);
void SetParameterValueByRoom(uint8_t room, uint8_t param, uint16_t value);
void SetDiscreteParameterValueByRoom(uint8_t room, uint8_t param, bool value);

void GetParameterName(uint8_t id, bool is16bit, char* buf);
void GetParameterNameByRoom(uint8_t room, uint8_t param, char* buf);
ParamTypes GetParameterTypeByRoom(uint8_t room, uint8_t param);

uint16_t GetParameterValue(uint8_t id);
bool GetDiscreteParameterValue(uint8_t id);
uint16_t GetParameterValueByRoom(uint8_t room, uint8_t param);
bool GetDiscreteParameterValueByRoom(uint8_t room, uint8_t param);

uint16_t GetParameterMinByRoom(uint8_t room, uint8_t param);
uint16_t GetParameterMaxByRoom(uint8_t room, uint8_t param);
uint16_t GetParameterStepByRoom(uint8_t room, uint8_t param);

// Controllers for Master
// Получить частоту опроса контроллера в секундах
uint8_t GetControllerRate(uint8_t id);
uint8_t GetControllerAddress(uint8_t id);
uint8_t GetCtrlRegCount(uint8_t id, RegType regType);
// Возвращает количество регистров в структуре
uint8_t FillCtrlRegInfo(uint8_t id, RegType regType, RegInfoTag *regInfo);

#define GetParamAddress(room, param) (roomParams[room].ParamAddresses[param])
bool IsParamEditable(uint8_t room, uint8_t param, bool *is16Bit); 

void PrintDate(MainItemTypes type);
/**
 * Вывод параметра на экран
 * @param paramId           ID параметра
 * @param col               Колонка (-1 - в текущую позицию)
 * @param row               Ряд (-1 - в текущую позицию)
 * @param printParamName    Печатать ли название параметра
 */
void PrintParameter(uint8_t paramId, bool is16bit, int8_t col, int8_t row, PrintParamName printParamName);

void PrintParameterByRoom(uint8_t room, uint8_t param, int8_t col, int8_t row, PrintParamName printParamName);
void PrintParameterByRoomAndValue(uint8_t room, uint8_t param, uint16_t value, int8_t col, int8_t row, PrintParamName printParamName);
void PrintDiscreteParameterByRoomAndValue(uint8_t room, uint8_t param, bool value, int8_t col, int8_t row, PrintParamName printParamName);
void PrintParameterByValue(uint8_t paramId, uint16_t value, int8_t col, int8_t row, PrintParamName printParamName);
void PrintDiscreteParameterByValue(uint8_t paramId, bool value, int8_t col, int8_t row, PrintParamName printParamName);
#endif