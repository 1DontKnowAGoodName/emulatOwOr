#include "parser.h"
#include "computer.h"
#include "instructionSet.h"

class computer;
namespace instructionSet{}
namespace menu{}

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

  void pushLabel(std::string& inputStr, std::vector<std::pair <std::string, int>>& label, unsigned short int l); //
  void pushDefine(std::string& inputStr, std::vector<std::pair <std::string, int>>& define); //
  bool isLabel(std::string inputStr, std::vector<std::pair <std::string, int>>& define); //
  bool isDefine(std::string inputStr, std::vector<std::pair <std::string, int>>& define); //
  std::pair<std::string, int> getLabel(std::string& inputStr, std::vector<std::pair<std::string, int>>& label); //
  std::pair<std::string, int> getDefine(std::string& inputStr, std::vector<std::pair<std::string, int>>& define); //

  void preparse(std::string& inputStr, std::vector<std::pair<std::string, int>>& label, std::vector<std::pair<std::string, int>>& define, unsigned short int l); // for label and define
  std::string parse(std::string& inputStr); 

  std::string command(std::string& inputStr); //
  template <typename T> T transMnemonic(std::string& inputStr, const std::unordered_map<std::string, int>& mnemToNum); // only 3 letter mnem
  std::string transRegister(std::string& inputStr); //
  std::string transImmediate(std::string& inputStr); //
}

void parser::deleteComments(std::string& inputStr){
  if(inputStr.find(';') == std::string::npos){
    return;
  }
  inputStr.erase(inputStr.find(';'), std::string::npos);
}
void parser::deleteSpaces(std::string& inputStr){
  inputStr.erase(std::remove(inputStr.begin(), inputStr.end(), ' '), inputStr.end());
}

void parser::pushLabel(std::string& inputStr, std::vector<std::pair <std::string, int>>& label, unsigned short int l){
  std::string temp;
  for(char ch : inputStr){
    if (ch == ':'){ break;}
    if (ch == '_'){ std::cerr << "a _ used, this will very likely crash your program";}
    temp.push_back(ch);
  }
  inputStr.erase(0, temp.length() + 1);
  label.push_back({temp, l});
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
  return {"error", -1};
}

void parser::preparse(std::string& inputStr, std::vector<std::pair<std::string, int>>& label, std::vector<std::pair<std::string, int>>& define, unsigned short int l){
  if(inputStr.at(0) == '.' && isLabel(inputStr, label)){
    std::cerr << "you declared an already declared label\n";
  }
  else if(inputStr.at(0) == '.' && !isLabel(inputStr, label)){
    pushLabel(inputStr, label, l);
  }
  else if(inputStr.at(0) == '#'){
    if(isDefine(inputStr, define)){
      std::cerr << "you defined an already used define\n";
      return;
    }
    pushDefine(inputStr, define);
  }
  return;
}
std::string parser::parse(std::string& inputStr){
  std::string outputStr;
  while(!inputStr.empty()){
    char temp = inputStr.at(0);
    if (temp == 'r'){ //registers
      outputStr += transRegister(inputStr);
      inputStr.erase(0,2);
    }
    
    else if(temp == '.' && isLabel(inputStr, label)){ //labels
      std::pair<std::string, int> pair = getLabel(inputStr, label);
      outputStr += pair.second;
      inputStr.erase(0, pair.first.length());
    }

    else if (isdigit(temp)){ //immediates
      outputStr += transImmediate(inputStr);
      while(isdigit(inputStr.at(0))){ //doesn't check for multiple immediates because that
        inputStr.erase(0, 1);         //because that wouldn't be possible, opcode + 2 imm > 16 bits
      }
    }

    else if (!isdigit(temp)){ //defines
      std::pair<std::string, int> pair = getDefine(inputStr, define);
      outputStr += pair.second;
      inputStr.erase(0, pair.first.length());
    }
  }
  return outputStr;
}

std::string parser::command(std::string& inputStr){
  inputStr.erase(0, 1);
  // if(inputStr == "break"){;
  //   //break
  // }
  // else if(inputStr == "list"){;
  //   //list
  // }
  // else if(inputStr == "broadcast"){;
  //   //blank
  // }
  // else{
  //   std::cerr << "this command isn't recognized\n";
  // }
  // return "";
}
template <typename T> T parser::transMnemonic(std::string& inputStr, const std::unordered_map<std::string, int>& mnemToNum){
  return itos(mnemToNum.find(inputStr.substr(0, 3))->second);
}
std::string parser::transRegister(std::string& inputStr){
  if (inputStr.at(1) == '8' || inputStr.at(1) == '9'){
    std::cerr << inputStr.at(1) << " is not a real register\n";
    return "err";
  }
  return {inputStr.at(1)};
}
std::string parser::transImmediate(std::string& inputStr){
  std::string temp;
  for(int i = 0; i < 3; i++){
    if(!isdigit(inputStr.at(i))){ break; }
    temp.push_back(inputStr.at(i));
    if ((i + 1) == inputStr.length()){ break; }
  }
  while(temp.length() < 3){
    temp.insert(0, "0");
  }
  return temp;
  if (stoi(temp) < 0 || stoi(temp) > 255){
    std::cerr << "immediate out of range, program won't handle this number\n"; 
  }
  return temp;
}