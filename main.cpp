/* TODO:
  open a GUI from raylib
  
  with:
   >terminal
   >place to see all memory, preferably in maps
   >perhaps even the code in a code editor maybe????
   >a window for 16x16 8-bit screen or a larger screeen

 -read input from file,

 -parser
  > for commands: /break, /list
    -> if break, then open a console for listing and stepping and editing variables || put it in the raylib GUI

 -execute
  >don't close GUI when done
*/
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

#include "computer.h"
#include "parser.h"
#include "instructionSet.h"



void pushLabel(std::string& inputStr, std::vector<std::pair <std::string, int>>& label, unsigned short int l){
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
void pushDefine(std::string& inputStr, std::vector<std::pair <std::string, int>>& define){
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
bool isLabel(std::string inputStr, std::vector<std::pair<std::string, int>>& label){
  for(std::pair<std::string, int> pair : label){
    if(inputStr.find(pair.first) == 0 && inputStr.at(pair.first.length()) == '_'){
      return true;
    }
  }
  return false;
}
bool isDefine(std::string inputStr, std::vector<std::pair<std::string, int>>& label){
  for(std::pair<std::string, int> pair : label){
    if(inputStr.find(pair.first) == 0 && inputStr.at(pair.first.length()) == '_'){
      return true;
    }
  }
  return false;
}
std::pair<std::string, int> getLabel(std::string& inputStr, std::vector<std::pair<std::string, int>>& label){
  for (std::pair<std::string, int> pair : label){
    if(inputStr.find(pair.first) == 0 && inputStr.at(pair.first.length()) == '_'){
      return pair;
    }
  }
  return {"error", -1};
}
std::pair<std::string, int> getDefine(std::string& inputStr, std::vector<std::pair<std::string, int>>& define){
  for (std::pair<std::string, int> pair : define){
    if(inputStr.find(pair.first) == 0 && inputStr.at(pair.first.length()) == '_'){
      return pair;
    }
  }
  return {"error", -1};
}


std::string transRegister(std::string& inputStr){
  if (inputStr.at(1) == '8' || inputStr.at(1) == '9'){
    std::cerr << inputStr.at(1) << " is not a real register\n";
    return "err";
  }
  return {inputStr.at(1)};
}
std::string transImmediate(std::string& inputStr){
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

void preparse(std::string& inputStr, std::vector<std::pair<std::string, int>>& label, std::vector<std::pair<std::string, int>>& define, unsigned short int l){
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
std::string command(std::string& inputStr){
  if(inputStr.find("/break") == 0){;
    //break
  }
  else if(inputStr.find("/list") == 0){;
    //list
  }
  else if(inputStr.find("broadcast")){;
    //blank
  }
  else{
    std::cerr << "this command isn't recognized\n";
  }
  return "";
}

std::string parse(std::string& inputStr, std::vector<std::pair<std::string, int>> define, std::vector<std::pair<std::string, int>> label){
  std::string outputStr;
  while(!inputStr.empty()){
    char temp = inputStr.at(0);

    if (temp == 'r'){ //registers
      outputStr += transRegister(inputStr);
      inputStr.erase(0,2);
    }
    
    else if(temp == '.' && isLabel(inputStr, label)){ //labels
      std::pair<std::string, int> pair = getLabel(inputStr, label);
      outputStr += std::to_string(pair.second);
      inputStr.erase(0, pair.first.length()+1);
    }

    else if (temp == '/'){
      command(inputStr);
      std::cerr << "this function isn't done yet, reminder for meeee\n";
    }
    
    else if (isdigit(temp) && !inputStr.empty()){ //immediates             //doesn't work, throws error
      outputStr += transImmediate(inputStr);
      while(!inputStr.empty() && isdigit(inputStr.at(0))){ //doesn't check for multiple immediates because that
        inputStr.erase(0, 1);         //because that wouldn't be possible, opcode + 2 imm > 16 bits
      }
    }

    else if (!isdigit(temp) && !inputStr.empty()){ //defines            //doesn't work
      std::pair<std::string, int> pair = getDefine(inputStr, define);
      outputStr += std::to_string(pair.second);
      inputStr.erase(0, pair.first.length()+1);
    }
  }
  return outputStr;
}

int main(){
  // computer Computer();
  std::vector<std::pair<std::string, int>> Dpair{{"one", 1}};
  std::vector<std::pair<std::string, int>> Lpair{{".two", 2}};
  std::string str {"one_.two_r534"};
  
  std::cout << parse(str, Dpair, Lpair) << '\n';

  return 0;
}