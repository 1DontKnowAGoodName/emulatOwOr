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

  // function that returns parameters<string>
  int RI(std::string& inputStr, char ch);

  void NOP(std::string& parameter);
  // template <typename T> const static std::unordered_map<int, T> numToFunk;
}

#endif