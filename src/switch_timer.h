#include <avr/io.h>
#include <avr/iom128.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void timer1_init() {
    // CTC mode, prescaler 64
    TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
    OCR1A = 25000;
    TIMSK |= (1 << OCIE1A);
}

void switch_init() {
    EIMSK |= (1 << INT4) | (1 << INT5);
    EICRB |= (1 << ISC41) | (1 << ISC51);
}
