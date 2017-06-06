#ifndef PARAMETERSCONTROLLER_H
#define PARAMETERSCONTROLLER_H

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include "LCD/xlcd.h"
#include "buttons.h"


typedef enum
{
    MIT_LITERAL, // ������ ������
    MIT_PARAM, // �������� ���������
    MIT_SHORT, // �������� ��������� � �������� ���������
    MIT_FULL, // �������� ��������� � ������� ��������� 
            
    MIT_TIME, // ������� ����� HH:MM
    MIT_TIME_HOUR,  // ������� ����� (���)
    MIT_TIME_MIN,  // ������� ����� (������)  
            
    MIT_DATE_LONG, // dd  month(8)   year 
    MIT_DATE_FULL, // dow dd mmm year     
    MIT_DATE_CAST, // ��� �������� ������ dd mmm        
    MIT_DATE_NORMAL, // dd.mm.yyyy       
    MIT_DATE_SHORT, // dd.mm.yy             
    MIT_DATE_DAY,
    MIT_DATE_MONTH_STR, // ����� ������
    MIT_DATE_MONTH, // ����� ������
    MIT_DATE_YEAR, // yyyy
    MIT_DATE_YEAR_SHORT, // yy
    MIT_DATE_DAY_OF_WEEK_LONG, // ������� ������
    MIT_DATE_DAY_OF_WEEK_MID, // 3 �������       
    MIT_DATE_DAY_OF_WEEK_SHORT, // 2 �������   
            
//    MIT_CAST_MORNING, // ����   
//    MIT_CAST_DAY,   // ����   
//    MIT_CAST_EVENING,  // �����    
//    MIT_CAST_NIGHT,  // ����
            
    MIT_UNKNOWN = 0xFF      
}MainItemTypes;

typedef enum 
{
    PT_INT,
    PT_UINT,
    PT_FLOAT_1, // �������� ��������� ����� �� 10
    PT_FLOAT_2, // �������� ��������� ����� �� 100
    
    PT_TEMP, // �����������
    PT_HYM, // ���������
    PT_PRESS, // ��������
            
    // discrete        
            
    PT_LIGHT, // ���� ���-����
    PT_DOOR_OPEN, // ����� ����-����
    PT_YES_NO, // �� ��� ���
       
    // ������� ������
    PT_CAST_DATE, // ��� �������� ������ dd mmm    HI - mon (0..11) LO - day 1..31      
    PT_CAST_TIME, // 0 - ����, 1 - ����, 2 - �����, 3 - ����
    /*
     * ��� ������, ������
     * 0 - ����
     * 1 - �������
     * 2 - ��������
     * 3 - �����
     * 4 - ����
     * 
    */
    PT_CAST_WEATHER_TYPE, // ��� ������, ������
    /*
     * '? �'
     * '? �'
     * '? �',
     * '? �',
     * ' ��'
     * ' ��'
     * ' ��'
     * ' ��'
     */
    PT_CAST_WIND, // ����� HI - �����������, LO - ��������       
            
     
    PT_UNKNOWN = 0xFF        
}ParamTypes;

// ������ �������� ��������� ����� ���������
typedef enum
{
    PPN_NONE, // �� ��������
    PPN_FULL, // ������ ���
    PPN_SHORT // �������� ���  
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
    // ���������� ��������, ������� ����� ������������� �� ����� 1-2-3
    // 0 - ������ ������ �� ������
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
    CB_NONE,        // ���������� ������
    CB_FIRST_BAN,   // ������ ��������������, �������� ������ ��������
    CB_SECOND_BAN,  // ������ ��������������, ������� �������� ������
    CB_COMPLETE_BAN // ������ �� ������������ TODO ���� ������� �������� ������������ �� ���� ���� ������������       
}ControllerBan;

typedef struct
{
    uint32_t nextRequest;
    ControllerBan banned;    // ������� �� ����������
    uint8_t continousErrors; // ������� ���������������� ������ �������� ����
}ControllerrInterval;


#define QUICK_BUTTON_COUNT 15
QuickButtonParam QuickButtonParams[QUICK_BUTTON_COUNT];


#define DUMMY_ROOM_COUNT 4
uint8_t RoomsCount;// = DUMMY_ROOM_COUNT;
#define MAIN_SCREEN_MAX_COUNT 8
uint8_t MainParamCount[MAIN_SCREEN_MAX_COUNT];
uint8_t MainParamStartAddresses[MAIN_SCREEN_MAX_COUNT];
// ���������� ������� �������
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
//    uint16_t *ParamAddresses;// ����� � EEPROM, ��� ����������� ��������� � ����������
//}RoomParams;
//const RoomParams roomParams[] =
//{
//    // �������
//    //{.Count, .ParamAddresses},
//    {2, ParamAddresses_0},
//    // ������
//    {3, ParamAddresses_1},
//    // �������
//    {1, ParamAddresses_2}, 
//    // �����
//    {3, ParamAddresses_3}
//};

//#define DUMMY_PARAMS_COUNT 9
uint16_t ParamCount;// = DUMMY_PARAMS_COUNT;

uint8_t DiscreteParamsCount = 0;
/**
 * ������ ���� ����������. ��������� 256
 */
uint16_t _parameters[256];

uint8_t DiscreteParameters[32]; // 256 ���

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

//������ ������ 8 = 7 + 1
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
// �������� ������� ������ ����������� � ��������
uint8_t GetControllerRate(uint8_t id);
uint8_t GetControllerAddress(uint8_t id);
uint8_t GetCtrlRegCount(uint8_t id, RegType regType);
// ���������� ���������� ��������� � ���������
uint8_t FillCtrlRegInfo(uint8_t id, RegType regType, RegInfoTag *regInfo);

#define GetParamAddress(room, param) (roomParams[room].ParamAddresses[param])
bool IsParamEditable(uint8_t room, uint8_t param, bool *is16Bit); 

void PrintDate(MainItemTypes type);
/**
 * ����� ��������� �� �����
 * @param paramId           ID ���������
 * @param col               ������� (-1 - � ������� �������)
 * @param row               ��� (-1 - � ������� �������)
 * @param printParamName    �������� �� �������� ���������
 */
void PrintParameter(uint8_t paramId, bool is16bit, int8_t col, int8_t row, PrintParamName printParamName);

void PrintParameterByRoom(uint8_t room, uint8_t param, int8_t col, int8_t row, PrintParamName printParamName);
void PrintParameterByRoomAndValue(uint8_t room, uint8_t param, uint16_t value, int8_t col, int8_t row, PrintParamName printParamName);
void PrintDiscreteParameterByRoomAndValue(uint8_t room, uint8_t param, bool value, int8_t col, int8_t row, PrintParamName printParamName);
void PrintParameterByValue(uint8_t paramId, uint16_t value, int8_t col, int8_t row, PrintParamName printParamName);
void PrintDiscreteParameterByValue(uint8_t paramId, bool value, int8_t col, int8_t row, PrintParamName printParamName);
#endif