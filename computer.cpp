#include "computer.h"
#include "parser.h"
#include "instructionSet.h"

computer::computer() : PC(0) {}

void computer::executeInstruction(){
  char cache = this->instructionReg.at(0);
  this->instructionReg.erase(0, 0);

  ISA::numToFunk.find(cache)->second(this->instructionReg, *this);
  this->instructionReg.erase();
  return;
}

uint8_t computer::gReg(uint8_t pos){
  if (pos == 0){return 0;}
  else if (pos < 1 || pos > 7){return 255;}
  return regs.at(pos);
}
uint8_t computer::gram (uint8_t pos){
  return RAM.at(pos);
}
uint8_t computer::gVram (uint8_t pos){
  return vidRAM.at(pos);
}
void computer::sReg (uint8_t val, uint8_t pos){
  if(pos == 0 || pos < 1 || pos > 7){
    return;
  }
  regs.at(pos) = val;
  return;
}
void computer::sram (uint8_t val, uint8_t pos){
  if(pos < 0 || pos > 255){
    return;
  }
  RAM.at(pos) = val;
  return;
}
void computer::sVram (uint8_t val, uint8_t pos){
  if(pos < 0 || pos > 255){
    return;
  }
  vidRAM.at(pos) = val;
  return;
}