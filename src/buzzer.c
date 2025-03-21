#include <avr/io.h>
#include <avr/iom128.h>
#include <avr/interrupt.h>
#include <util/delay.h>


float tone[] = {1046.6, 1174.6, 1318.6, 1397.0, 1568.0, 1760.0, 1975.6, 2093.2};

void custom_delay_us(int us) {
    for(int i = 0; i < us; i++) {
        _delay_us(1);
    }
}

void buzzer(float hz, int ms) {
    int us = (int)(500000 / hz);
    int count = (int)(ms / 2);

    for(int i = 0; i < count; i++) {
        PORTB |= (1 << PB4);
        custom_delay_us(us);
        PORTB &= ~(1 << PB4);
        custom_delay_us(us);
    }
}

void buzzer_init(){
    DDRB |= (1 << PB4);
}

void play(int tone_idx){
    buzzer(tone[tone_idx], 500);
}
    