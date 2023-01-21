#define F_CPU 8000000UL
#ifndef LED_H
#define LED_H

#include <avr/io.h>
#include <util/delay.h>


class Led
{
public:
    Led( volatile uint8_t* port, uint8_t pin1,uint8_t pin2);
    void ledGreen();
    void ledRed();
    void ledOff();
    void ledAmber();


private:
    volatile uint8_t* _port;
    uint8_t _pin1;
    uint8_t _pin2;
};

#endif