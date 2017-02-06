#include "ParametersController.h"
#include "ModbusRtu.h"

#include "i2c/i2c.h"


#define ROOM_NAME_LEN 7
#define PARAM_NAME_LEN 8
#define MAX_PARAM_COUNT 0x100

#define PI_SIZE 16
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


typedef struct
{
    char Name[10];
    uint8_t Type;
    bool editable; // ����������� ���������
    uint16_t min;  // ����������� �������� ��� ����������� ���������
    uint16_t max;  // ������������ ��������� ��� ����������� ���������
    uint16_t step; // ��� ���������
}Param;
//char *roomNames[] = 
//{
//    "�������",
//    "������ ",
//    "�������",
//    "�����  "
//};
//const Param Params[] =
//{
//    // �������
//    //{.ParamId, .Name,     .Type,          .Value}, 
//    // ���� 8 ��������
//    {"������. ", PT_TEMP,      false, 0, 0, 0}, //   0
//    {"�����.  ", PT_HYM,       false, 0, 0, 0}, //   1
//    // ������
//    {"����    ", PT_LIGHT,     false, 0, 0, 0}, //   2 
//    {"�����   ", PT_DOOR_OPEN, false, 0, 0, 0}, //   3 
//    {"���.��. ", PT_YES_NO,    true,  0, 1, 1}, //   3 
//    // �������
//    {"����    ", PT_LIGHT,     false, 0, 0, 0}, //   4 
//    // �����
//    {"������. ", PT_TEMP,      false, 0, 0, 0}, //   5 
//    {"�����.  ", PT_HYM,       false, 0, 0, 0}, //   6 
//    {"��������", PT_PRESS,     false, 0, 0, 0}, //   7 
//};


/**
 * ������ ���� ����������. ��������� 256
 */
uint16_t _parameters[256];


uint8_t dummyEe[] =
{
    //��������� �������� ������
    5,
  //col row    type     len? value
    1,  0, MIT_LITERAL, 6, '�','�','�','�','�',':',
    8,  0, MIT_PARAM,   6,
    // 2 ������
    1,  1, MIT_LITERAL, 4, '�','�','�',':',
    6,  1, MIT_PARAM,   0,
    11, 1, MIT_PARAM,   1,
    
    // QuickButtons
    //Button,ParamId,ValuesCount, Value1, Value2, Value3 16-������ �������� ��������� HI-LO
    BTN_ARM,    4, 1, HIGH_BYTE(MODBUS_TRUE), LOW_BYTE(MODBUS_TRUE),   0,0,                                             0,0, // 0
    BTN_DISARM, 4, 1, HIGH_BYTE(MODBUS_FALSE), LOW_BYTE(MODBUS_FALSE), 0,0,                                             0,0, // 1
    BTN_BPS,    4, 2, HIGH_BYTE(MODBUS_TRUE), LOW_BYTE(MODBUS_TRUE),   HIGH_BYTE(MODBUS_FALSE), LOW_BYTE(MODBUS_FALSE), 0,0, // 2
    BTN_TRBL,   0, 0, 0,0,                                             0,0,                                             0,0, // 3
    BTN_MEM,    0, 0, 0,0,                                             0,0,                                             0,0, // 4
    BTN_1,      0, 0, 0,0,                                             0,0,                                             0,0, // 5
    BTN_2,      0, 0, 0,0,                                             0,0,                                             0,0, // 6
    BTN_3,      0, 0, 0,0,                                             0,0,                                             0,0, // 7
    BTN_4,      0, 0, 0,0,                                             0,0,                                             0,0, // 8
    BTN_5,      0, 0, 0,0,                                             0,0,                                             0,0, // 9
    BTN_6,      0, 0, 0,0,                                             0,0,                                             0,0, // 10
    BTN_7,      0, 0, 0,0,                                             0,0,                                             0,0, // 11
    BTN_8,      0, 0, 0,0,                                             0,0,                                             0,0, // 12
    BTN_9,      0, 0, 0,0,                                             0,0,                                             0,0, // 13
    BTN_0,      0, 0, 0,0,                                             0,0,                                             0,0, // 14
    
    
    
    
    
    
    
    
    4, // 4 �������
    '�','�','�','�','�','�','�',
    '�','�','�','�','�','�',' ',
    '�','�','�','�','�','�','�',
    '�','�','�','�','�',' ',' ',
    // roomParams
    2,  0, 1,
    3,  2, 3, 4,
    1,  5,
    3,  6, 7, 8,
    
    DUMMY_PARAMS_COUNT,
    
    //Params 16-������ �������� ��������� HI-LO
    '�','�','�','�','�','�','.',' ', PT_TEMP,      false, 0,0, 0,0, 0,0, //   0 
    '�','�','�','�','�','.',' ',' ', PT_HYM,       false, 0,0, 0,0, 0,0, //   1
    // ������
    '�','�','�','�',' ',' ',' ',' ', PT_LIGHT,     false, 0,0, 0,0, 0,0, //   2 
    '�','�','�','�','�',' ',' ',' ', PT_DOOR_OPEN, false, 0,0, 0,0, 0,0, //   3 
    '�','�','�','.','�','�','.',' ', PT_YES_NO,    true,  0,0, 0,0, 0,0, //   3 
    // �������
    '�','�','�','�',' ',' ',' ',' ', PT_LIGHT,     false, 0,0, 0,0, 0,0, //   4 
    // �����
    '�','�','�','�','�','�','.',' ', PT_TEMP,      false, 0,0, 0,0, 0,0, //   5 
    '�','�','�','�','�','.',' ',' ', PT_HYM,       false, 0,0, 0,0, 0,0, //   6 
    '�','�','�','�','�','�','�','�', PT_PRESS,     false, 0,0, 0,0, 0,0, //   7 

};

