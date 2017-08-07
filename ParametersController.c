#include "ParametersController.h"
#include "MODBUS/ModbusRtu.h"

#include "user.h"
#include "i2c/i2c.h"
#include "interrupts.h"
//#include "ModbusRtu.h"

#define MY_DEBUG


#ifndef MY_DEBUG
#define DummyEERandomRead EERandomRead
#define DummyEESequentialRead EESequentialRead
#endif

#define ROOM_NAME_LEN 7
#define PARAM_NAME_LEN 8
#define MAX_PARAM_COUNT 0x100

#define PI_SIZE 16
#define PI_DISCRETE_SIZE 10
#define PI_TYPE_OFFSET 8
#define PI_EDITABLE_OFFSET 9
#define PI_MIN_OFFSET 10
#define PI_MAX_OFFSET 12
#define PI_STEP_OFFSET 14

#define MIT_COL_OFFSET 0
#define MIT_ROW_OFFSET 1
#define MIT_TYPE_OFFSET 2
#define MIT_VALUE_OFFSET 3


//  uint8_t _paramCount = 8;
const char *daysOfWeekLong[] =
{
    "Воскр.",
    "Понед.",
    "Втор.",
    "Среда",
    "Четв.",
    "Пятн.",
    "Субб.",            
};

const char *daysOfWeekMid[] =
{
    "Вск",
    "Пнд",
    "Втр",
    "Срд",
    "Чтв",
    "Птн",
    "Суб",            
};

const char *daysOfWeekShort[] =
{
    "Вс",
    "Пн",
    "Вт",
    "Ср",
    "Чт",
    "Пт",
    "Сб",            
};

const char *monthesLong[] = 
{
    " Январь ",
    "Февраль ",
    "  Март  ",
    " Апрель ",
    "  Май   ",
    "  Июнь  ",
    "  Июль  ",            
    " Август ",            
    "Сентябрь",            
    "Октябрь ",            
    " Ноябрь ",            
    "Декабрь ",            
};

const char *monthesMid[] = 
{
    "Янв",
    "Фев",
    "Мар",
    "Апр",
    "Май",
    "Июн",
    "Июл",            
    "Авг",            
    "Сен",            
    "Окт",            
    "Ноя",            
    "Дек",            
};


typedef struct
{
    char Name[10];
    uint8_t Type;
    bool editable; // Возможность изменения
    uint16_t min;  // Минимальное значение при возможности изменения
    uint16_t max;  // Максимальное знавчение при возможности изменения
    uint16_t step; // Шаг изменения
}Param;
//char *roomNames[] = 
//{
//    "Спальня",
//    "Ванная ",
//    "Коридор",
//    "Улица  "
//};
//const Param Params[] =
//{
//    // Спальня
//    //{.ParamId, .Name,     .Type,          .Value}, 
//    // макс 8 символов
//    {"Темпер. ", PT_TEMP,      false, 0, 0, 0}, //   0
//    {"Влажн.  ", PT_HYM,       false, 0, 0, 0}, //   1
//    // Ванная
//    {"Свет    ", PT_LIGHT,     false, 0, 0, 0}, //   2 
//    {"Дверь   ", PT_DOOR_OPEN, false, 0, 0, 0}, //   3 
//    {"Игн.дв. ", PT_YES_NO,    true,  0, 1, 1}, //   3 
//    // Коридор
//    {"Свет    ", PT_LIGHT,     false, 0, 0, 0}, //   4 
//    // Улица
//    {"Темпер. ", PT_TEMP,      false, 0, 0, 0}, //   5 
//    {"Влажн.  ", PT_HYM,       false, 0, 0, 0}, //   6 
//    {"Давление", PT_PRESS,     false, 0, 0, 0}, //   7 
//};


// Прогноз погоды:
/*
 * На ближайшее время
 * Символы погоды: Ясно, Снег, дождь, град
 * 
 * 
Дата
0    5    0     |
22 Фев Утро +18С
48% Снег ^ 25м/с
 
 */


