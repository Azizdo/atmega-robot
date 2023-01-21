#define F_CPU 8000000UL
#ifndef RS232_H
#define RS232_H

#include <avr/io.h>
#include "memoire_24.h"

class Uart
{
public:
    Uart(){};

    void initiate(void);

    void transmitData(unsigned char data);

    void transmitString(char data[]);

    unsigned char receiveData(void);
};

#endif