int16_t roomNamesStartAddr = 0;
int16_t roomParamsStartAddr = 0;
int16_t paramsInfoStartAddr = 0;

bool initialized = false;


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

int8_t InitParameters()
{
    // ��������� ���������� ��� �����
    uint8_t as =  sizeof(dummyEe);
//    EEPageWrite(0xA0, 0, dummyEe, sizeof(dummyEe));
    
    
    MainParamCount = dummyEe[0];
    if(MainParamCount == 0 || MainParamCount == 0xff) // ������ ����������� ��� �������
        return -1;
    
    int16_t res;
    uint16_t curAddress = 1;
    // ���������� ���������
    for(uint8_t i = 0; i < MainParamCount; i++) // ���������� ���������� ���������
    {
        res = DummyEERandomRead(0xA0, curAddress + MIT_TYPE_OFFSET);
        if(res < 0)
            return -2;
        switch(res)
        {
            case MIT_LITERAL:
                res = DummyEERandomRead(0xA0, curAddress + MIT_VALUE_OFFSET);
                if(res < 0)
                    return -2;
                curAddress += 4 + res;
                break;
            default:
                curAddress += 4;
                break;
        }
    }
    
    uint8_t as =  sizeof(QuickButtonParams);
    DummyEESequentialRead(0xA0, curAddress, QuickButtonParams, sizeof(QuickButtonParams));
    curAddress += sizeof(QuickButtonParams);
    
    
    RoomsCount = dummyEe[curAddress];
    
    roomNamesStartAddr = curAddress + 1; 
    

    roomParamsStartAddr = roomNamesStartAddr + RoomsCount * ROOM_NAME_LEN;
    
    

    curAddress = roomParamsStartAddr;
    uint16_t allRoomsParamCount = 0;
    for(uint8_t i = 0; i < RoomsCount; i++) // ���������� ���������� ���������
    {
        res = DummyEERandomRead(0xA0, curAddress);
        if(res < 0)
            return -2;
        allRoomsParamCount += res;
        curAddress += 1 + res;
    }
    if(allRoomsParamCount > MAX_PARAM_COUNT)
        return -4;
    
    res = DummyEERandomRead(0xA0, curAddress);
    if(res < 0 || res < allRoomsParamCount || res > MAX_PARAM_COUNT)
        return -3;
    
    ParamCount = res;
    paramsInfoStartAddr = curAddress + 1;
    
    
    initialized = true;
    
    _parameters[0] = 22;
    _parameters[1] = 54;
    
    _parameters[2] = MODBUS_TRUE;   
    _parameters[3] = MODBUS_FALSE;
    _parameters[4] = MODBUS_FALSE;
    
    _parameters[5] = MODBUS_FALSE;
    
    _parameters[6] = -12;
    _parameters[7] = 96;
    _parameters[8] = 446;
    
    
    return 0;
}






