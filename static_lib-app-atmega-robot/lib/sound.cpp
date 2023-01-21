#include"sound.h"

int time = 0;

/*ISR(TIMER0_COMPA_vect){
    time++;
    if(time>200){
        PORTB ^= (1<<PORTB0); // xor, toggle
        time = 0;
    }
}*/

Sound::Sound(){ // initialiser les registres
    
}

void Sound::initPwm(int note){
    //Timer::startTime();
    //Pwm::initTimer0();
    //Pwm::ajustDutyCycle();

    DDRB = 0x01;
    
    OCR0A = noteDutyCycles[note-45];
    TCCR0A |= (1 << WGM01); //ctc
    TCCR0A |= (1 << COM0A0); //ocr0a toggle a chaque comparaison
    TCCR0B |= (1 << CS02) | (1 << CS00); //clk/1024 max prescaler
    TIMSK0 = (1 << OCIE0A);

    //sei();

}

void Sound::playSound(int note){
    // Timer timer(TimerOptions::TIMER1, Prescaler::PRESCALER1024, 200);
    // OCR0A = noteDutyCycles[note-45];
    // timer.startTime();
    initPwm(note);

}

void Sound::stopSound(){
    //sar;
    OCR0A = 0x00;
}

Sound::~Sound(){
    
}
