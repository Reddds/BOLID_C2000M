#include "SectionRooms.h"
#include "../LCD/xlcd.h"
#include "../buttons.h"
#include "../ParametersController.h"




#define DUMMY_ROOM_COUNT 4
// ��������� ������, ������� ����� ����� � EEPROM
uint8_t roomsCount = DUMMY_ROOM_COUNT;
char *roomNames[] = 
{
    "�������",
    "������",
    "�������",
    "�����"
};


typedef struct
{
    uint8_t Count;
    uint16_t *ParamAddresses;// ����� � EEPROM, ��� ����������� ��������� � ����������
}RoomParams;




/*typedef struct
{
    char Name[10];
    uint8_t Type;
}Param;*/

uint8_t _paramCount = 8;
/*const Param Params[] =
{
    // �������
    //{.ParamId, .Name,     .Type,          .Value}, 
    {"������.",     PT_TEMP,        }, 
    {"���������",   PT_HYM,         }, 
    // ������
    {"����",        PT_LIGHT,       }, 
    {"�����",       PT_DOOR_OPEN,   }, 
    // �������
    {"����",        PT_LIGHT,       }, 
    // �����
    {"������.",     PT_TEMP,        }, 
    {"���������",   PT_HYM,         }, 
    {"��������",    PT_PRESS,       }, 
};*/



const uint16_t ParamAddresses_0[] = {0, 1};
const uint16_t ParamAddresses_1[] = {2, 3};
const uint16_t ParamAddresses_2[] = {4};
const uint16_t ParamAddresses_3[] = {5, 6, 7};

const RoomParams roomParams[] =
{
    // �������
    //{.Count, .ParamAddresses},
    {2, ParamAddresses_0},
    // ������
    {2, ParamAddresses_1},
    // �������
    {1, ParamAddresses_2}, 
    // �����
    {3, ParamAddresses_3}
};

uint8_t _currentRoom;
uint8_t _currentParam;

typedef enum 
{
    VS_ROOT,
    VS_SELECT_ROOM,
    VS_SHOW_PARAMS
}ViewStates;

ViewStates _currentState;

void RoomDisplayRedraw();

bool inited = false;


void RoomsStart()
{
    if(!inited)
    {
        InitParameters();//!!!!
        inited = true;
    }
    
    _currentState = VS_ROOT;
    //DisplayClear();
    //DisplayPrintChar(CH_LEFT_RIGHT);
    //DisplayPrintStr("����� �������");
    
    DisplayNoBlink();
    DisplayNoCursor();
    
    _currentRoom = 0;
    RoomDisplayRedraw();
    //DisplayHome();
}


void RoomDisplayRedraw()
{
    
    DisplayClear();
    
    switch(_currentState)
    {
        case VS_ROOT:
        case VS_SELECT_ROOM:
        {
            if(_currentState == VS_ROOT)
            DisplayPrintChar(CH_LEFT_RIGHT);
            else
                DisplayPrintChar(' ');
            DisplayPrintStr("����� �������");
            DisplaySetCursorPos(0, 1);
            if(_currentState == VS_SELECT_ROOM)
                DisplayPrintChar(CH_LEFT_RIGHT);
            if(_currentRoom >= roomsCount)
            {
                DisplayPrintStr("������");
                return;
            }
            DisplayPrintStr(roomNames[_currentRoom]);
        }
        break;
        case VS_SHOW_PARAMS:
        {
            // ������ ������ - �������� �������
            DisplayPrintStr(roomNames[_currentRoom]);
            // ������ ������ �������� ��������� � ��������
            DisplaySetCursorPos(0, 1);
            DisplayPrintChar(CH_LEFT_RIGHT);
            PrintParameter(roomParams[_currentRoom].ParamAddresses[_currentParam], -1, -1, PPN_FULL);
        }
        break;
    }
    
    
    
}

void RoomsOnButton(uint8_t button)
{
    if (ButtonStates[button] != BUTTON_PRESSED)
        return;
    switch (button)
    {
        case BTN_LEFT:
        {
            switch(_currentState)
            {
                case VS_SELECT_ROOM:// ����� � ������
                {
                    if(_currentRoom == 0)
                        _currentRoom = roomsCount - 1;
                    else
                        _currentRoom--;
                    _currentParam = 0;
                    RoomDisplayRedraw();
                }
                break;
                case VS_SHOW_PARAMS:
                {
                    if(_currentParam == 0)
                        _currentParam = roomParams[_currentRoom].Count - 1;
                    else
                        _currentParam--;
                    RoomDisplayRedraw();
                }
                break;        
            }
        }
        break;
        case BTN_RIGHT:
        {
            switch(_currentState)
            {
                case VS_SELECT_ROOM:// ����� � ������
                {
                    if(_currentRoom == roomsCount - 1)
                        _currentRoom = 0;
                    else
                        _currentRoom++;
                    _currentParam = 0;
                    RoomDisplayRedraw();
                }
                break;
                case VS_SHOW_PARAMS:
                {
                    if(_currentParam == roomParams[_currentRoom].Count - 1)
                        _currentParam = 0;
                    else
                        _currentParam++;
                    RoomDisplayRedraw();
                }
                break;        
            }
        }
        break;   
        
        
        case BTN_ENT: 
        {
            switch(_currentState)
            {
                case VS_ROOT:// ���� � ����� ������ ������
                {
                    _currentState = VS_SELECT_ROOM;
                }
                break;
                case VS_SELECT_ROOM:
                {
                    _currentState = VS_SHOW_PARAMS;
                }
                break;
            }
            RoomDisplayRedraw();
        }
            break;
        case BTN_CLR:
        {
            switch(_currentState)
            {
                case VS_SELECT_ROOM:// ����� � ������
                {
                    _currentState = VS_ROOT;
                }
                break;
                case VS_SHOW_PARAMS:
                {
                    _currentState = VS_SELECT_ROOM;
                }
                break;
            }
            RoomDisplayRedraw();
        }
            break;
    }
}

bool RoomsIsRoot()
{
    return _currentState == VS_ROOT;
}