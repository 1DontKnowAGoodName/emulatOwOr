#ifndef ISA_H
#define ISA_H

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

namespace ISA {
  // all the functions that should be able to get called and probably numbered
  uint8_t RI(const std::string& inputStr, char ch, int place);

  void NOP(std::string& parameter);
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
 
  const static std::unordered_map<int, void *> numToFunk{
  {0, NOP},
  {1, LDI},
  {2, STO},
  {3, GET},
  {4, MOV},
  {5, },
  {6, },
  {7, },
  {8, },
  {9, },
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
  {23, },
  {24,RBS},
  {25,LBS},
  {26,CMP},
  {27, },
  {28,MLT},
  {29,ODD},
  {30,INC},
  {31,DCR}, // mayhaps we make this just a big switch statement
};
}

#endif