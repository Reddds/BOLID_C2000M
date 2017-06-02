#include "i2c.h"


/********************************************************************
 *     Function Name:    EESequentialRead                            *
 *     Return Value:     error condition status                      *
 *     Parameters:       EE memory control, address, pointer and     *
 *                       length bytes.                               *
 *     Description:      Reads data string from I2C EE memory        *
 *                       device. This routine can be used for any I2C*
 *                       EE memory device, which only uses 1 byte of *
 *                       address data as in the 24LC01B/02B/04B/08B. *
 *                                                                   *  
 ********************************************************************/
#if defined (I2C_V1) 

int8_t EESequentialRead(uint8_t control, uint32_t address, uint8_t *rdptr, uint32_t length)
{
    control |= (address >> 16) << 1; // Если адрес больше размера первого чипа, то переходим ко второму
    IdleI2C(); // ensure module is idle
    StartI2C(); // initiate START condition
    while (SSPCON2bits.SEN); // wait until start condition is over 
    if (PIR2bits.BCLIF) // test for bus collision
    {
        return ( -11); // return with Bus Collision error 
    }
    else
    {
        int8_t r1 = WriteI2C(control);
        if (r1) // write 1 byte 
        {
            StopI2C();
            return ( -40 + r1); // set error for write collision
        }

        //IdleI2C();                    // ensure module is idle
        if (!SSPCON2bits.ACKSTAT) // test for ACK condition, if received
        {
            if (WriteI2C_W(address & 0xFFFF)) // WRITE word address to EEPROM
            {
                StopI2C();
                return ( -32); // return with write collision error
            }

            //IdleI2C();                  // ensure module is idle
            if (!SSPCON2bits.ACKSTAT) // test for ACK condition received
            {
                RestartI2C(); // generate I2C bus restart condition
                while (SSPCON2bits.RSEN); // wait until re-start condition is over 
                if (WriteI2C(control + 1u))// WRITE 1 byte - R/W bit should be 1 for read
                {
                    StopI2C();
                    return ( -33); // set error for write collision
                }

                //IdleI2C();                // ensure module is idle
                if (!SSPCON2bits.ACKSTAT)// test for ACK condition received
                {
                    if (getsI2C(rdptr, length))// read in multiple bytes
                    {
                        return ( -12); // return with Bus Collision error
                    }

                    NotAckI2C(); // send not ACK condition
                    while (SSPCON2bits.ACKEN); // wait until ACK sequence is over 
                    StopI2C(); // send STOP condition
                    while (SSPCON2bits.PEN); // wait until stop condition is over 
                    if (PIR2bits.BCLIF) // test for bus collision
                    {
                        return ( -13); // return with Bus Collision error 
                    }
                }
                else
                {
                    StopI2C();
                    return ( -21); // return with Not Ack error
                }
            }
            else
            {
                StopI2C();
                return ( -22); // return with Not Ack error
            }
        }
        else
        {
            StopI2C();
            return ( -23); // return with Not Ack error
        }
    }
    return ( 0); // return with no error
}

#endif
