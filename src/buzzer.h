#include <avr/io.h>
#include <avr/iom128.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void custom_delay_us(int us);
void buzzer(float hz, int ms);
void buzzer_init();
void play(int tone_idx);
    