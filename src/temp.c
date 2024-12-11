// // #define F_CPU 16000000UL
// // #include <avr/io.h>
// // #include <avr/iom128.h>
// // #include <avr/interrupt.h>
// // #include <util/delay.h>

// // #include "buzzer.h"
// // #include "fnd.h"

// // #define ALARM_ON 1
// // #define ALARM_OFF 0
// // #define DELAY 60000

// // volatile int alert = ALARM_OFF;
// // volatile int delay = 0;
// // int threshold = 300; 
// // int humidity = 200;

// // ISR(TIMER1_COMPA_vect) {
// //     if (alert == ALARM_ON) {
// //         delay--;
// //     }
// // }

// // ISR(INT4_vect) {
// //     alert = ALARM_OFF;
// // }

// // ISR(INT5_vect) {
// //     if(delay>=0)
// //     delay+=DELAY;
// //     //fnd조작 추가 
// // }

// // void timer1_init() {
// //     // CTC mode, prescaler 64
// //     TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
// //     OCR1A = 25000;
// //     TIMSK |= (1 << OCIE1A);
// // }

// // void switch_init() {
// //     EIMSK |= (1 << INT4) | (1 << INT5);
// //     EICRB |= (1 << ISC41) | (1 << ISC51);
// // }


// // int main(void) {

// //     // 인터럽트 설정
// //     EIMSK = 0x10;   // INT4 활성화
// //     EICRB = 0x02;   // Falling Edge에서 인터럽트 발생

// //     // buzzer, 가져온거
// //     // DDRB |= (1 << PB4);

// //     sei();
// //     while(1){
// //         // if (humidity < threshold){
// //         //     alert = ALARM_ON;
// //         //     while(alert && delay ==0){
// //         //         for(int i = 0; i < 8; i++) {
// //         //             buzzer(tone[i], 500);
// //         //             _delay_ms(500);
// //         //         }
// //         //     }
// //         // }
// //         fnd_print(delay, 1);
// //         PORTA = delay / 10000;
// //         delay+=DELAY;
// //     }
    



// // }





// #define F_CPU 16000000UL
// #include <avr/io.h>
// #include <avr/iom128.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>
// #include "fnd.h"
// #include "switch_timer.h"
// #include "buzzer.h"



// #define STOP 0
// #define PAUSE 1
// #define RUN 2

// volatile int count = 60;
// volatile int state = RUN;
// volatile int playing = 0;

// // ISR(TIMER1_COMPA_vect) {
// //     if (state == RUN) {
// //         count--;
// //     }
// //     if(count <=0){
// //         state = PAUSE;
// //     }
// // }

// // ISR(INT4_vect) {
// //     // if (state == STOP) {
// //     //     state = RUN;
// //     // } else if (state == RUN) {
// //     //     state = PAUSE;
// //     // } else if (state == PAUSE) {
// //     //     state = RUN;
// //     // }
// //     state=STOP;
// // }

// // ISR(INT5_vect) {
// //     count += 60;
// // }

// ISR(TIMER1_COMPA_vect) {
//     if (state == RUN) {
//         count--;
//         if (count <= 0) {
//             state = PAUSE;
//         }
//     }
// }

// ISR(INT4_vect) {
//     if(state == RUN){state = PAUSE;}
//     else {state =RUN;}
//     playing = 1;
// }

// ISR(INT5_vect) {
//     count += 60;   // 1분 추가
//     // if (state == PAUSE) {
//     //     state = RUN; // 재시작 가능
//     // }
//     playing = 0;
// }

// int main() {
//     timer1_init();
//     switch_init();
//     fnd_init();
//     buzzer_init();
//     sei();

//     DDRA = 0xFF;
    
//     // while (1) {
//     //     fnd_print(count, 1);
//     //     PORTA = count / 10000;
//     //     if((count <= 0)&& (state == RUN) ){
//     //         state = PAUSE; // play 호출 후 상태 변경
//     //         play();
//     //     }
//     // }
//     int played = 0; // play 호출 여부를 추적하는 플래그

//     while (1) {
//         fnd_print(count, 1);

//         if (count <= 0 && state == PAUSE && !played) {
//             play(playing);
//             played = 1;  // play 함수 호출 후 플래그 설정
//         }

//         if (state == RUN && count > 0) {
//             played = 0;  // RUN 상태에서 다시 초기화 가능
//         }
//     }
// }

