#include <reg52.h>
#include "SPI.h"
unsigned char code num[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
unsigned char DisplayData[5];

sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;
void delay(unsigned int time);
void DigDisplay();
void DataProcess();
void ChangeTemp();

unsigned int temper;
void main()
{
	while(1)
	{
		temper=ReadTemper();
		ChangeTemp();
		DataProcess();
		DigDisplay();
	}
	return;
}
void DataProcess()
{
    DisplayData[1] = num[temper % 10];
    DisplayData[2] = num[temper % 100 / 10];
    DisplayData[3] = num[temper % 1000 / 100] | 0x80;
    DisplayData[4] = num[temper % 10000 / 1000];
	
}
void DigDisplay()
{
    unsigned char i, j = 200;
    while (j--)     //delay here
        for (i = 0; i < 4; i++)
        {
            switch (i)
            {
            case 0:
                LSA = 0;
                LSB = 0;
                LSC = 0;
                break;
            case 1:
                LSA = 1;
                LSB = 0;
                LSC = 0;
                break;
            case 2:
                LSA = 0;
                LSB = 1;
                LSC = 0;
                break;
            case 3:
                LSA = 1;
                LSB = 1;
                LSC = 0;
                break;
            }
            P0 = DisplayData[i + 1];
            delay(100);
            P0 = 0x00;
        }
}
void ChangeTemp()
{
		float tp;
    if (temper < 0)
    {
        DisplayData[0] = 0x40;
        temper = temper - 1;
        temper = ~temper;
        tp = temper / 32;
        temper = tp * 0.25 * 100 + 0.5;
    }
    else
    {
        DisplayData[0] = 0x00;
        tp = temper / 32;
        temper = tp * 0.25 * 100 + 0.5;
    }
}
void delay(unsigned int time)
{
    while (time--)
        ;
}F