#include "button.h"

Button::Button(volatile uint8_t* inputPinsAddress, uint8_t pinNumber) : _pinNumber(pinNumber), _inputPinsAddress(inputPinsAddress){

    if (inputPinsAddress == &PIND) {
        _dataDirectionRegister = &DDRD;
    } else if (inputPinsAddress == &PINA) {
        _dataDirectionRegister = &DDRA;
    }


    *_dataDirectionRegister &= ~(1 << _pinNumber);
}

Button::~Button()
{
    *_dataDirectionRegister &= ~(1 << _pinNumber);
}

Button::State Button::getState() {
    updateState();
    return _state;
}

void Button::updateState() {
    switch (_state)
    {
    case State::NONE:
        if (isPressed()) {
            _state = State::PRESS;
        }
        break;
    case State::PRESS:
        if (isPressed()) {
            _state = State::HOLD;
        } else {
            _state = State::RELEASE;
        }
        break;
    case State::HOLD:
        if (!isPressed()) {
            _state = State::RELEASE;
        }
        break;
    case State::RELEASE:
        if (isPressed()) {
            _state = State::PRESS;
        } else {
            _state = State::NONE;
        }
        break;
    }
}

bool Button::isPressed() {
    bool buttonPressed = *_inputPinsAddress & (1 << _pinNumber);
    if (buttonPressed) {
        _delay_ms(10); // Debounce
        buttonPressed = *_inputPinsAddress & (1 << _pinNumber);
    }

    return buttonPressed;
}