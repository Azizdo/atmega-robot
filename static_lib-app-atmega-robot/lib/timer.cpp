#include "timer.h"

Timer::Timer(TimerOptions timerOptions, Prescaler prescaler, uint8_t ratioTime){
    _timer = timerOptions;
    _prescaler = prescaler;
    _ratioTime = ratioTime;
    //initPrescaler();
}

void Timer::initPrescaler(){
    switch (prescaler)
    {
    case Prescaler::PRESCALER1024:
        if(timerOptions == TimerOptions::TIMER1){
            TCCR1B = (1 << WGM12)|(1 << CS12) | (1 << CS10);
        }
        else if(timerOptions == TimerOptions::TIMER2){
            TCCR2A = (1 << WGM21);
            TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
        }        
        break;

    case Prescaler::PRESCALER256:
        if(timerOptions == TimerOptions::TIMER1){
            TCCR1B = (1 << WGM12)|(1 << CS12);
        }
        else if(timerOptions == TimerOptions::TIMER2){
            TCCR2A = (1 << WGM21);
            TCCR2B = (1 << CS22) | (1 << CS21);
        }        
        break;

    case Prescaler::PRESCALER8:
        if(timerOptions == TimerOptions::TIMER1){
            TCCR1B = (1 << WGM12)|(1 << CS11);
        }
        else if(timerOptions == TimerOptions::TIMER2){
            TCCR2A = (1 << WGM21);
            TCCR2B = (1 << CS21);
        }        
        break;

    default:
        break;
    }
}

void Timer::startTime(){

    if (timerOptions == TimerOptions::TIMER1){
        TCCR1C = 0;
        TCNT1 = 0;
        TIMSK1 = (1 << OCIE1A);
        OCR1A = _ratioTime;
    }
    else if (timerOptions == TimerOptions::TIMER2){
        TCNT2 = 0;
        TIMSK2 = (1 << OCIE2A);
        OCR2A = _ratioTime;
    }

}


