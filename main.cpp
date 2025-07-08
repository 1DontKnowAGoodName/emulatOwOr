/* TODO:
  open a GUI from raylib
  
  with:
   >terminal
   >place to see all memory, preferably in maps
   >perhaps even the code in a code editor maybe????
   >a window for 16x16 8-bit screen or a larger screeen

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

int main(){ // do the the core logic first
bool askClockSpeed = true;
int clockSpeed = 1; // instructions per second
if (askClockSpeed){
  std::cout << "how fast do you want the clockspeed to be, in instructions per second? >>";
  std::cin >> clockSpeed;
  std::cout << '\n';
}
//open file
std::ifstream code{"/home/peter/Documents/CPUwUproject/emulatOwOr/resources/code.txt"};

if(!code.is_open()){
  std::cout << "was not able to open code file\n";
  return 1;
}

computer comp;

//preparse
int line = 0;
std::string codeLine;
while(std::getline(code, codeLine)){
  parser::deleteComments(codeLine);
  parser::deleteSpaces(codeLine);
  if(!(codeLine.at(0) == '/')){
    ++line;
  }
  parser::preparse(codeLine, parser::label, parser::define, line);
}

code.clear();
code.seekg(0, std::ios::beg); 

for(;;){ // main loop // this needs work, it needs to go like to the PC, but that's harrrrddd
  std::getline(code, comp.instructionReg)
  parser::deleteComments(comp.instructionReg);
  parser::deleteSpaces(comp.instructionReg);
  std::string str = parser::parse(comp.instructionReg, parser::define, parser::label);
  ++comp.PC
}

/*
open the windows and stuff

main loop{

execute

window drawing and stuff, and input and so on, maybe figure out the framerate, i might have to optimise this, but idk, it's C++
}
*/
}