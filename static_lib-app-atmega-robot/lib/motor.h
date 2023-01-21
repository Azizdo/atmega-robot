#define F_CPU 8000000UL
#ifndef MOTOR_H
#define MOTOR_H
#include <avr/io.h>
#include <util/delay.h>

class Motor{
public:
    Motor();
    void goForward(uint8_t dutyCycleRoue1 = 100, uint8_t dutyCycleRoue2 = 100);
    void goBackward(uint8_t dutyCycleRoue1 = 100, uint8_t dutyCycleRoue2 = 100);
    void turnRight();
    void turnLeft();
    void r_eturn();
    void stop();
};

#endif