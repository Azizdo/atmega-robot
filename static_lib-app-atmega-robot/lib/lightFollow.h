#define F_CPU 8000000UL
#ifndef LIGHTFOLLOW_H
#define LIGHTFOLLOW_H

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "pwm.h"
#include "can.h"
#include "led.h"
//#include "instructionMemory.h"


class LightFollow
{
public:
    LightFollow(){};
    void setAmbLight();
    void setLightPwm();
    //void setLightPwmSavingMode();
    uint8_t getPwmRoue1();
    uint8_t getPwmRoue2();

    uint8_t roue1_;
    uint8_t roue2_;

    uint16_t lumAmbG;
    uint16_t lumAmbD;

    uint8_t direction_;

    can convert;
    //InstructionMemory memory;
};

#endif