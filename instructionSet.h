#ifndef ISA_H
#define ISA_H

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

class computer;

namespace ISA {
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
 
  extern const std::unordered_map<int, void (*)(std::string& par, computer& C)> numToFunk;
}

#endif