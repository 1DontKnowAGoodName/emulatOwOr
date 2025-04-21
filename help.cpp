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
#include <fstream>

class computer;
class instructionSet;

namespace menu{
  
}

namespace parser{
  std::vector<std::pair <std::string, int>> label;
  std::vector<std::pair <std::string, int>> define;

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
  std::string transMnemonic(std::string& inputStr);
  std::string transRegister(std::string& inputStr); //
  std::string transImmediate(std::string& inputStr); //
}

class instructionSet{
  public:
    instructionSet();
    ~instructionSet();

    // all the functions that should be able to get called and probably numbered
};

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
//parser
void parser::deleteComments(std::string& inputStr){
  if(inputStr.find(';') == std::string::npos){
    return;
  }
  inputStr.erase(inputStr.find(';'), std::string::npos);
}
void parser::deleteSpaces(std::string& inputStr){
  inputStr.erase(std::remove(inputStr.begin(), inputStr.end(), ' '), inputStr.end());
}
void parser::pushLabel(std::string& inputStr, std::vector<std::pair <std::string, int>>& label, computer comp){
  inputStr.erase(0, 1);
  std::string temp;
  for(char ch : inputStr){
    if (ch == ':'){ break;}
    if (ch == '_'){ std::cerr << "a _ used, this will very likely crash your program";}
    temp.push_back(ch);
  }
  inputStr.erase(0, temp.length() + 1);
  label.push_back({temp, comp.PC});
  return;
}
void parser::pushDefine(std::string& inputStr, std::vector<std::pair <std::string, int>>& define){
  if(inputStr.find("#define") != 0){
    return;
  }
  inputStr.erase(0, 7);
  std::string temp;
  while(!isdigit(inputStr.at(0))){
    if(inputStr.at(0) == '_') { std::cerr << "a _ used, this will very likely crash your program"; }
    temp.push_back(inputStr.at(0));
    inputStr.erase(0, 1);
  }
  define.push_back({temp, stoi(inputStr)});
}
bool parser::isLabel(std::string inputStr, std::vector<std::pair<std::string, int>>& label){
  inputStr.erase(0, 1);
  for(std::pair<std::string, int> pair : label){
    if(inputStr.find(pair.first) == 0 && inputStr.at(pair.first.length()) == '_'){
      return true;
    }
  }
  return false;
}
bool parser::isDefine(std::string inputStr, std::vector<std::pair<std::string, int>>& label){
  for(std::pair<std::string, int> pair : label){
    if(inputStr.find(pair.first) == 0 && inputStr.at(pair.first.length()) == '_'){
      return true;
    }
  }
  return false;
}
std::pair<std::string, int> parser::getLabel(std::string& inputStr, std::vector<std::pair<std::string, int>>& label){
  inputStr.erase(0, 1);
  for (std::pair<std::string, int> pair : label){
    if(inputStr.find(pair.first) == 0 && inputStr.at(pair.first.length()) == '_'){
      inputStr.erase(0, pair.first.length() + 1);
      return pair;
    }
  }
  return {"error", -1};
}
std::pair<std::string, int> parser::getDefine(std::string& inputStr, std::vector<std::pair<std::string, int>>& define){
  for (std::pair<std::string, int> pair : label){
    if(inputStr.find(pair.first) == 0 && inputStr.at(pair.first.length()) == '_'){
      inputStr.erase(0, pair.first.length() + 1);
      return pair;
    }
  }
};
std::string parser::command(std::string& inputStr){
  inputStr.erase(0, 1);
  if(inputStr == "break"){
    //break
  }
  else if(inputStr == "list"){
    //list
  }
  else if(inputStr == "broadcast"){
    //blank
  }
  else{
    std::cerr << "this command isn't recognized\n";
  }
  return "";
}
std::string parser::transRegister(std::string& inputStr){
  if (inputStr.at(1) == '8' || inputStr.at(1) == '9'){
    std::cerr << inputStr.at(1) << " is not a real register\n";
    return "err";
  }
  std::string temp;
  temp.push_back(inputStr.at(1));
  inputStr.erase(0, 2);
  return temp;
}
std::string parser::transImmediate(std::string& inputStr){
  std::string temp;
  for(int i = 0; i < 3; i++){
    if(!isdigit(inputStr.at(i))){ break; }
    temp.push_back(inputStr.at(i));
    if ((i + 1) == inputStr.length()){ break; }
  }
  if (stoi(temp) < 0 || stoi(temp) > 255){
    std::cerr << "immediate out of range, program won't handle this number\n"; 
  }
  return temp;
}

//computer
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
  if(pos < 0 || pos > 255){
    return;
  }
  regs.at(pos) = val;
  return;
}