uint8_t dummyEe[] =
{
    //Настройки главного экрана
    // Количество экранов
    3, // 0
    // Количество элементов на экране 0
    3, // 1
   //col row    type     len? is16Bit, value
    //0,  0, MIT_DATE_DAY_OF_WEEK_STR, 0,
    
    0,  0, MIT_DATE_DAY_OF_WEEK_LONG, 0,0,
    8,  0, MIT_TIME,                  0,0, // 2
    0,  1, MIT_DATE_LONG,             0,0, // 6
    
    
    // Количество элементов на экране 1
    5, // 10
  //col row    type     len? is16Bit, value
    1,  0, MIT_LITERAL, 6, 'У','л','и','ц','а',':', //1
    8,  0, MIT_PARAM,   1,2, //11
    // 2 строка
    1,  1, MIT_LITERAL, 4, 'Д','о','м',':', //16    19
    6,  1, MIT_PARAM,   1,0, //24
    11, 1, MIT_PARAM,   1,1, //29
    
    // Прогноз погоды
    // Количество элементов на экране 2
    6,
    0,  0, MIT_PARAM,   1,5, // 
    7,  0, MIT_PARAM,   1,6, // 
    12, 0, MIT_PARAM,   1,7, // 
    0,  1, MIT_PARAM,   1,8, // 
    4,  1, MIT_PARAM,   1,9, // 
    9,  1, MIT_PARAM,   1,10, // 
    // QuickButtons 34
    //Button,is16Bit,ParamId,ValuesCount, Value1, Value2, Value3 16-битные значения сохраняем HI-LO
    // BIG ENDIAN!
    BTN_ARM,    0,2, 1, LOW_BYTE(MODBUS_TRUE), HIGH_BYTE(MODBUS_TRUE),   0,0,                                             0,0, // 0  10
    BTN_DISARM, 0,2, 1, LOW_BYTE(MODBUS_FALSE), HIGH_BYTE(MODBUS_FALSE), 0,0,                                             0,0, // 1
    BTN_BPS,    0,2, 2, LOW_BYTE(MODBUS_TRUE), HIGH_BYTE(MODBUS_TRUE),   LOW_BYTE(MODBUS_FALSE), HIGH_BYTE(MODBUS_FALSE), 0,0, // 2
    BTN_TRBL,   0,0, 0, 0,0,                                             0,0,                                             0,0, // 3
    BTN_MEM,    0,0, 0, 0,0,                                             0,0,                                             0,0, // 4
    BTN_1,      0,0, 0, 0,0,                                             0,0,                                             0,0, // 5
    BTN_2,      0,0, 0, 0,0,                                             0,0,                                             0,0, // 6
    BTN_3,      0,0, 0, 0,0,                                             0,0,                                             0,0, // 7
    BTN_4,      0,0, 0, 0,0,                                             0,0,                                             0,0, // 8
    BTN_5,      0,0, 0, 0,0,                                             0,0,                                             0,0, // 9
    BTN_6,      0,0, 0, 0,0,                                             0,0,                                             0,0, // 10
    BTN_7,      0,0, 0, 0,0,                                             0,0,                                             0,0, // 11
    BTN_8,      0,0, 0, 0,0,                                             0,0,                                             0,0, // 12
    BTN_9,      0,0, 0, 0,0,                                             0,0,                                             0,0, // 13
    BTN_0,      0,0, 0, 0,0,                                             0,0,                                             0,0, // 14
    
    // 184
    
    
    
    
    

    4, // 4 комнаты // 166
    'С','п','а','л','ь','н','я', //167
    'В','а','н','н','а','я',' ',
    'К','о','р','и','д','о','р',
    'У','л','и','ц','а',' ',' ',
    // roomParams
    // кол-во, первый байт - 1 - 16битный регистр 0 - дискретный
    2,  1,0, 1,1, //
    3,  0,0, 0,1, 0,2,//
    1,  0,3,//
    3,  1,2, 1,3, 1,4,//
    
    
    4, // количество дискретных регистров или катушек
    // Название                      Тип          Редактриуемо
    // Ванная
    'С','в','е','т',' ',' ',' ',' ', PT_LIGHT,     false,   //   0  241
    'Д','в','е','р','ь',' ',' ',' ', PT_DOOR_OPEN, false,   //   1  257
    'И','г','н','.','д','в','.',' ', PT_YES_NO,    true,    //   2  273
    // Коридор
    'С','в','е','т',' ',' ',' ',' ', PT_LIGHT,     false,   //   3  289
    
    11, //Количество 16битных регистров 324
    
    //Params 16-битные значения сохраняем HI-LO 209
    // 0x7f 6 0xff 0 0 20
    // Название                      Тип    Редактриуемо  min  max  step
    // Спальня
    'Т','е','м','п','е','р','.',' ', PT_TEMP,      false, 0,0, 0,0, 0,0, //   0  209
    'В','л','а','ж','н','.',' ',' ', PT_HYM,       false, 0,0, 0,0, 0,0, //   1  225
    // Улица
    'Т','е','м','п','е','р','.',' ', PT_TEMP,      false, 0,0, 0,0, 0,0, //   2  305  313
    'В','л','а','ж','н','.',' ',' ', PT_HYM,       false, 0,0, 0,0, 0,0, //   3  321
    'Д','а','в','л','е','н','и','е', PT_PRESS,     false, 0,0, 0,0, 0,0, //   4  337    
    // Прогноз погоды
    'Д','а','т','а',' ','.',' ',' ', PT_CAST_DATE, false, 0,0, 0,0, 0,0, //   5  321
    'В','р','е','м','я','.',' ',' ', PT_CAST_TIME, false, 0,0, 0,0, 0,0, //   6
    'Т','е','м','п','е','р','.',' ', PT_TEMP,      false, 0,0, 0,0, 0,0, //   7
    'В','л','а','ж','н','.',' ',' ', PT_HYM,       false, 0,0, 0,0, 0,0, //   8
    'О','с','а','д','к','и',' ',' ', PT_CAST_WEATHER_TYPE, false, 0,0, 0,0, 0,0, // 9 
    'В','е','т','е','р',' ',' ',' ', PT_CAST_WIND, false, 0,0, 0,0, 0,0, //  10 
    
//353
    
    // Зона настроек мастера сети
    4, //!!! Количество контроллеров
        // Спальня
        2, // Адрес
        5, // Частота опроса в секундах
        0,  // Количество катушек
        0,  // Количество дискретных регистров
        0,  // Количество регистров хранения
        2,  // Количество регистров 
            // Индекс / Ид 16-битного параметра
            2, 0, // температура
            3, 1, // влажность
        // Балкон
        15, // Адрес
        5, // Частота опроса в секундах
        0,  // Количество дискретных регистров
        0,  // Количество дискретных регистров
        0,  // Количество регистров хранения
        3,  // Количество регистров
            // Индекс / Ид 16-битного параметра
            1, 2, // Вычисленная температура
            4, 3, // Влажность
            5, 4, // Давление
        // Датчик движения в коридоре
        1, // Адрес
        0, // Частота опроса в секундах
        1,  // Количество дискретных регистров
            // Индекс / Ид 1-битного параметра
            3, 3, // Движение в коридоре 
        0,  // Количество катушек
        0,  // Количество регистров хранения
        0,  // Количество регистров
        // Ванна
        3, // Адрес
        0, // Частота опроса в секундах
        0,  // Количество катушек
        2,  // Количество дискретных регистров
            // Индекс / Ид 1-битного параметра
            0, 0, // Дверь открыта
            1, 0, // Свет включён
        0,  // Количество регистров хранения
        0,  // Количество регистров
            
        
    
    // Адреса устройст и регистры, откуда брать значения параметров и с какой частотой
    // Адрес (1 байт) / тип (1 байт) 0 - дискретный, 1 - катушка, 2 - регистр, 3 - записываемый регистр / частота опроса (1 байт) 0 - постоянно, > 0 - в секундах
    
    
    // Подписчики на изменения
    // Для упрощения только катушки и регистры хранения. Никаких команд
    1, // Количество подписчиков
    // Ид параметра / Тип параметра(is16Bit) / MODBUS адрес / номер регистра или катушки
    2, 0, 3, 0//... 
};

