/*
 Print.cpp - Base class that provides print() and println()
 Copyright (c) 2008 David A. Mellis.  All right reserved.
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 
 Modified 23 November 2006 by David A. Mellis
 Modified 03 August 2015 by Chuck Todd
 */

//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <math.h>


#include "xlcd.h"

uint8_t DisplayPrintNumber(unsigned long n, uint16_t base);
char RecodeSymbol(char c);
// Public Methods //////////////////////////////////////////////////////////////

/* default implementation: may be overridden */
//write(const uint8_t *buffer, uint8_t size)
//{
//    uint8_t n = 0;
//    while (size--) 
//    {
//        WriteDataXLCD(*buffer++);
//        n++;
////        if (WriteDataXLCD(*buffer++))
////            n++;
////        else break;
//    }
//    return n;
//}

//size_t DisplayPrint(const __FlashStringHelper *ifsh)
//{
//  PGM_P p = reinterpret_cast<PGM_P>(ifsh);
//  size_t n = 0;
//  while (1) {
//    unsigned char c = pgm_read_byte(p++);
//    if (c == 0) break;
//    if (write(c)) n++;
//    else break;
//  }
//  return n;
//}

//size_t Print::print(const String &s)
//{
//  return write(s.c_str(), s.length());
//}

uint8_t DisplayPrintStr(const char *str)
{
    while(BusyXLCD());
    return putsXLCD(str);
}

uint8_t DisplayPrintChar(char c)
{
    while(BusyXLCD());
    putcXLCD(RecodeSymbol(c));
    return 0;
}

uint8_t DisplayPrintSymbol(uint8_t c)
{
    
    if(c >= 0x80 && c <= 0x90)
    {
        InitSymbol(c);
        c = CH_CUSTOM_SYMBOL;
    }
    while(BusyXLCD());
    putcXLCD(c);
    return 0;
}


//uint8_t DisplayPrint(unsigned char b, int base)
//{
//  return DisplayPrint((unsigned long) b, base);
//}
//
//uint8_t DisplayPrint(int n, int base)
//{
//  return DisplayPrint((long) n, base);
//}
//
//uint8_t DisplayPrint(unsigned int n, int base)
//{
//  return DisplayPrint((unsigned long) n, base);
//}

uint8_t DisplayPrintInt(long n, uint16_t base)
{
    if (base == 0) 
    {
        putcXLCD((uint32_t)n);
        return 0;
    } 
    else if (base == 10) 
    {
      if (n < 0) 
      {
        uint8_t t = DisplayPrintChar('-');
        n = -n;
        return DisplayPrintNumber((uint32_t)n, 10u) + t;
      }
      return DisplayPrintNumber((uint32_t)n, 10u);
    } else {
      return DisplayPrintNumber((uint32_t)n, base);
    }
}

uint8_t DisplayPrintUInt(unsigned long n, uint16_t options)
{
    if (options == 0) 
    {
        putcXLCD(n);
        return 0;
    }
    else 
        return DisplayPrintNumber(n, options);
}

//uint8_t DisplayPrintDouble(double n, int digits)
//{
//  return DisplayPrintFloat(n, digits);
//}

//size_t Print::println(const __FlashStringHelper *ifsh)
//{
//  size_t n = print(ifsh);
//  n += println();
//  return n;
//}

//size_t Print::print(const Printable& x)
//{
//  return x.printTo(*this);
//}

//size_t Print::println(void)
//{
//  return write("\r\n");
//}

//size_t Print::println(const String &s)
//{
//  size_t n = print(s);
//  n += println();
//  return n;
//}
//
//size_t Print::println(const char c[])
//{
//  size_t n = print(c);
//  n += println();
//  return n;
//}
//
//size_t Print::println(char c)
//{
//  size_t n = print(c);
//  n += println();
//  return n;
//}
//
//size_t Print::println(unsigned char b, int base)
//{
//  size_t n = print(b, base);
//  n += println();
//  return n;
//}
//
//size_t Print::println(int num, int base)
//{
//  size_t n = print(num, base);
//  n += println();
//  return n;
//}
//
//size_t Print::println(unsigned int num, int base)
//{
//  size_t n = print(num, base);
//  n += println();
//  return n;
//}
//
//size_t Print::println(long num, int base)
//{
//  size_t n = print(num, base);
//  n += println();
//  return n;
//}
//
//size_t Print::println(unsigned long num, int base)
//{
//  size_t n = print(num, base);
//  n += println();
//  return n;
//}
//
//size_t Print::println(double num, int digits)
//{
//  size_t n = print(num, digits);
//  n += println();
//  return n;
//}
//
//size_t Print::println(const Printable& x)
//{
//  size_t n = print(x);
//  n += println();
//  return n;
//}

// Private Methods /////////////////////////////////////////////////////////////


