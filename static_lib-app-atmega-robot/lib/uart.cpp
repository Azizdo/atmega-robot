#include "memoire_24.h"
#include "uart.h"

void Uart::initiate(void)
{
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0A = 0;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void Uart::transmitData(unsigned char data)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }
    UDR0 = data;
}

void Uart::transmitString(char data[])
{
    uint8_t index = 0;
    while (data[index] != '\0')
    {
        transmitData(data[index]);
        ++index;
    }
}

unsigned char Uart::receiveData(void)
{

    while (!(UCSR0A & (1 << RXC0)))
        ;

    return UDR0;
}
