#include "motor.h"
#include "pwm.h"

Motor::Motor()
{
   DDRB |= (1 << PB3) | (1 << PB4) | (1 << PB2) | (1 << PB5);
};

void Motor::goForward(uint8_t dutyCycleRoue1, uint8_t dutyCycleRoue2)
{

   Pwm pwm;
   pwm.initTimer0();
   pwm.ajustDutyCycle(dutyCycleRoue1, dutyCycleRoue2);
}

void Motor::goBackward(uint8_t dutyCycleRoue1, uint8_t dutyCycleRoue2)
{
   PORTB |= (1 << PB2) | (1 << PB5);
   Pwm pwm;
   pwm.initTimer0();
   pwm.ajustDutyCycle(dutyCycleRoue1, dutyCycleRoue2);
}

void Motor::turnRight()
{
   Pwm pwm;
   pwm.initTimer0();
   pwm.ajustDutyCycle(0, 100);
   _delay_ms(97);
}

void Motor::turnLeft()
{
   Pwm pwm;
   pwm.initTimer0();
   pwm.ajustDutyCycle(100, 0);
   _delay_ms(97);
}

void Motor::stop()
{
   Pwm pwm;
   pwm.initTimer0();
   pwm.ajustDutyCycle(); //par défaut à zéro
}
 void Motor::r_eturn(){
   goForward();
   _delay_ms(277);
   turnRight();
   goForward();
   _delay_ms(60);
   turnRight();
   _delay_ms(15);
   goForward();
   _delay_ms(160);
   stop();
}
