#include "i2c.h"

#include "../system.h" // для delay
/********************************************************************
 *     Function Name:    EEPageWrite                                 *
 *     Return Value:     error condition status                      *
 *     Parameters:       EE memory control, address and pointer 1    *
 *                       length длина массива.                       *
 *                              
 *     Description:      Writes data string to I2C EE memory         *
 *                       device.                                     *
 *                                                                   *  
 ********************************************************************/
#if defined (I2C_V1) 

#define PAGE_MASK 0x7F

int8_t EEArrayWrite(uint8_t control, uint32_t address, uint8_t *wrptr, uint32_t length)
{
    uint32_t bytesWrote = 0;
    uint8_t pageCnt = 0;
    while(bytesWrote < length)
    {
        uint8_t bytesToWrite = PAGE_SIZE;
        if(pageCnt == 0) //  Надо чтобы при записи не пересекались границы страниц
        {
            uint8_t addrStart = address & PAGE_MASK;
            if(address != 0)
                bytesToWrite = PAGE_SIZE - addrStart;
            if(bytesToWrite > length)
                bytesToWrite = length;
        }
        else if(length - bytesWrote < PAGE_SIZE)
            bytesToWrite = length - bytesWrote;
        int8_t res = EEPageWrite(control, address + bytesWrote, wrptr + bytesWrote, bytesToWrite);        
        if(res != 0)
            return res - pageCnt * 10;
        bytesWrote += bytesToWrite;
        pageCnt++;
        
        // Паксимальное время записи одной страницы - 5 мс
        __delay_ms(6);
    }
    return 0;
}



int8_t EEPageWrite(uint8_t control, uint32_t address, uint8_t *wrptr, uint8_t length)
{
    control |= (address >> 16) << 1; // Если адрес больше размера первого чипа, то переходим ко второму
    IdleI2C(); // ensure module is idle
    StartI2C(); // initiate START condition
    while (SSPCON2bits.SEN); // wait until start condition is over 
    if (PIR2bits.BCLIF) // test for bus collision
    {
        return ( -1); // return with Bus Collision error 
    }
    else
    {
        if (WriteI2C(control)) // write 1 byte - R/W bit should be 0
        {
            StopI2C();
            return ( -3); // return with write collision error
        }

        //IdleI2C();                    // ensure module is idle
        if (!SSPCON2bits.ACKSTAT) // test for ACK condition, if received 
        {
            if (WriteI2C_W(address & 0xFFFF)) // write address byte to EEPROM
            {
                StopI2C();
                return ( -3); // return with write collision error
            }

            //IdleI2C();                  // ensure module is idle
            if (!SSPCON2bits.ACKSTAT) // test for ACK condition, if received
            {
                if (putBufI2C(wrptr, length))
                {
                    StopI2C();
                    return ( -4); // bus device responded possible error
                }
            }
            else
            {
                StopI2C();
                return ( -2); // return with Not Ack error
            }
        }
        else
        {
            StopI2C();
            return ( -2); // return with Not Ack error
        }
    }

    //IdleI2C();                      // ensure module is idle
    StopI2C(); // send STOP condition
    while (SSPCON2bits.PEN); // wait until stop condition is over 
    if (PIR2bits.BCLIF) // test for Bus collision
    {
        return ( -1); // return with Bus Collision error 
    }
   
    return ( 0); // return with no error
}

#endif
