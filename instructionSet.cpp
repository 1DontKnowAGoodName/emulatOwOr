#include "instructionSet.h"
#include "parser.h"
#include "computer.h"

namespace ISA{
  uint8_t RI(const std::string& inputStr, char ch, int place);

  void NOP(std::string& par, computer& C);
  void LDI(std::string& par, computer& C);
  void STO(std::string& par, computer& C);
  void GET(std::string& par, computer& C);
  void MOV(std::string& par, computer& C);
  void JIT(std::string& par, computer& C);
  void ECT(std::string& par, computer& C);
  void GCT(std::string& par, computer& C);
  void GTV(std::string& par, computer& C);
  void PTV(std::string& par, computer& C);
  void HLT(std::string& par, computer& C);

  void ADD(std::string& par, computer& C);
  void SUB(std::string& par, computer& C);
  void AND(std::string& par, computer& C);
  void ORE(std::string& par, computer& C);
  void XOR(std::string& par, computer& C);
  void NOT(std::string& par, computer& C);
  void RBS(std::string& par, computer& C);
  void LBS(std::string& par, computer& C);
  void CMP(std::string& par, computer& C);
  void MLT(std::string& par, computer& C);
  void ODD(std::string& par, computer& C);
  void INC(std::string& par, computer& C);
  void DCR(std::string& par, computer& C);
  const std::unordered_map<int, void (*)(std::string&, computer&)> numToFunk{
    {0, NOP},
    {1, LDI},
    {2, STO},
    {3, GET},
    {4, MOV},
    {5, NOP},
    {6, NOP},
    {7, NOP},
    {8, NOP},
    {9, NOP},
    {10, JIT},
    {11, ECT},
    {12, GCT},
    {13, GTV},
    {14, PTV},
    {15, HLT},
    {16, NOP},
    {17, ADD},
    {18, SUB},
    {19, AND},
    {20, ORE},
    {21, XOR},
    {22, NOT},
    {23, NOP},
    {24, RBS},
    {25, LBS},
    {26, CMP},
    {27, NOP},
    {28, MLT},
    {29, ODD},
    {30, INC},
    {31, DCR}
  };
};

uint8_t ISA::RI(const std::string& inputStr, char ch, int place){ //assumes mnemonic is read and deleted beforehand
  switch (ch){
  case 'r': //register
    return std::stoi(inputStr.substr(place,1));
    break;
  case 'i': //immediate   |
  case 'd': //define      |- should all be the same, three chars, not more, not less.
  case 'l': //label       |
    return std::stoi(inputStr.substr(place,3));;
    break;
  default:
    std::cerr << "can't find put-in char in RI()\n";
    break;
  }
  return 0;
}

void ISA::NOP(std::string& par, computer& C){
  return;
}
void ISA::LDI(std::string& par, computer& C){
  C.sReg(ISA::RI(par, 'i', 1), ISA::RI(par, 'r', 0));
}
void ISA::STO(std::string& par, computer& C){
  C.sram(C.gReg(ISA::RI(par, 'r', 0)), ISA::RI(par, 'i', 1));
}
void ISA::GET(std::string& par, computer& C){
  C.sReg(C.gram(ISA::RI(par, 'i', 1)), ISA::RI(par, 'r', 0));
}
void ISA::MOV(std::string& par, computer& C){
  C.sReg(C.gReg(ISA::RI(par, 'r', 1)), ISA::RI(par, 'r', 0));
}
void ISA::JIT(std::string& par, computer& C){
  if(C.gReg(ISA::RI(par, 'r', 1)) == C.gReg(ISA::RI(par, 'r', 2))){
    C.PC = C.gReg(ISA::RI(par, 'r', 0)) - 1;
  }
}
void ISA::ECT(std::string& par, computer& C){
  C.PC = ISA::RI(par, 'i', 0) - 1;
}
void ISA::GCT(std::string& par, computer& C){
  C.sReg(C.PC, ISA::RI(par, 'r', 0));
}
void ISA::GTV(std::string& par, computer& C){
  C.sReg(C.gVram(ISA::RI(par, 'i', 1)), ISA::RI(par, 'r', 0));
}
void ISA::PTV(std::string& par, computer& C){
  C.sVram(C.gReg(ISA::RI(par, 'r', 0)), ISA::RI(par, 'i', 1));
}
void ISA::HLT(std::string& par, computer& C){
  getchar();
}

void ISA::ADD(std::string& par, computer& C){
  C.sReg(C.gReg(ISA::RI(par, 'r', 1 )) + C.gReg(ISA::RI(par,'r', 2)), ISA::RI(par, 'r', 0));
}
void ISA::SUB(std::string& par, computer& C){
  C.sReg(C.gReg(ISA::RI(par, 'r', 1)) - C.gReg(ISA::RI(par, 'r', 2)), ISA::RI(par, 'r', 0));
}
void ISA::AND(std::string& par, computer& C){
  C.sReg(C.gReg(ISA::RI(par, 'r', 1)) & C.gReg(ISA::RI(par, 'r', 2)), ISA::RI(par, 'r', 0));
}
void ISA::ORE(std::string& par, computer& C){
  C.sReg(C.gReg(ISA::RI(par, 'r', 1)) | C.gReg(ISA::RI(par, 'r', 2)), ISA::RI(par, 'r', 0));
}
void ISA::XOR(std::string& par, computer& C){
  C.sReg(C.gReg(ISA::RI(par, 'r', 1)) ^ C.gReg(ISA::RI(par, 'r', 2)), ISA::RI(par, 'r', 0));
}
void ISA::NOT(std::string& par, computer& C){
  C.sReg(~C.gReg(ISA::RI(par, 'r',1)), ISA::RI(par, 'r', 0));
}
void ISA::RBS(std::string& par, computer& C){
  C.sReg(C.gReg(ISA::RI(par, 'r', 1)) >> C.gReg(ISA::RI(par, 'r', 2)), ISA::RI(par, 'r', 0));
}
void ISA::LBS(std::string& par, computer& C){
  C.sReg(C.gReg(ISA::RI(par, 'r', 1)) << C.gReg(ISA::RI(par, 'r', 2)), ISA::RI(par, 'r', 0));
}
void ISA::CMP(std::string& par, computer& C){
  C.sReg(C.gReg(ISA::RI(par, 'r', 1)) == C.gReg(ISA::RI(par, 'r', 2)), ISA::RI(par, 'r', 0));
}
void ISA::MLT(std::string& par, computer& C){
  C.sReg(C.gReg(ISA::RI(par, 'r', 1)) * C.gReg(ISA::RI(par, 'r', 2)), ISA::RI(par, 'r', 0));
}
void ISA::ODD(std::string& par, computer& C){
  C.sReg((C.gReg(ISA::RI(par, 'r', 1)) % 2 == 0) ? 0 : 1, ISA::RI(par, 'r', 0));
}
void ISA::INC(std::string& par, computer& C){
  C.sReg(C.gReg(ISA::RI(par, 'r', 1)) + 1, ISA::RI(par, 'r', 0));
}
void ISA::DCR(std::string& par, computer& C){
  C.sReg(C.gReg(ISA::RI(par, 'r', 1)) - 1, ISA::RI(par, 'r', 0));
}