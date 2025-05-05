#ifndef PARSER_H
#define PARSER_H

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

class computer;

namespace parser{
  std::vector<std::pair <std::string, int>> label;
  std::vector<std::pair <std::string, int>> define;

  const static std::unordered_map<std::string, uint8_t> mnemToNum{
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
    {"PTV", 13},
    {"HLT", 14},
    {"PSS", 15},
    {"ADD", 16},
    {"SUB", 17},
    {"AND", 18},
    {"AND", 19},
    {"ORE", 20},
    {"XOR", 21},
    {"NVA", 22},
    {"NVB", 23},
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

  void pushLabel(std::string& inputStr, std::vector<std::pair <std::string, int>>& label, computer comp); //
  void pushDefine(std::string& inputStr, std::vector<std::pair <std::string, int>>& define); //
  bool isLabel(std::string inputStr, std::vector<std::pair <std::string, int>>& define); //
  bool isDefine(std::string inputStr, std::vector<std::pair <std::string, int>>& define); //
  std::pair<std::string, int> getLabel(std::string& inputStr, std::vector<std::pair<std::string, int>>& label); //
  std::pair<std::string, int> getDefine(std::string& inputStr, std::vector<std::pair<std::string, int>>& define); //

  std::string parse(std::string& inputStr); //CHECK CONDITIONS BEFOREHAND!!! THERE IS NO CHECKING IN THE FUNCTIONS ITSELF
  std::string command(std::string& inputStr); //
  template <typename T> T transMnemonic(std::string& inputStr, const std::unordered_map<std::string, int>& mnemToNum); // only 3 letter mnem
  std::string transRegister(std::string& inputStr); //
  std::string transImmediate(std::string& inputStr); //
}

#endif