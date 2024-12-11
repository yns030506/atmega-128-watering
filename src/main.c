#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

// LCD 통신 헤더
#include "uart0.h"
#include "I2C.h"
#include "i2c_lcd.h"

// 토양 습도 센서 헤더
#include "soil_sensor.h"


FILE OUTPUT = FDEV_SETUP_STREAM(UART0_Transmit, NULL, _FDEV_SETUP_WRITE);

int main(void)
{	
	// LCD
	LCDInit();
	UART0_Init();
	stdout =&OUTPUT;
	LCDWriteStringXY(0,0,"hello world");
	int c=0;
	char stbuf[30];

	// 토양습도센서
	uint16_t moisture;
    ADC_Init();
    UART_Init();
	
	
	
    while (1) 
    {
		moisture = ADC_Read(7);
		sprintf(stbuf,"moisture :%d",moisture);
		LCDWriteStringXY(1,0,stbuf);
		_delay_ms(50);
    }
}
