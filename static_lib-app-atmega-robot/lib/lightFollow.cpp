#include "lightFollow.h"

uint8_t LightFollow::getPwmRoue1(){
    return roue1_;
}

uint8_t LightFollow::getPwmRoue2(){
    return roue2_;
}

void LightFollow::setAmbLight()
{   
    uint16_t sumLumD = 0, sumLumG = 0;
    uint8_t loopCounter = 0;
    uint8_t nElements = 6;

    while (loopCounter < nElements)
    {

        uint8_t lumD = convert.lecture(PA4) >> 2;
        uint8_t lumG = convert.lecture(PA2) >> 2;
        sumLumD += lumD;
        sumLumG += lumG;
        loopCounter++;
    }

    lumAmbD = sumLumD / nElements;
    lumAmbG = sumLumG / nElements;

}

void LightFollow::setLightPwm()
{
    const uint8_t lumMax = 250;
    const uint8_t pwmMax = 255;

    Pwm pwm;
    pwm.initTimer0();
   
    uint8_t readLumD = convert.lecture(PA4) >> 2;
    uint8_t readLumG = convert.lecture(PA2) >> 2;

    if (readLumG <= lumAmbG)
    {
        readLumG = lumAmbG;
    }
    else if (readLumG > lumMax)
    {
        readLumG = lumMax;
    }

    if (readLumD <= lumAmbD)
    {
        readLumD = lumAmbD;
    }
    else if (readLumD > lumMax)
    {
        readLumD = lumMax;
    }
    uint16_t pwmDroite = ((readLumD - lumAmbD) * pwmMax) / (lumMax - lumAmbD);
    uint16_t pwmGauche = ((readLumG - lumAmbG) * pwmMax) / (lumMax - lumAmbG);

    uint16_t diff = pwmDroite - pwmGauche;

    if (pwmDroite > 10 && pwmGauche > 10)
    {
        if (diff > 75)
        {
            if (pwmGauche < pwmDroite)
            {
                PORTB &= ~(1 << PB2);
                PORTB |= (1 << PB5);
                pwm.ajustDutyCycle(pwmDroite, pwmDroite);
                roue1_ = pwmDroite;
                roue2_ = pwmDroite;
                direction_ = 1;
                
            }
            else
            {
                PORTB &= ~(1 << PB5);
                PORTB |= (1 << PB2);
                pwm.ajustDutyCycle(pwmGauche, pwmGauche);
                roue1_ = pwmGauche;
                roue2_ = pwmGauche;
                direction_ = 2;
                
            }
        }

        else
        {
            PORTB &= ~(1 << PB2) & ~(1 << PB5);
            pwm.ajustDutyCycle(pwmGauche, pwmDroite);
            roue1_ = pwmGauche;
            roue2_ = pwmDroite;
            direction_ = 3;
        }
    }
    else
    {
        pwm.ajustDutyCycle(0, 0);
        roue1_ = 0;
        roue2_ = 0;
        direction_ = 4;
        
    }
    
}