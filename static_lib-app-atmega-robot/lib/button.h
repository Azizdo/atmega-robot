#define F_CPU 8000000UL
#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>
#include <util/delay.h>

class Button
{
public:
    enum class State {
        NONE,
        PRESS,
        HOLD,
        RELEASE,
    };

    Button(volatile uint8_t* inputPinsAddress, uint8_t pinNumber);
    ~Button();

    State getState();

private:

    void updateState();
    bool isPressed();
    volatile uint8_t* _dataDirectionRegister;
    volatile uint8_t* _inputPinsAddress;
    uint8_t _pinNumber;
    State _state;
};

#endif