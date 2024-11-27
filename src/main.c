#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/iom128.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define STOP 0
#define PAUSE 1
#define RUN 2

volatile unsigned char fnd_digit[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66,
    0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

volatile int count = 0;
volatile int state = STOP;

ISR(TIMER1_COMPA_vect) {
    if (state == RUN) {
        count++;
    }
}

ISR(INT4_vect) {
    if (state == STOP) {
        state = RUN;
    } else if (state == RUN) {
        state = PAUSE;
    } else if (state == PAUSE) {
        state = RUN;
    }
}

ISR(INT5_vect) {
    count = 0;
    state = STOP;
}

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

void fnd_init() {
    DDRC = 0xFF;
    DDRG = 0x0F;
}

void fnd_print(int value, int dot) {
    unsigned char fnd_value[4] = {
        fnd_digit[value % 10],
        fnd_digit[(value / 10) % 10],
        fnd_digit[(value / 100) % 10],
        fnd_digit[(value / 1000) % 10]
    };

    for (int i = 0; i < 4; i++) {
        PORTC = fnd_value[i] | (i == dot ? 0x80 : 0x00);
        PORTG = 0x01 << i;
        _delay_ms(1);
    }
}

int main() {
    timer1_init();
    switch_init();
    fnd_init();
    sei();

    DDRA = 0xFF;

    while (1) {
        fnd_print(count, 1);
        PORTA = count / 10000;
    }
}