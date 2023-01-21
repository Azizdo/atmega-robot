#include "led.h"

Led::Led(volatile uint8_t* port, uint8_t pin1, uint8_t pin2)
{
    _pin1 = pin1;
    _pin2 = pin2;
    _port = port;
}

void Led::ledGreen()
{
    *_port = ( 1 << _pin1);
}

void Led::ledRed()
{
    *_port = ( 1 << _pin2);
}

void Led::ledOff()
{
    *_port = 0 << _pin1;
    *_port = 0 << _pin2;
}

void Led::ledAmber()
{
    uint8_t delayRed = 13;
    uint8_t delayGreen = 19;
    while(true)
    {
        *_port = ( 1 << _pin2);
        _delay_ms(delayRed);
        *_port = ( 1 << _pin1);
        _delay_ms(delayGreen);
    }
}
