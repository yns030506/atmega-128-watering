#include <avr/io.h>
#include <avr/iom128.h>
#include <util/delay.h>

volatile unsigned char fnd_digit[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66,
    0x6D, 0x7D, 0x07, 0x7F, 0x6F
};


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