int16_t roomNamesStartAddr = 0;
int16_t roomParamsStartAddr = 0;
int16_t discreteParamsInfoStartAddr = 0;
int16_t paramsInfoStartAddr = 0;
int16_t _controllersStartAddr = 0;

bool initialized = false;




#ifdef MY_DEBUG
int16_t DummyEERandomRead( uint8_t control,  uint16_t address )
{
    return dummyEe[address];
}
int8_t DummyEESequentialRead(uint8_t control, uint16_t address, uint8_t *rdptr, uint8_t length)
{
    for(uint16_t i = 0; i < length; i++)
    {
        rdptr[i] = dummyEe[address + i];
    }
}
#endif

int8_t InitParameters()
{
    // Начальное заполнение для теста
    uint16_t as =  sizeof(dummyEe);
    //WriteI2C_W(as);
    int16_t res;    
    //!!!!!!
    
    
#if 0
    WP_LATCH = 0; // Снимаем защиту от записи
    __delay_ms(5);
    EEArrayWrite(EXT_MEM_COMMAND, 0, dummyEe, sizeof(dummyEe));
    WP_LATCH = 1;
    __delay_ms(5);
    #define RBUF_LEN 0x20
    unsigned char arrayrd[RBUF_LEN];    
    for (uint24_t i = 0; i < as; i += RBUF_LEN)
    {

        DummyEESequentialRead(EXT_MEM_COMMAND, i, arrayrd, RBUF_LEN);
        PortWrite(arrayrd, RBUF_LEN);
    }   
#endif    
    res = DummyEERandomRead(EXT_MEM_COMMAND, 0);
    if(res < 0)
        return -10 + res;
    
    MainScreenCount = res;     

    
    if(MainScreenCount == 0 || MainScreenCount == 0xff) // Данные незагружены или неверны
        return -1;
    
    if(MainScreenCount > MAIN_SCREEN_MAX_COUNT)
        return -10 + res;
    
    
//    uint8_t bbb[10];
//    DummyEESequentialRead(0xA0, 0, bbb, 10);
//    
//    
//    DisplayPrintInt(DummyEERandomRead(0xA0, 1), DEC);
//    DisplayPrintChar(' ');
//    
//    DisplayPrintInt(DummyEERandomRead(0xA0, 2), DEC);
//    DisplayPrintChar(' ');
//    
//    DisplayPrintInt(DummyEERandomRead(0xA0, 3), DEC);
//    DisplayPrintChar(' ');
//    
//    DisplayPrintInt(DummyEERandomRead(0xA0, 4), DEC);
//    DisplayPrintChar(' ');
//    
//    DisplaySetCursorPos(0, 1);
//    
//    DisplayPrintInt(DummyEERandomRead(0xA0, 5), DEC);
//    DisplayPrintChar(' ');
//    
//    DisplayPrintInt(DummyEERandomRead(0xA0, 6), DEC);
//    DisplayPrintChar(' ');
//    
//    DisplayPrintInt(DummyEERandomRead(0xA0, 7), DEC);
//    DisplayPrintChar(' ');
//    
//    DisplayPrintInt(DummyEERandomRead(0xA0, 8), DEC);
//    DisplayPrintChar(' ');
    
//    WP_LATCH = 0;
//    __delay_ms(5);    
//    res8 = EEByteWrite(0xA0, 0, 123);
//    if(res8 < 0)
//        return -90 + res8;  
//    
//    WP_LATCH = 1;
//    __delay_ms(5);
//    res = DummyEERandomRead(0xA0, 0);
//    if(res < 0)
//        return -10 + res;    
//    DisplayPrintInt(res, DEC);
//    DisplayPrintChar(' ');
    
    
    //DisplaySetCursorPos(0, 1);
    uint16_t curAddress = 1;
    
    for(uint8_t s = 0; s < MainScreenCount; s++)
    {
        res = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
        if(res < 0)
            return -10 + res;
        
        MainParamCount[s] = res;
        curAddress++;
        MainParamStartAddresses[s] = curAddress;
        // Пропускаем параметры
        for(uint8_t i = 0; i < MainParamCount[s]; i++) // Пропускаем предыдущие параметры
        {
            res = DummyEERandomRead(EXT_MEM_COMMAND, curAddress + MIT_TYPE_OFFSET);
            if(res < 0)
                return -2;
            switch(res)
            {
                case MIT_LITERAL:
                    res = DummyEERandomRead(EXT_MEM_COMMAND, curAddress + MIT_VALUE_OFFSET);
                    if(res < 0)
                        return -2;
                    curAddress += 4 + res;
                    break;
                default:
                    curAddress += 5;
                    break;
            }
        }
    }
//    DisplayPrintInt(curAddress, DEC);
//    DisplayPrintChar('-');
    
    //as =  sizeof(QuickButtonParams);
//    DisplayPrintInt(as, DEC);
//    DisplayPrintChar('+');
    DummyEESequentialRead(EXT_MEM_COMMAND, curAddress, (uint8_t *)QuickButtonParams, sizeof(QuickButtonParams));
    curAddress += sizeof(QuickButtonParams);
    
#ifdef MY_DEBUG
    DisplayPrintInt(curAddress, DEC);
    DisplayPrintChar(':');
#endif    
    
    res = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
    if(res < 0)
        return -5;
    RoomsCount = res;
#ifdef MY_DEBUG    
    DisplayPrintInt(res, DEC);
    DisplayPrintChar(' ');
#endif     
    roomNamesStartAddr = curAddress + 1; 
    

    roomParamsStartAddr = roomNamesStartAddr + RoomsCount * ROOM_NAME_LEN;
    
    

    curAddress = roomParamsStartAddr;
    uint16_t allRooms16BitParamCount = 0;
    uint16_t allRoomsDiscreteParamCount = 0;
    for(uint8_t i = 0; i < RoomsCount; i++) // Пропускаем предыдущие параметры
    {
        uint8_t roomParamCount = 0;
        res = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
        if(res < 0)
            return -2;
        roomParamCount = res;
        for(uint8_t p = 0; p < roomParamCount; p++)
        {
            res = DummyEERandomRead(EXT_MEM_COMMAND, curAddress + 1 + (p << 1));
            if(res < 0)
                return -2;   
            if(res != 0)
                allRooms16BitParamCount++;
            else
                allRoomsDiscreteParamCount++;                
        }
        curAddress += 1 + (roomParamCount << 1);
    }
    if(allRooms16BitParamCount > MAX_PARAM_COUNT || allRoomsDiscreteParamCount > MAX_PARAM_COUNT)
        return -4;
    
    res = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
#ifdef MY_DEBUG
    DisplaySetCursorPos(0, 1);
    DisplayPrintInt(res, DEC);
    DisplayPrintChar('/');
    DisplayPrintInt(allRoomsDiscreteParamCount, DEC);
    DisplayPrintChar(']');
#endif      
    if(res < 0 || res < allRoomsDiscreteParamCount || res > MAX_PARAM_COUNT)
        return -3;
    
    
    DiscreteParamsCount = res;
    
    discreteParamsInfoStartAddr = curAddress + 1;
    for(uint8_t i = 0; i < (DiscreteParamsCount >> 3); i++)
    {
       DiscreteParameters[i] = 0; 
    }    
    curAddress += 1 + DiscreteParamsCount * PI_DISCRETE_SIZE;
    
    res = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
    if(res < 0 || res < allRooms16BitParamCount || res > MAX_PARAM_COUNT)
        return -3;
    ParamCount = res;
//    DisplayPrintInt(res, DEC);
//    DisplayPrintChar(' ');

    paramsInfoStartAddr = curAddress + 1;
#ifdef SERIAL_DEBUG
    DebugPrintValue("paramsInfoStartAddr", paramsInfoStartAddr);
#endif     
    
    
    for(uint8_t i = 0; i < ParamCount; i++)
    {
       _parameters[i] = 0; 
    }
    
    curAddress += 1 + ParamCount * PI_SIZE;
    res = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
    if(res < 0 || res > CONTROLLERS_MAX_COUNT)
        return -3;
    ControllersCount = res;
#ifdef SERIAL_DEBUG
    DebugPrintValue("ControllersCount", ControllersCount);
#endif        
    _controllersStartAddr = curAddress + 1;
#ifdef SERIAL_DEBUG
    DebugPrintValue("_controllersStartAddr", _controllersStartAddr);
#endif 
    // Очищаем массив
    for(uint8_t i = 0; i < ControllersCount; i++)
    {
       ControllerrInterval tmpStruct; 
       tmpStruct.nextRequest = 0;
       tmpStruct.banned = CB_NONE;
       tmpStruct.continousErrors = 0;
       ControllersNextRequest[i] = tmpStruct; 
    }
    
    
    
    initialized = true;
    
//    _parameters[0] = 22;
//    _parameters[1] = 54;
//    
//    _parameters[2] = MODBUS_TRUE;   
//    _parameters[3] = MODBUS_FALSE;
//    _parameters[4] = MODBUS_FALSE;
//    
//    _parameters[5] = MODBUS_FALSE;
//    
//    _parameters[6] = -12;
//    _parameters[7] = 96;
//    _parameters[8] = 446;
    
    
    return 0;
}






