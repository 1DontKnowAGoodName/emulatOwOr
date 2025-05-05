#ifndef COMPUTER_H
#define COMPUTER_H

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

class computer{
  private:
    std::array <uint8_t, 8> regs;
    std::array <uint8_t, 256> RAM;
    std::array <uint8_t, 256> vidRAM;
  
  public:
    computer();
    ~computer();
  
    std::string instructionReg;
    unsigned short int PC;
    
    uint8_t gReg (uint8_t pos); // remember that there's a zero read register //
    uint8_t gram (uint8_t pos); //
    uint8_t gVram (uint8_t pos); //
    void sReg (uint8_t val, uint8_t pos); //
    void sram (uint8_t val, uint8_t pos); //
    void sVram (uint8_t val, uint8_t pos); //
  
    void decodeInstruction();
  };

#endif