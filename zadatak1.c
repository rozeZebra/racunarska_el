#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h> 
#include <lcd.h>

const int RS=3;
const int EN=14;
const int D0=4;
const int D1=12;
const int D2=13;
const int D3=6;

const char PCF8591 = 0x48;
int fd, adcVal;



int main()
{
	int lcd_h;
	if(wiringPiSetup()==1) exit (1);
	
	fd=wiringPiI2CSetup(PCF8591);
	lcd_h=lcdInit(2,16,4,RS,EN,D0,D1,D2,D3,D0,D1,D2,D3);
	
	while(1){
		
		wiringPiI2CReadReg8(fd, PCF8591 + 3);
		adcVal=wiringPiI2CReadReg8(fd, PCF8591 + 3);
		//printf("adc vrednost %d\n", adcVal*(3.3/256));
		
		
		
	wiringPiI2CWriteReg8(fd, PCF8591 + 4, adcVal);
		
		wiringPiI2CReadReg8(fd, PCF8591 + 2);
		adcVal=wiringPiI2CReadReg8(fd, PCF8591 + 2);
		printf("dac vrednost %f\n", adcVal*(3.3/256));
		lcdPosition(lcd_h,0,0);
	lcdPrintf(lcd_h, "%f", adcVal*(3.3/256));

    delay(1000);
	lcdClear(lcd_h);
		
		}
		
		return 0;
	
	}

