#ifndef PARSER_H
#define PARSER_H

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

namespace parser{
  extern std::vector<std::pair <std::string, int>> label;
  extern std::vector<std::pair <std::string, int>> define;

  const static std::unordered_map<std::string, int> mnemToNum{
    {"NOP", 0},
    {"LDI", 1},
    {"STO", 2},
    {"GET", 3},
    {"MOV", 4},
    {"NDY", 0},
    {"NDY", 0},
    {"NDY", 0},
    {"NDY", 0},
    {"NDY", 0},
    {"JIT", 10},
    {"ECT", 11},
    {"GCT", 12},
    {"GTV", 13},
    {"PTV", 14},
    {"HLT", 15},
    {"PSS", 16},
    {"ADD", 17},
    {"SUB", 18},
    {"AND", 19},
    {"ORE", 20},
    {"XOR", 21},
    {"NOT", 22},
    {"NDY", 0},
    {"RBS", 24},
    {"LBS", 25},
    {"COM", 26},
    {"NDY", 0},
    {"MLT", 28},
    {"ODD", 29},
    {"INC", 30},
    {"DEC", 31},
  };

  void deleteSpaces(std::string& inputStr);
  void deleteComments(std::string& inputStr);

  void pushLabel(std::string& inputStr, std::vector<std::pair <std::string, int>>& label, unsigned short int l);
  void pushDefine(std::string& inputStr, std::vector<std::pair <std::string, int>>& define);
  bool isLabel(std::string inputStr, const std::vector<std::pair <std::string, int>>& define);
  bool isDefine(std::string inputStr, const std::vector<std::pair <std::string, int>>& define);
  std::pair<std::string, int> getLabel(std::string& inputStr, const std::vector<std::pair<std::string, int>>& label);
  std::pair<std::string, int> getDefine(std::string& inputStr, const std::vector<std::pair<std::string, int>>& define);

  std::string addLength(std::string inputStr);

  std::string parse(std::string& inputStr, std::vector<std::pair<std::string, int>> define, const std::vector<std::pair<std::string, int>> label, const std::unordered_map<std::string, int> &mnemToNum);
  void preparse(std::string inputStr, std::vector<std::pair<std::string, int>>& label, std::vector<std::pair<std::string, int>>& define, unsigned short int l);

  std::string command(std::string& inputStr);
  auto transMnemonic(std::string& inputStr, const std::unordered_map<std::string, int>& mnemToNum);
  std::string transRegister(std::string& inputStr);
  std::string transImmediate(std::string& inputStr);
}

#endif