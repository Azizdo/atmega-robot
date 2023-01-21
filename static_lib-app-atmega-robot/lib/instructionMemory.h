#include <avr/io.h>
#include <util/delay.h>
#include "memoire_24.h"

class InstructionMemory
{
public: 
    InstructionMemory();

    void writeInstruction(uint8_t instruction, 
                            uint8_t firstOperand, uint8_t secondOperand);
    
    uint8_t readInstruction();
    // uint8_t readOperands();
    uint8_t readOp1();

    uint8_t readOp2();

   uint16_t getWritingAddress() const;
    uint16_t getReadingAddress() const;

    uint16_t readingAddress_ = 0; 
    uint16_t writingAddress_ = 0;
    

private:
    
    Memoire24CXXX memory;
};