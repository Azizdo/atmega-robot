#define F_CPU 8000000UL
#ifndef PWM_H
#define PWM_H

#include <avr/io.h>
#include <avr/interrupt.h>

   enum mode {
      PHASE_CORRECT = (1 << WGM00),
      FAST_PWM = (1 << WGM01) | (1 << WGM00)
   };

   enum compare {
      NON_INVERTING = (1 << COM0A1) |  (1 << COM0B1),  
      INVERTING =  (1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0)
   };

   enum prescaler{
      NONE = (1 << CS00),
      PRESCALER8 = (1 << CS01),
      PRESCALER64 = (1 << CS01) | (1 << CS00),
      PRESCALER256 = (1 << CS02),
      PRESCALER1024 = (1 << CS02) | (1 << CS00)
   };

class Pwm{

public:
   Pwm();

   void initTimer0(mode mode = FAST_PWM,compare compare = NON_INVERTING, prescaler prescaler = PRESCALER8, uint8_t startValue = 0);

   void ajustDutyCycle(uint8_t dutyCycleRoue1 = 0, uint8_t dutyCycleRoue2 = 0);
   
   void goBackward();
};

#endif