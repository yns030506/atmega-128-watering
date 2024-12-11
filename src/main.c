#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

// LCD 헤더 
#include "i2c_master.h"
#include "liquid_crystal_i2c.h"

// 토양 습도 센서 헤더
#include "soil_sensor.h"

int main(void)
{
	//LCD init
    i2c_master_init(100000);
    LiquidCrystalDevice_t lcd = lq_init(0x27, 20, 4, LCD_5x8DOTS);
    lq_turnOnBacklight(&lcd);
    

	// 토양습도센서
	uint16_t moisture; // 습도 값
    char moisture_str[16]; // 습도 값을 문자열로 저장하는 버퍼
    ADC_Init();
    UART_Init();

    while (1)
    {
		// ADC로 토양 습도 값 읽기
        moisture = ADC_Read(7);

        // 습도 값을 문자열로 변환
        sprintf(moisture_str, "Moisture: %d", moisture);

        // LCD에 출력
        lq_clear(&lcd); // 기존 텍스트 지우기
		
		lq_print(&lcd, "Hello!");
		lq_setCursor(&lcd, 1, 0);
        lq_print(&lcd, moisture_str);

        _delay_ms(1000); // 1초 대기
    }

    return 0;
}
