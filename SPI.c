#include "SPI.h"
#include <reg52.h>
void DDelay(unsigned int time);
unsigned char SPI_Read()
{

    unsigned char value, i;
    SCL = 0;
    DDelay(100);
    for (i = 0; i < 8; i++)
    {
        value <<= 1;
        SCL = 1;
        Delay10us();
        value |= SDA;
        SCL = 0;
        Delay10us();
    }
    return value;
}
void Delay10us()
{
    unsigned char i = 1;
    while (i)
        i--;
}
unsigned int ReadTemper()
{
    unsigned int temp1 = 0, temp2 = 0;
    CS = 0;
    temp1 = SPI_Read();
    temp2 = SPI_Read();
    CS = 1;
    temp1 <<= 8;
    temp1 |= temp2;
    return temp1;
}
void DDelay(unsigned int time)
{
    while (time--)
        ;
}