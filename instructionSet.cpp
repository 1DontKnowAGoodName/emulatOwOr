#include "instructionSet.h"
#include "parser.h"
#include "computer.h"

namespace ISA{
  // all the functions that should be able to get called and probably numbered

  // function that returns parameters<string>
  int RI(std::string& inputStr, char ch);
  void NOP(std::string& parameter);
  //template <typename T> const static std::unordered_map<int, T> numToFunk;
};

// template <typename T> const static std::unordered_map<int, T> numToFunk{
//   {0,},
//   {1,},
//   {2,},
//   {3,},
//   {4,},
//   {5,},
//   {6,},
//   {7,},
//   {8,},
//   {9,},
//   {10,},
//   {11,},
//   {12,},
//   {13,},
//   {14,},
//   {15,},
//   {16,},
//   {17,},
//   {18,},
//   {19,},
//   {20,},
//   {21,},
//   {22,},
//   {23,},
//   {24,},
//   {25,},
//   {26,},
//   {27,},
//   {28,},
//   {29,},
//   {30,},
//   {31,}, // mayhaps we make this just a big switch statement
// };

uint8_t ISA::RI(std::string& inputStr, char ch){
  switch (ch){
  case 'r':
    return std::stoi(inputStr.substr(0,1));
    break;
  case 'i':
  case 'd':
  case 'l'
    return std::stoi(inputStr.substr(0,3));
    break;
  default:
    std::cerr << "can't find put-in char in returnInt()\n";
    break;
  }
  return 0;
}

//OR: |
//NOT: ~
//NOR: ~( | )
//NAND: ~( & )
//XOR: ^
//BSR: >>
//BSL: <<

void ISA::NOP(std::string& parameter){
  return;
}
void ISA::ADD(std::string& par, computer comp){
  comp.sReg(comp.gReg(ISA::RI(par, 'r')) + comp.gReg(ISA::RI(par, 'r')), ISA::RI(par, 'r'));
}
void ISA::SUB(std::string& par, computer comp){
  comp.sReg(comp.gReg(ISA::RI(par, 'r')) - comp.gReg(ISA::RI(par, 'r')), ISA::RI(par, 'r'));
}
void ISA::AND(std::string& par, computer comp){
  comp.sReg(comp.gReg(ISA::RI(par, 'r')) & comp.gReg(ISA::RI(par, 'r')), ISA::RI(par, 'r'));
}