#ifndef TIMER_H
#define F_CPU 8000000UL
#define TIMER_H

#include <avr/interrupt.h>
#include <avr/io.h> 

enum class TimerOptions{
    TIMER1,
    TIMER2
};

enum class Prescaler{
    PRESCALER1024,
    PRESCALER256,
    PRESCALER8
};

class Timer {
public : 

    TimerOptions timerOptions {TimerOptions::TIMER1};

    Prescaler prescaler {Prescaler::PRESCALER1024};

    Timer(TimerOptions timerOptions, Prescaler prescaler, uint8_t ratioTime);

    void initPrescaler();
    void startTime();


private : 

    TimerOptions _timer;
    Prescaler _prescaler;
    uint8_t _ratioTime;

};

#endif