void GetMainScreenParam(uint8_t mainScreenId, uint8_t paramId, MainScreenItem *paramStruct)
{
    paramStruct->Type = MIT_UNKNOWN;
    if(mainScreenId >= MainScreenCount)
        return;
    if(paramId >= MainParamCount[mainScreenId])
        return;
    int16_t res;
    uint16_t curAddress = MainParamStartAddresses[mainScreenId];
    // Пропускаем параметры
    for(uint8_t i = 0; i < paramId; i++) // Пропускаем предыдущие параметры
    {
        res = DummyEERandomRead(EXT_MEM_COMMAND, curAddress + MIT_TYPE_OFFSET);
        if(res < 0)
        {
            paramStruct->Type = MIT_UNKNOWN;
            return;
        }
        switch(res)
        {
            case MIT_LITERAL:
                res = DummyEERandomRead(EXT_MEM_COMMAND, curAddress + MIT_VALUE_OFFSET);
                if(res < 0 || res > SCREEN_WIDTH)
                    return;
                curAddress += 4 + res;
                break;
            default:
                curAddress += 5;
                break;
        }
    }
    
    res = DummyEERandomRead(EXT_MEM_COMMAND, curAddress + MIT_VALUE_OFFSET);
    if(res < 0)
        return;
    
    DummyEESequentialRead(EXT_MEM_COMMAND, curAddress, (uint8_t *)paramStruct, 5);

    
    switch(paramStruct->Type)
    {
        case MIT_LITERAL:            
        {
            uint8_t lenToRead = paramStruct->Value.Str.strLen;
            // Первый символ строки должен быть уже прочитан
            DummyEESequentialRead(EXT_MEM_COMMAND | EXT_MEM_CHIP_0, curAddress + MIT_VALUE_OFFSET + 2, paramStruct->Value.Str.str + 1, lenToRead - 1);
            paramStruct->Value.Str.str[lenToRead] = 0;
        }
            break;
    }

}





