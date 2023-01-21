#include "pwm.h"

// const uint8_t maxPwm = 255;
// const uint8_t pourcentage = 100;

Pwm::Pwm(){};

void Pwm::initTimer0(mode mode, compare compare, prescaler prescaler, uint8_t startValue)
{
   cli();
   //DDRB |= (1<<PB3) | (1<<PB4);
   DDRB |= (1 << PB3) | (1 << PB4);
   TCNT0 = startValue;
   TCCR0A = mode | compare;
   TCCR0B = prescaler;
   sei();
}

void Pwm::ajustDutyCycle(uint8_t dutyCycleRoue1, uint8_t dutyCycleRoue2)
{
   OCR0A = (dutyCycleRoue1); /// pourcentage) * maxPwm;
   OCR0B = (dutyCycleRoue2); /// pourcentage) * maxPwm;
}

void Pwm::goBackward()
{
   DDRB |= (1 << PB2) | (1 << PB5);
   PORTB |= (1 << PB2) | (1 << PB5);
}
