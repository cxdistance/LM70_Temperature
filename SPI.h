#ifndef _SPI_H_
#define _SPI_H_

#include <reg52.h>

sbit CS = P2 ^ 7;
sbit SCL = P2 ^ 1;
sbit SDA = P2 ^ 0;

void SPI_Write();
unsigned char SPI_Read();
void Delay10us();
unsigned int ReadTemper();

#endif