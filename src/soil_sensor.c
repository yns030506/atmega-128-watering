#include <avr/io.h>
#include <avr/iom128.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

void ADC_Init(void) {
    ADMUX = (1<<REFS0);               // AVCC를 기준 전압으로 설정
    ADCSRA = (1<<ADEN) | (1<<ADPS2); // ADC 활성화, 프리스케일러 16
}

uint16_t ADC_Read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF8) | (channel & 0x07); // 채널 선택
    ADCSRA |= (1<<ADSC);                      // 변환 시작
    while (ADCSRA & (1<<ADSC));               // 변환 완료 대기
    return ADC;                               // 10비트 데이터 반환
}

void UART_Init(void) {
    UBRR0H = 0;                     // UBRR 상위 바이트 (0으로 설정)
    UBRR0L = 51;                    // UBRR 하위 바이트 (9600bps 기준, F_CPU=8MHz)
    UCSR0B = (1 << TXEN0);          // 송신 활성화
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8비트 데이터, 1 스톱 비트
}

void UART_Transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0))); // 송신 버퍼가 비어있을 때까지 대기
    UDR0 = data;                      // 데이터를 전송
}

void UART_PrintString(const char *str) {
    while (*str) {
        UART_Transmit(*str++);        // 문자열의 각 문자를 전송
    }
}

void UART_PrintNumber(uint16_t num) {
    char buffer[10];
    itoa(num, buffer, 10); // 숫자를 문자열로 변환 (10진수)
    UART_PrintString(buffer);
    UART_Transmit('\n');   // 줄 바꿈 추가
}
