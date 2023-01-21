#define F_CPU 8000000UL
#ifndef CAPTEUR_H
#define CAPTEUR_H
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "led.h"
#include "can.h"
#include "pwm.h"
#include "instructionMemory.h"

class Capteur
{
public:

    enum class Mouvement
    {
        TOURNER_DROITE,
        TOURNER_GAUCHE,
        TOUT_DROIT,
        ARRETER
    };
    
    Capteur();
   
    float conversionNumericVolt();
    float trouverDistance();
    //Mouvement mouvement{Mouvement::TOUT_DROIT};
    Mouvement interpreteMouvement();
    void deplacement();
    uint8_t getPwmRoue1();
    uint8_t getPwmRoue2();
    //void interpreteMouvement();

    Pwm p;
    uint8_t roue1_;
    uint8_t roue2_;
};

#endif
