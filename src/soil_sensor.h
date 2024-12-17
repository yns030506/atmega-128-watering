#include <avr/io.h>
#include <avr/iom128.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

void ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);
void UART_Init(void);
void UART_Transmit(char data) ;
void UART_PrintString(const char *str);
void UART_PrintNumber(uint16_t num);