void GetRoomName(uint8_t room, char* buf)
{
    if(!initialized || room >= RoomsCount)
        return;
    
    
    DummyEESequentialRead(EXT_MEM_COMMAND, roomNamesStartAddr + ROOM_NAME_LEN * room, buf, ROOM_NAME_LEN);
    
    
    
//    for(i = 0; i < ROOM_NAME_LEN; i++)
//    {
//        buf[i] = roomNames[i];
//    }
    buf[ROOM_NAME_LEN] = 0;
}

uint8_t GetRoomParamsCount(uint8_t room)
{
    if(!initialized || room >= RoomsCount)
        return 0; 
    uint16_t curAddress = roomParamsStartAddr;
    int16_t paramsCount = 0;
    for(uint8_t i = 0; i <= room; i++) // Пропускаем предыдущие параметры
    {
        paramsCount = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
        if(paramsCount < 0)
            return 0;
        curAddress += 1 + (paramsCount << 1);
    }
    return paramsCount;
}

//uint8_t GetParamCount()
//{
//    return ParamCount;
//}



//#define ParamInfoStartAdd(param) (paramsInfoStartAddr + PI_SIZE * + PI_EDITABLE_OFFSET)

uint8_t GetParamInfoId(uint8_t room, uint8_t param, bool *is16Bit)
{
    uint16_t curAddress = roomParamsStartAddr;
    int16_t res = 0;
    for(uint8_t i = 0; i < room; i++) // Пропускаем предыдущие параметры
    {
        res = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
        if(res < 0)
            return 0;
        curAddress += 1 + (res << 1);
    }
    res = DummyEERandomRead(EXT_MEM_COMMAND, curAddress); // count
    if(res < param - 1)
        return 0;
    curAddress += 1 + (param << 1);
    res = DummyEERandomRead(EXT_MEM_COMMAND, curAddress); // is 16 bit register
    if(res < 0)
        return 0;
    *is16Bit = res;
    res = DummyEERandomRead(EXT_MEM_COMMAND, curAddress + 1); // paramInfoId
    if(res < 0)
        return 0;
   
    return res;
}

uint16_t GetParamInfoStartAdd(uint8_t pid, bool is16Bit)
{
    if(is16Bit)
        return paramsInfoStartAddr + PI_SIZE * pid;
    
    return discreteParamsInfoStartAddr + PI_DISCRETE_SIZE * pid;
    
}

uint16_t GetParamInfoStartAddByRoom(uint8_t room, uint8_t param, bool *is16Bit)
{
    uint8_t pid = GetParamInfoId(room, param, is16Bit);
    
    return GetParamInfoStartAdd(pid, *is16Bit);
}

bool IsParamEditable(uint8_t room, uint8_t param, bool *is16Bit)
{
    if(!initialized || room >= RoomsCount)
        return false;
    
    uint16_t addr = GetParamInfoStartAddByRoom(room, param, is16Bit);
    if(addr == 0)
        return false;
    
    int16_t res = DummyEERandomRead(EXT_MEM_COMMAND, addr + PI_EDITABLE_OFFSET);
    if(res < 0)
        return false;
    
    return res;
}

bool SetParameterValue(uint8_t id, uint16_t value)
{
    if(id >= ParamCount)
        return false;
    if(_parameters[id] == value)
        return true;
    
    _parameters[id] = value;
    
    
    
    
    return true;
}

bool SetDiscreteParameterValue(uint8_t id, bool value)
{
    if(id >= DiscreteParamsCount)
        return false;
    
    
    uint8_t u8currentByte = (uint8_t) (id >> 3); // / 8
    uint8_t u8currentBit = (uint8_t) (id & 0x07);

    if(bitRead(DiscreteParameters[u8currentByte], u8currentBit) == value)
        return true;
    
    bitWrite(DiscreteParameters[u8currentByte], u8currentBit, value);
    
    // Если есть подписчики, то добавляем в очередь рассылки
    
    
    
    return true;
}

void SetParameterValueByRoom(uint8_t room, uint8_t param, uint16_t value)
{
    bool is16Bit;
    uint8_t pid = GetParamInfoId(room, param, &is16Bit);
    if(!is16Bit)
        return;
    _parameters[pid] = value;
}

void SetDiscreteParameterValueByRoom(uint8_t room, uint8_t param, bool value)
{
    bool is16Bit;
    uint8_t pid = GetParamInfoId(room, param, &is16Bit);
    if(is16Bit)
        return;
    SetDiscreteParameterValue(pid, value);
}

