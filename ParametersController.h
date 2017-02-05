#ifndef PARAMETERSCONTROLLER_H
#define PARAMETERSCONTROLLER_H

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */


typedef enum 
{
    PT_INT,
    PT_UINT,
    PT_FLOAT_1, // �������� ��������� ����� �� 10
    PT_FLOAT_2, // �������� ��������� ����� �� 100
    
    PT_TEMP, // �����������
    PT_HYM, // ���������
    PT_PRESS, // ��������
    PT_LIGHT, // ���� ���-����
    PT_DOOR_OPEN, // ����� ����-����
    PT_YES_NO // �� ��� ���
}ParamTypes;

// ������ �������� ��������� ����� ���������
typedef enum
{
    PPN_NONE, // �� ��������
    PPN_FULL, // ������ ���
    PPN_SHORT // �������� ���  
}PrintParamName;

#define DUMMY_ROOM_COUNT 4
char *roomNames[] = 
{
    "�������",
    "������",
    "�������",
    "�����"
};

const uint16_t ParamAddresses_0[] = {0, 1};
const uint16_t ParamAddresses_1[] = {2, 3, 4};
const uint16_t ParamAddresses_2[] = {5};
const uint16_t ParamAddresses_3[] = {6, 7, 8};

typedef struct
{
    uint8_t Count;
    uint16_t *ParamAddresses;// ����� � EEPROM, ��� ����������� ��������� � ����������
}RoomParams;
const RoomParams roomParams[] =
{
    // �������
    //{.Count, .ParamAddresses},
    {2, ParamAddresses_0},
    // ������
    {3, ParamAddresses_1},
    // �������
    {1, ParamAddresses_2}, 
    // �����
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
 * ����� ��������� �� �����
 * @param paramId           ID ���������
 * @param col               ������� (-1 - � ������� �������)
 * @param row               ��� (-1 - � ������� �������)
 * @param printParamName    �������� �� �������� ���������
 */
void PrintParameter(uint8_t paramId, int8_t col, int8_t row, PrintParamName printParamName);

void PrintParameterByRoom(uint8_t room, uint8_t param, int8_t col, int8_t row, PrintParamName printParamName);
void PrintParameterByRoomAndValue(uint8_t room, uint8_t param, uint16_t value, int8_t col, int8_t row, PrintParamName printParamName);
void PrintParameterByValue(uint8_t paramId, uint16_t value, int8_t col, int8_t row, PrintParamName printParamName);
#endif