void GetMainScreenParam(uint8_t paramId, MainScreenItem *paramStruct)
{
    if(paramId >= MainParamCount)
        return;
    paramStruct->Type = MIT_UNKNOWN;
    int16_t res;
    uint16_t curAddress = 1;
    // ���������� ���������
    for(uint8_t i = 0; i < paramId; i++) // ���������� ���������� ���������
    {
        res = DummyEERandomRead(0xA0, curAddress + MIT_TYPE_OFFSET);
        if(res < 0)
        {
            paramStruct->Type = MIT_UNKNOWN;
            return;
        }
        switch(res)
        {
            case MIT_LITERAL:
                res = DummyEERandomRead(0xA0, curAddress + MIT_VALUE_OFFSET);
                if(res < 0 || res > SCREEN_WIDTH)
                    return;
                curAddress += 4 + res;
                break;
            default:
                curAddress += 4;
                break;
        }
    }
    
    res = DummyEERandomRead(0xA0, curAddress + MIT_VALUE_OFFSET);
    if(res < 0)
        return;
    
    DummyEESequentialRead(0xA0, curAddress, (uint8_t *)paramStruct, 4);

    
    switch(paramStruct->Type)
    {
        case MIT_LITERAL:            
        {
            uint8_t lenToRead = paramStruct->Value.paramId;
            DummyEESequentialRead(0xA0, curAddress + MIT_VALUE_OFFSET + 1, paramStruct->Value.str, lenToRead);
            paramStruct->Value.str[lenToRead] = 0;
        }
            break;
    }

}





void GetRoomName(uint8_t room, char* buf)
{
    if(!initialized || room >= RoomsCount)
        return;
    
    
    DummyEESequentialRead(0xA0, roomNamesStartAddr + ROOM_NAME_LEN * room, buf, ROOM_NAME_LEN);
    
    
    
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
    for(uint8_t i = 0; i <= room; i++) // ���������� ���������� ���������
    {
        paramsCount = DummyEERandomRead(0xA0, curAddress);
        if(paramsCount < 0)
            return 0;
        curAddress += 1 + paramsCount;
    }
    return paramsCount;
}

//uint8_t GetParamCount()
//{
//    return ParamCount;
//}



//#define ParamInfoStartAdd(param) (paramsInfoStartAddr + PI_SIZE * + PI_EDITABLE_OFFSET)

uint8_t GetParamInfoId(uint8_t room, uint8_t param)
{
    uint16_t curAddress = roomParamsStartAddr;
    int16_t res = 0;
    for(uint8_t i = 0; i < room; i++) // ���������� ���������� ���������
    {
        res = DummyEERandomRead(0xA0, curAddress);
        if(res < 0)
            return 0;
        curAddress += 1 + res;
    }
    res = DummyEERandomRead(0xA0, curAddress); // count
    if(res < param - 1)
        return 0;
    curAddress += 1 + param;
    res = DummyEERandomRead(0xA0, curAddress); // paramInfoId
    if(res < 0)
        return 0;
    return res;
}


uint16_t GetParamInfoStartAdd(uint8_t room, uint8_t param)
{
    return paramsInfoStartAddr + PI_SIZE * GetParamInfoId(room, param);
}

bool IsParamEditable(uint8_t room, uint8_t param)
{
    if(!initialized || room >= RoomsCount)
        return false;
    
    uint16_t addr = GetParamInfoStartAdd(room, param);
    if(addr == 0)
        return false;
    
    int16_t res = DummyEERandomRead(0xA0, addr + PI_EDITABLE_OFFSET);
    if(res < 0)
        return false;
    
    return res;
}

bool SetParameterValue(uint8_t id, uint16_t value)
{
    if(id >= ParamCount)
        return false;
    _parameters[id] = value;
    return true;
}

void SetParameterValueByRoom(uint8_t room, uint8_t param, uint16_t value)
{
    _parameters[GetParamInfoId(room, param)] = value;
}

uint16_t GetParameterValue(uint8_t id)
{
    if(id >= ParamCount)
        return 0;
    return _parameters[id];
}

/**
 * ���������� ������� ������ ���������
 * @param buf ������ [9]: 8 ���� + 1 ��������� ����
 */
void GetParameterNameByRoom(uint8_t room, uint8_t param, char* buf)
{
    if(!initialized || room >= RoomsCount)
        return;
    
    GetParameterName(GetParamInfoId(room, param), buf);
    
    
//    uint16_t addr = GetParamInfoStartAdd(room, param);
//    if(addr == 0)
//        return false;
//    
//    DummyEESequentialRead(0xA0, addr, buf, PARAM_NAME_LEN);
    
}

void GetParameterName(uint8_t id, char* buf)
{

    DummyEESequentialRead(0xA0, paramsInfoStartAddr + PI_SIZE * id, buf, PARAM_NAME_LEN);


//    //���� ����, ����� ������� ���������� ������� �� ������
//    uint8_t i;
//    for(i = 0; i < 8; i++)
//        buf[i] = Params[id].Name[i];
    buf[PARAM_NAME_LEN] = 0;    
}

uint16_t GetParameterValueByRoom(uint8_t room, uint8_t param)
{
    return _parameters[GetParamInfoId(room, param)];
}

