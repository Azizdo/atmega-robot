#define F_CPU 8000000UL
#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>


class Interrupt
{
private:
    /*volatile uint8_t& _dataDirectionRegister; 
    volatile uint8_t& _externalInterruptMaskRegister;
    volatile uint8_t& _externalInterruptControlRegisterA;
*/
public:
    Interrupt();
    /*(volatile uint8_t& dataDirectionRegister,
    volatile uint8_t& externalInterruptMaskRegister, 
    volatile uint8_t& externalInterruptControlRegisterA);*/
    ~Interrupt();

    //methode
    void initialization();
    void initializationTimer();
};

#endif