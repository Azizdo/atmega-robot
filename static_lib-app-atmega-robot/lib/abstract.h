#define F_CPU 8000000UL
#ifndef ABSTRACT_H
#define ABSTRACT_H
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "memoire_24.h"
#include "can.h"

class Abstract
{
public:
    can convert;
    Memoire24CXXX memoire;
};

#endif