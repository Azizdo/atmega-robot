#include "./instructionMemory.h"

InstructionMemory::InstructionMemory() 
{
}

void InstructionMemory::writeInstruction(uint8_t instruction, 
                                            uint8_t firstOperand, uint8_t secondOperand)
{   uint8_t memoryDelay = 5;
    
    _delay_ms(memoryDelay);
    memory.ecriture(writingAddress_++, instruction);
    _delay_ms(memoryDelay);
    memory.ecriture(writingAddress_++, firstOperand);
    _delay_ms(memoryDelay);
    memory.ecriture(writingAddress_++, secondOperand);
}

uint16_t InstructionMemory::getWritingAddress() const{
    return writingAddress_;
}

uint16_t InstructionMemory::getReadingAddress() const{
    return readingAddress_;
}

uint8_t InstructionMemory::readInstruction()
{   
    uint8_t instructionRead;
    _delay_ms(5);
    memory.lecture(readingAddress_++, &instructionRead);

    return instructionRead;
}
uint8_t InstructionMemory::readOp1()
{   
    uint8_t operandRead1;
    _delay_ms(5);
    memory.lecture(readingAddress_++, &operandRead1);

    return operandRead1;
}

uint8_t InstructionMemory::readOp2()
{   
    uint8_t operandRead2;
    _delay_ms(5);
    memory.lecture(readingAddress_++, &operandRead2);

    return operandRead2;
}

    