ParamTypes GetParameterType(uint8_t paramId)
{
    
    int16_t res = DummyEERandomRead(0xA0, paramsInfoStartAddr + PI_SIZE * paramId + PI_TYPE_OFFSET);
    if(res < 0)
        return 0;
}

ParamTypes GetParameterTypeByRoom(uint8_t room, uint8_t param)
{
    if(!initialized || room >= RoomsCount)
        return 0;

    return GetParameterType(GetParamInfoId(room, param));
    
//    uint16_t addr = GetParamInfoStartAdd(room, param);
//    if(addr == 0)
//        return 0;
//
//    int16_t res = DummyEERandomRead(0xA0, addr + PI_TYPE_OFFSET);
//    if(res < 0)
//        return 0;
//    
//    return res;
}
uint16_t GetParameterMinByRoom(uint8_t room, uint8_t param)
{
    if(!initialized || room >= RoomsCount)
        return 0;

    uint16_t addr = GetParamInfoStartAdd(room, param);
    if(addr == 0)
        return 0;

    int16_t res = DummyEERandomRead(0xA0, addr + PI_MIN_OFFSET);
    if(res < 0)
        return 0;
    
    uint16_t min = (res & 0xFF) << 8;

    int16_t res = DummyEERandomRead(0xA0, addr + PI_MIN_OFFSET + 1);
    if(res < 0)
        return 0;

    min |= (res & 0xFF);
    return min;
}
uint16_t GetParameterMaxByRoom(uint8_t room, uint8_t param)
{
    if(!initialized || room >= RoomsCount)
        return 0;

    uint16_t addr = GetParamInfoStartAdd(room, param);
    if(addr == 0)
        return 0;

    int16_t res = DummyEERandomRead(0xA0, addr + PI_MAX_OFFSET);
    if(res < 0)
        return 0;
    
    uint16_t max = (res & 0xFF) << 8;

    int16_t res = DummyEERandomRead(0xA0, addr + PI_MAX_OFFSET + 1);
    if(res < 0)
        return 0;

    max |= (res & 0xFF);
    return max;
}
uint16_t GetParameterStepByRoom(uint8_t room, uint8_t param)
{
    if(!initialized || room >= RoomsCount)
        return 0;

    uint16_t addr = GetParamInfoStartAdd(room, param);
    if(addr == 0)
        return 0;

    int16_t res = DummyEERandomRead(0xA0, addr + PI_STEP_OFFSET);
    if(res < 0)
        return 0;
    
    uint16_t step = (res & 0xFF) << 8;

    int16_t res = DummyEERandomRead(0xA0, addr + PI_STEP_OFFSET + 1);
    if(res < 0)
        return 0;

    step |= (res & 0xFF);
    return step;
}

void PrintParameterByRoom(uint8_t room, uint8_t param, int8_t col, int8_t row, PrintParamName printParamName)
{
    PrintParameter(GetParamInfoId(room, param), col, row, printParamName);
}

void PrintParameter(uint8_t paramId, int8_t col, int8_t row, PrintParamName printParamName)
{
    PrintParameterByValue(paramId, _parameters[paramId], col, row, printParamName);
}

void PrintParameterByRoomAndValue(uint8_t room, uint8_t param, uint16_t value, int8_t col, int8_t row, PrintParamName printParamName)
{
    PrintParameterByValue(GetParamInfoId(room, param), value, col, row, printParamName);
}

void PrintParameterByValue(uint8_t paramId, uint16_t value, int8_t col, int8_t row, PrintParamName printParamName)
{
    if(col >= 0 && row >= 0)
        DisplaySetCursorPos(col, row);
    
    
    switch(printParamName)
    {
        case PPN_FULL:
        {
            char *buf[PARAM_NAME_LEN + 1];
            GetParameterName(paramId, buf);
            DisplayPrintStr(buf);
            DisplayPrintChar(' ');
        }
            break;
        case PPN_SHORT:
        {
            
        }
            break;
    }
    
    switch(GetParameterType(paramId))
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
                DisplayPrintStr("� ");
            if(value != MODBUS_FALSE)
                DisplayPrintStr("���");
            else
                DisplayPrintStr("����");
        }
            break;  
        case PT_DOOR_OPEN:
        {
            if(printParamName == PPN_SHORT)
                DisplayPrintStr("� ");
            if(value != MODBUS_FALSE)
                DisplayPrintStr("���");
            else
                DisplayPrintStr("����");
        }
            break;  
        case PT_YES_NO:
        {
            if(printParamName == PPN_SHORT)
                DisplayPrintStr("? ");
            if(value != MODBUS_FALSE)
                DisplayPrintStr("��");
            else
                DisplayPrintStr("���");
        }
            break;      
    }    
}