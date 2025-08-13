#ifndef COMPUTER_H
#define COMPUTER_H

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <bitset>
#include <string>
#include <vector>
#include <array>

class computer{
  private:
    std::array <uint8_t, 8> regs;
    std::array <uint8_t, 256> RAM;
    std::array <bool, 2048> vidRAM;
  
  public:
    computer();
  
    std::string instructionReg;
    unsigned short int PC;
    
    void executeInstruction();

    uint8_t gReg (uint8_t pos);
    uint8_t gram (uint8_t pos);
    bool gVram (short int pos);
    void sReg (uint8_t val, uint8_t pos);
    void sram (uint8_t val, uint8_t pos);
    void sVram (uint8_t val, short int pos);
  };

#endif