#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>
#include <cstdint>
#include <fstream>
#include <array>
#include <algorithm>
#include <bitset>
#include <sstream>
#include "computer.h"


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
  regs.at(pos) = val;
  return;
}
void computer::sVram (uint8_t val, uint8_t pos){