#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

// LCD 헤더 
#include "i2c_master.h"
#include "liquid_crystal_i2c.h"

// 토양 습도 센서 헤더
#include "soil_sensor.h"

// buzzer 헤더
#include "buzzer.h"

// 스위치 헤더 
#include "switch_timer.h"

// 설정값
#define THRESHOLD 350  // 수분 임계값
#define ALARM_DURATION 10 // 알람 울리는 시간 (초)
#define ALARM_DELAY 600 // 알람 지연 시간 (초)

// 전역 변수
volatile int alert = 0;          // 현재 알람 상태 (0: 비활성, 1: 활성)
volatile int alarm_timer = 0;    // 알람 대기 타이머
volatile int delay_timer = 0;    // 알람 지연 타이머
uint16_t moisture = 0;           // 현재 수분값
char display_buffer[16];         // LCD 문자열 버퍼

// LCD 전역 변수
LiquidCrystalDevice_t lcd;

void update_lcd(void) {
    lq_clear(&lcd);
    sprintf(display_buffer, "Moisture: %d", moisture);
    lq_print(&lcd, display_buffer);

    if (delay_timer > 0) {
        lq_setCursor(&lcd, 1, 0);
        sprintf(display_buffer, "Delay: %d sec", delay_timer / 10);
        lq_print(&lcd, display_buffer);
    }
    else{
        lq_setCursor(&lcd, 1, 0);
        lq_print(&lcd, ":)");
    }
}

// 알람 중지 (Switch1)
ISR(INT4_vect) {
    alert = 0;
    alarm_timer = 0;
}

// 알람 지연 (Switch2)
ISR(INT5_vect) {
    if (delay_timer <= 0) {
        delay_timer = ALARM_DELAY;
    }
    else{
        delay_timer += ALARM_DELAY;
    }
}

// 타이머 인터럽트 (1초 간격)
ISR(TIMER1_COMPA_vect) {
    if (alert) {
        if (--alarm_timer <= 0) {
            alert = 0; // 알람 종료
        }
    }
    if (delay_timer > 0) {
        --delay_timer; // 알람 지연 시간 감소
    }
}

int main(void)
{
	//LCD init
    i2c_master_init(100000);
    lcd = lq_init(0x27, 20, 4, LCD_5x8DOTS);
    lq_turnOnBacklight(&lcd);
    

	// 토양 습도 센서 init
    ADC_Init();
    UART_Init();

    // Buzzer 초기화
    buzzer_init();

    // Switch 및 Timer 초기화
    switch_init();
    timer1_init();
    sei();

    while (1)
    {
        moisture = ADC_Read(7);
        update_lcd();
        if (moisture <= THRESHOLD && !alert && delay_timer <= 0) {
            alert = 1;
            alarm_timer = ALARM_DURATION;

            // 알람 시작
            while (alarm_timer > 0 && alert) {
                play(0); // Buzzer 울리기
                _delay_ms(1000);
            }
        }

        _delay_ms(1000);
    }

    return 0;
}