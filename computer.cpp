#include "computer.h"
#include "parser.h"
#include "instructionSet.h"

computer::computer() : PC(0) {}

void computer::executeInstruction(){
  int cache = static_cast<int>(this->instructionReg.at(0) - '0');
  this->instructionReg.erase(0, 1);

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
bool computer::gVram (short int pos){
  return vidRAM.at(pos);
}
void computer::sReg (uint8_t val, uint8_t pos){
  if(pos <= 0 || pos >= 8){
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
void computer::sVram (uint8_t val, short int pos){
  if(pos < 0 || pos > 2047){
    return;
  }
  if (val > 0)
    vidRAM.at(pos) = 1;
  else
    vidRAM.at(pos) = 0;
  return;
}