uint16_t GetParameterValue(uint8_t id)
{
    if(id >= ParamCount)
        return 0;
    return _parameters[id];
}

bool GetDiscreteParameterValue(uint8_t id)
{
    if(id >= DiscreteParamsCount)
        return 0;
    uint8_t u8currentByte = (uint8_t) (id >> 3); // / 8
    uint8_t u8currentBit = (uint8_t) (id & 0x07);

    return bitRead(DiscreteParameters[u8currentByte], u8currentBit);
}
/**
 * Заполнение массива именем параметра
 * @param buf Массив [9]: 8 букв + 1 последний ноль
 */
void GetParameterNameByRoom(uint8_t room, uint8_t param, char* buf)
{
    if(!initialized || room >= RoomsCount)
        return;
    
    bool is16Bit;
    uint8_t pid = GetParamInfoId(room, param, &is16Bit);
    GetParameterName(pid, is16Bit, buf);
    
    
//    uint16_t addr = GetParamInfoStartAdd(room, param);
//    if(addr == 0)
//        return false;
//    
//    DummyEESequentialRead(EXT_MEM_COMMAND | EXT_MEM_CHIP_0, addr, buf, PARAM_NAME_LEN);
    
}

void GetParameterName(uint8_t id, bool is16bit, char* buf)
{
    uint16_t startAddr = GetParamInfoStartAdd(id, is16bit);
    
    DummyEESequentialRead(EXT_MEM_COMMAND, startAddr, buf, PARAM_NAME_LEN);


//    //Пока тупо, потом сделать заполнение массива из еепром
//    uint8_t i;
//    for(i = 0; i < 8; i++)
//        buf[i] = Params[id].Name[i];
    buf[PARAM_NAME_LEN] = 0;    
}

uint16_t GetParameterValueByRoom(uint8_t room, uint8_t param)
{
    bool is16Bit;
    uint8_t pid = GetParamInfoId(room, param, &is16Bit);
    if(!is16Bit)
        return 0;
    return _parameters[pid];
}

bool GetDiscreteParameterValueByRoom(uint8_t room, uint8_t param)
{
    bool is16Bit;
    uint8_t pid = GetParamInfoId(room, param, &is16Bit);
    if(is16Bit)
        return false;
    return GetDiscreteParameterValue(pid);
}

ParamTypes GetParameterType(uint8_t paramId, bool is16bit)
{
    uint16_t startAddr = GetParamInfoStartAdd(paramId, is16bit);
    
    int16_t res = DummyEERandomRead(EXT_MEM_COMMAND, startAddr + PI_TYPE_OFFSET);
    if(res < 0)
        return PT_UNKNOWN;
    return res;
}

ParamTypes GetParameterTypeByRoom(uint8_t room, uint8_t param)
{
    if(!initialized || room >= RoomsCount)
        return 0;

    bool is16Bit;
    uint8_t pid = GetParamInfoId(room, param, &is16Bit);

    return GetParameterType(pid, is16Bit);
    

    
}

//typedef enum 
//{
//    PI_MIN_V,
//    PI_MAX_V,
//    PI_STEP_V
//    
//}Mmsv;

uint16_t GetParameterMinMaxStepByRoom(uint8_t room, uint8_t param, uint8_t offset)
{
    if(!initialized || room >= RoomsCount)
        return 0;

    bool is16Bit; 
    uint16_t addr = GetParamInfoStartAddByRoom(room, param, &is16Bit);
    if(!is16Bit)
        return 0;
    if(addr == 0)
        return 0;
    
    int16_t res = DummyEERandomRead(EXT_MEM_COMMAND, addr + offset);
    if(res < 0)
        return 0;
    
    uint16_t min = (res & 0xFF) << 8;

    int16_t res = DummyEERandomRead(EXT_MEM_COMMAND, addr + offset + 1);
    if(res < 0)
        return 0;

    min |= (res & 0xFF);
    return min;
    
}

uint16_t GetParameterMinByRoom(uint8_t room, uint8_t param)
{
    return GetParameterMinMaxStepByRoom(room, param, PI_MIN_OFFSET);
}
uint16_t GetParameterMaxByRoom(uint8_t room, uint8_t param)
{
    return GetParameterMinMaxStepByRoom(room, param, PI_MAX_OFFSET);
}
uint16_t GetParameterStepByRoom(uint8_t room, uint8_t param)
{
    return GetParameterMinMaxStepByRoom(room, param, PI_STEP_OFFSET);    
}

void PrintParameterByRoom(uint8_t room, uint8_t param, int8_t col, int8_t row, PrintParamName printParamName)
{
    bool is16Bit;
    uint8_t pid = GetParamInfoId(room, param, &is16Bit);
    
    PrintParameter(pid, is16Bit, col, row, printParamName);

}

void PrintParameter(uint8_t paramId, bool is16bit, int8_t col, int8_t row, PrintParamName printParamName)
{
    if(is16bit)
        PrintParameterByValue(paramId, _parameters[paramId], col, row, printParamName);
    else
        PrintDiscreteParameterByValue(paramId, GetDiscreteParameterValue(paramId), col, row, printParamName);
}

void PrintParameterByRoomAndValue(uint8_t room, uint8_t param, uint16_t value, int8_t col, int8_t row, PrintParamName printParamName)
{
    bool is16Bit;
    uint8_t pid = GetParamInfoId(room, param, &is16Bit);
    if(!is16Bit)
        return;
   PrintParameterByValue(pid, value, col, row, printParamName);
}
void PrintDiscreteParameterByRoomAndValue(uint8_t room, uint8_t param, bool value, int8_t col, int8_t row, PrintParamName printParamName)
{
    bool is16Bit;
    uint8_t pid = GetParamInfoId(room, param, &is16Bit);
    if(is16Bit)
        return;
    
    PrintDiscreteParameterByValue(pid, value, col, row, printParamName);
}


