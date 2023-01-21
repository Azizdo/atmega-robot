//implementation
#include "interrupt.h"

//Interrupt::Interrupt(){
    //liste dinitialisation, prend ses valeurs par defaut
    /*_dataDirectionRegister(dataDirectionRegister), 
    _externalInterruptMaskRegister(externalInterruptMaskRegister),
    _externalInterruptControlRegisterA(externalInterruptControlRegisterA)
{*/
    //mtn le constructeur plus etre sur des operations sur choses quon a
    //_dataDirectionRegister &= ~(1 << _pinNumber);

Interrupt::Interrupt(){
    
}

void Interrupt::initialization(){
        /*cli();
        
        _dataDirectionRegister &= ~(1 << DDD2) & ~(1 << DDD3); 

        _externalInterruptMaskRegister |= 1 << INT0; //| 1 << INT1; 
    
        _externalInterruptControlRegisterA |= 1 << ISC00 | 1 << ISC01; 

        _externalInterruptControlRegisterA |= (1 << ISC00) | (1 << ISC01); 
        _externalInterruptControlRegisterA |= (1 << ISC10) | (1 << ISC11); 


        sei();*/

}

void Interrupt::initializationTimer(){
    cli();
        

    EIMSK |= 1 << INT0; //| 1 << INT1;
    EICRA |= (1 << ISC00) | (1 << ISC01); 

    sei();

}
Interrupt::~Interrupt(){
}

//}