uint8_t DisplaySprint(unsigned long n, uint16_t options, char *buf, uint8_t bufsize)
{
    uint8_t base = options & MASK_BASE;
    
//    uint8_t bufSize;
//    if(options & SHOW_USE_FIELD_SIZE)
//        bufSize = (options & MASK_FIELD_SIZE) + 1 + 1;
//    else
    
    
//    char buf[SCREEN_WIDTH + 1]; //8 * sizeof(long) + 1 Assumes 8-bit chars plus zero byte.
    char *str = &buf[bufsize - 1];

    *str = '\0';

    // prevent crash if called with base == 1
    if (base < 2) base = 10;

    uint8_t alreadyPrinted = 0;
    do 
    {
        char c = n % base;
        n /= base;

        *--str = c < 10 ? c + '0' : c + 'A' - 10;
        alreadyPrinted++;
    } while(n && (str - buf > 0));

    
    
    if(options & SHOW_USE_FIELD_SIZE)
    {
        uint8_t fieldSize = ((options & MASK_FIELD_SIZE) >> 8) + 1;
        char symToFill = (options & SHOW_STARTING_ZEROES) ? '0' : ' ';
        for(uint8_t i = alreadyPrinted; i < fieldSize && (str - buf > 0); i++)
            *--str = symToFill;
        if(alreadyPrinted < fieldSize)
            alreadyPrinted = fieldSize;
    }
    return alreadyPrinted;
}

uint8_t DisplayPrintNumber(unsigned long n, uint16_t options)
{
//    uint8_t base = options & MASK_BASE;
//    
////    uint8_t bufSize;
////    if(options & SHOW_USE_FIELD_SIZE)
////        bufSize = (options & MASK_FIELD_SIZE) + 1 + 1;
////    else
//    
//    
//    char buf[SCREEN_WIDTH + 1]; //8 * sizeof(long) + 1 Assumes 8-bit chars plus zero byte.
//    char *str = &buf[sizeof(buf) - 1];
//
//    *str = '\0';
//
//    // prevent crash if called with base == 1
//    if (base < 2) base = 10;
//
//    uint8_t alreadyPrinted = 0;
//    do 
//    {
//        char c = n % base;
//        n /= base;
//
//        *--str = c < 10 ? c + '0' : c + 'A' - 10;
//        alreadyPrinted++;
//    } while(n && (str - buf > 0));
//
//    
//    
//    if(options & SHOW_USE_FIELD_SIZE)
//    {
//        uint8_t fieldSize = ((options & MASK_FIELD_SIZE) >> 8) + 1;
//        char symToFill = (options & SHOW_STARTING_ZEROES) ? '0' : ' ';
//        for(uint8_t i = alreadyPrinted; i < fieldSize && (str - buf > 0); i++)
//            *--str = symToFill;
//        if(alreadyPrinted < fieldSize)
//            alreadyPrinted = fieldSize;
//    }
    
    char buf[SCREEN_WIDTH + 1]; //8 * sizeof(long) + 1 Assumes 8-bit chars plus zero byte.
    uint8_t printedCharCount = DisplaySprint(n, options, buf, sizeof(buf));
    
    putsXLCD((const char *)(&(buf[sizeof(buf) - printedCharCount - 1]))); //str
    return printedCharCount;
}


uint8_t DisplayPrintFloat(double number, uint16_t options) 
{ 
    uint8_t n = 0;
    uint8_t digits = options & MASK_BASE;
    
  //  if (isnan(number)) return print("nan");
  //  if (isinf(number)) return print("inf");
    if (number > 4294967040.0) 
        return DisplayPrintStr ("ovf");  // constant determined empirically
    if (number < -4294967040.0) 
        return DisplayPrintStr ("ovf");  // constant determined empirically

    // Handle negative numbers
    bool negate = false;
    if (number < 0.0)
    {
       //n += DisplayPrintChar('-');
       number = -number;
       negate = true;
    }

    char buf[SCREEN_WIDTH + 1]; // plus zero byte.

    
    
    // Round correctly so that print(1.999, 2) prints as "2.00"
    double rounding = 0.5;
    for (uint8_t i = 0; i < digits; ++i)
      rounding /= 10.0;

    number += rounding;

    // Extract the integer part of the number and print it
    unsigned long int_part = (unsigned long)number;
    double remainder = number - (double)int_part;
    
    // Печатаем начальные пробелы или нули
//    for(uint8_t i = 0; i <)
//    {
//        DisplayPrintChar((options & SHOW_STARTING_ZEROES) ? '0' : ' ');
//    }
        
    n = DisplaySprint(int_part, DEC, buf, sizeof(buf));
    if(negate)
    {
        buf[sizeof(buf) - n - 2] = '-';
        n++;
    }
    //n += DisplayPrintUInt(int_part, DEC);

    uint8_t bufPos = sizeof(buf) - 1;
    // Print the decimal point, but only if there are digits beyond
    if (digits > 0) 
    {
        // Освобождаем место в конце буфера для десятичной части
        uint8_t offset = digits + 1u;
        if(n + offset > (uint8_t)sizeof(buf) - 1u)
            offset = sizeof(buf) - n;
        // n не может быть больше 10 символов, так что проверять не нужно что будет -
        for(uint8_t i = sizeof(buf) - n - 1; i < sizeof(buf) - 1; i++)
        {
            buf[i - offset] = buf[i];
        }
        bufPos -= offset;
        buf[bufPos] = '.';
        bufPos++;
        n++;
        
        //n += DisplayPrintChar('.'); 
    }

    // Extract digits from the remainder one at a time
    while (digits > 0)
    {
        remainder *= 10.0;
        int toPrint = (int)(remainder);
        buf[bufPos] = '0' + (int)(remainder);
        n++;
        bufPos++;
        //n += DisplayPrintInt(toPrint, DEC);
        remainder -= toPrint; 
        digits--;
    } 
    putsXLCD(&(buf[sizeof(buf) - n - 1])); //str
    return n;
}