void PrintDateByValue(MainItemTypes type, uint8_t day, uint8_t dayOfWeek, uint8_t month, uint16_t year)
{
    if(day < 1 || day > 31)
        day = 1;
    if(month > 11)
        month = 0;
    if(dayOfWeek > 6)
        dayOfWeek = 0;
    switch (type)
    {
        
        case MIT_DATE_DAY:
        {
            DisplayPrintUInt(day, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
        }
        break;
        case MIT_DATE_LONG: // dd  month(8)   year 
        {
            DisplayPrintUInt(day, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
            DisplayPrintChar(' ');
            DisplayPrintStr(monthesLong[month]);
            DisplayPrintChar(' ');
            DisplayPrintUInt(year + 1900, DEC);
        }
            break;
        case MIT_DATE_CAST: // Для прогноза погоды dd mmm        
        {
            DisplayPrintUInt(day, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
            DisplayPrintChar(' ');
            DisplayPrintStr(monthesMid[month]);
        }
        break;
        case MIT_DATE_NORMAL: // dd.mm.yyyy       
        {
            DisplayPrintUInt(day, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
            DisplayPrintChar('.');
            DisplayPrintUInt(month + 1, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
            DisplayPrintChar('.');
            DisplayPrintUInt(year + 1900, DEC);
        }
            break;
        case MIT_DATE_FULL: // dow dd mmm year     
        {
            DisplayPrintStr(daysOfWeekMid[dayOfWeek]);
            DisplayPrintChar(' ');
            DisplayPrintUInt(day, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
            DisplayPrintChar(' ');
            DisplayPrintStr(monthesMid[month]);
            DisplayPrintChar(' ');
            DisplayPrintUInt(year + 1900, DEC);
        }
            break;
        case MIT_DATE_SHORT: // dd.mm.yy   
        {
            DisplayPrintUInt(day, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
            DisplayPrintChar('.');
            DisplayPrintUInt(month + 1, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
            DisplayPrintChar('.');
            DisplayPrintUInt(year - 100, DEC);
        }
            break;
        case MIT_DATE_MONTH_STR: // Месяц словом
        {
            DisplayPrintStr(monthesLong[month]);
        }
            break;
        case MIT_DATE_MONTH: // Месяц цифрой
        {
            DisplayPrintUInt(month + 1, DEC | SHOW_USE_FIELD_SIZE | SHOW_STARTING_ZEROES | FIELD_SIZE(2));
        }
            break;
        case MIT_DATE_YEAR: // yyyy
        {
            DisplayPrintUInt(year + 1900, DEC);
        }
            break;
        case MIT_DATE_YEAR_SHORT: // yy
        {
            DisplayPrintUInt(year - 100, DEC);
        }
            break;
        case MIT_DATE_DAY_OF_WEEK_LONG: // Длинная строка
        {
            DisplayPrintStr(daysOfWeekLong[dayOfWeek]);
        }
            break;
        case MIT_DATE_DAY_OF_WEEK_MID: // 3 символа     
        {
            DisplayPrintStr(daysOfWeekMid[dayOfWeek]);
        }
            break;
        case MIT_DATE_DAY_OF_WEEK_SHORT: // 2 символа     
        {
            DisplayPrintStr(daysOfWeekShort[dayOfWeek]);
        }
            break;    
    }   
}
/**
 * Печать даты в текущую позицию
 * @param type
 */
void PrintDate(MainItemTypes type)
{
    struct tm *timeStruct = localtime((const time_t*)GetTime());    
    PrintDateByValue(type, timeStruct->tm_mday, timeStruct->tm_wday, timeStruct->tm_mon, timeStruct->tm_year);
     
}

void PrintParameterByValue(uint8_t paramId, uint16_t value, int8_t col, int8_t row, PrintParamName printParamName)
{
    if(col >= 0 && row >= 0)
        DisplaySetCursorPos(col, row);
    
    
    switch(printParamName)
    {
        case PPN_FULL:
        {
            char buf[PARAM_NAME_LEN + 1];   ///!!!!!!!!!!!!!!! *
            GetParameterName(paramId, true, buf);
            DisplayPrintStr((const char *)buf);
            DisplayPrintChar(' ');
        }
            break;
        case PPN_SHORT:
        {
            
        }
            break;
    }
    uint8_t paramType = GetParameterType(paramId, true);
    switch(paramType)
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
        // Прогноз погоды
        case PT_CAST_DATE:
        {
            if(printParamName == PPN_SHORT)
                DisplayPrintStr("д ");
            PrintDateByValue(MIT_DATE_CAST, LOW_BYTE(value), 0, HIGH_BYTE(value), 0);
        }
            break; 
        case PT_CAST_TIME:
        {
            if(printParamName == PPN_SHORT)
                DisplayPrintStr("в ");
            char *t = "Утро";
            switch(value)
            {
                case 1:
                   t = "День";
                   break;
                case 2:
                    t = "Веч.";
                   break;
                case 3:
                    t = "Ночь";
                   break;
            }
            DisplayPrintStr((const char *)t); 
        }
            break;   
        case PT_CAST_WEATHER_TYPE:
        {
            if(printParamName == PPN_SHORT)
                DisplayPrintStr("о ");
            
            char *t = "Ясно";
            switch(value)
            {

                case 1:
                   t = "Обл.";
                   break;
                case 2:
                    t = "Пасм";
                   break;
                case 3:
                    t = "Дожд";
                   break;
                case 4:
                    t = "Снег";
                   break;
            }
            DisplayPrintStr((const char *)t); 
        }
            break;    
        case PT_CAST_WIND:
        {
            if(printParamName == PPN_SHORT)
                DisplayPrintStr("в ");
            
            uint8_t dir = HIGH_BYTE(value);
            /*
            * 0 'с'
            * 1 'св'
            * 2 'в',
            * 3 'юв',
            * 4 'ю'
            * 5 'юз'
            * 6 'з'
            * 7 'сз'
            */
            char t = CH_ARROW_DOWN;
            switch(dir)
            {
                case 1:
                   t = CH_ARROW_LEFT_BOTTOM;
                   break;
                case 2:
                    t = '<';
                   break;
                case 3:
                    t = CH_ARROW_LEFT_TOP;
                   break;
                case 4:
                    t = CH_ARROW_UP;
                   break;
                case 5:
                    t = CH_ARROW_RIGHT_TOP;
                   break;
                case 6:
                    t = '>' ;
                   break;
                case 7:
                    t = CH_ARROW_RIGHT_BOTTOM;
                   break;
            }
            DisplayPrintSymbol(t); 
            DisplayPrintChar(' '); 
            DisplayPrintUInt(LOW_BYTE(value), DEC | SHOW_USE_FIELD_SIZE | FIELD_SIZE(2));
            DisplayPrintStr("м/с");
        }
            break;    
    }    
}

void PrintDiscreteParameterByValue(uint8_t paramId, bool value, int8_t col, int8_t row, PrintParamName printParamName)
{
    if(col >= 0 && row >= 0)
        DisplaySetCursorPos(col, row);
    
    
    switch(printParamName)
    {
        case PPN_FULL:
        {
            char buf[PARAM_NAME_LEN + 1]; //!!!!!!!!!!!!!!!!!!*
            GetParameterName(paramId, false, buf);
            DisplayPrintStr((const char *)buf);
            DisplayPrintChar(' ');
        }
            break;
        case PPN_SHORT:
        {
            
        }
            break;
    }
    uint8_t paramType = GetParameterType(paramId, false);
    switch(paramType)
    {
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

// Controllers for Master ======================================================

uint16_t GetControllerStartAddress(uint8_t id)
{
    if(!initialized || id > ControllersCount - 1)
        return 0;
    
    uint16_t curAddress = _controllersStartAddr;
    int16_t tmp;
    for(uint8_t i = 0; i < id; i++) // Пропускаем предыдущие параметры
    {
        curAddress += 2;
        // Количество катушек 
        tmp = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
        if(tmp < 0)
            return 0;
        curAddress++;
        if(tmp > 0)
            curAddress += (tmp << 1);        
        // Количество дискретных регистров
        tmp = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
        if(tmp < 0)
            return 0;
        curAddress++;
        if(tmp > 0)
            curAddress += (tmp << 1);
        // Количество регистров хранения 
        tmp = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
        if(tmp < 0)
            return 0;
        curAddress++;
        if(tmp > 0)
            curAddress += (tmp << 1);
        // Количество регистров
        tmp = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
        if(tmp < 0)
            return 0;
        curAddress++;
        if(tmp > 0)
            curAddress += (tmp << 1);
    }
    return curAddress;
}

uint8_t GetControllerRate(uint8_t id)
{
    uint16_t curAddress = GetControllerStartAddress(id);    
    if(curAddress == 0)
        return 0;
    
    int16_t tmp = DummyEERandomRead(EXT_MEM_COMMAND, curAddress + 1);
        if(tmp < 0)
            return 0;
    return tmp;
}

uint8_t GetControllerAddress(uint8_t id)
{
    uint16_t curAddress = GetControllerStartAddress(id);    
    if(curAddress == 0)
        return 0;
    
    int16_t tmp = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
        if(tmp < 0)
            return 0;
    return tmp;
}

uint8_t GetCtrlRegCount(uint8_t id, RegType regType)
{
    uint16_t curAddress = GetControllerStartAddress(id);  
    if(curAddress == 0)
        return 0;
    
    curAddress += 2;
    int16_t tmp;
    for(uint8_t i = 0; i < regType; i++)
    {
        tmp = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
        if(tmp < 0)
            return 0;
        curAddress++;
        if(tmp > 0)
            curAddress += (tmp << 1);
    }
    
    tmp = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
    if(tmp < 0)
        return 0;
    return tmp;
}

uint8_t FillCtrlRegInfo(uint8_t id, RegType regType, RegInfoTag *regInfo)
{
    //CTRL_REG_BUF_COUNT
    uint16_t curAddress = GetControllerStartAddress(id);  
    if(curAddress == 0)
        return 0;
    
    curAddress += 2;
    int16_t tmp;
    for(uint8_t i = 0; i < regType; i++)
    {
        tmp = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
        if(tmp < 0)
            return 0;
        curAddress++;
        if(tmp > 0)
            curAddress += (tmp << 1);
    }
    
    uint8_t cnt = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
    if(cnt < 0)
        return 0;
    
    if(cnt > CTRL_REG_BUF_COUNT)
        return 0;
        
    for(uint8_t i = 0; i < cnt; i++)
    {
        curAddress++;
        
        tmp = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
        if(tmp < 0)
            return 0;
        
        regInfo[i].rgId = tmp;
        
        curAddress++;
        
        tmp = DummyEERandomRead(EXT_MEM_COMMAND, curAddress);
        if(tmp < 0)
            return 0;
        
        regInfo[i].paramId = tmp;
    }
    
    return cnt;
}