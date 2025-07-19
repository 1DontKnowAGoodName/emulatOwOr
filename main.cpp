/* TODO:
  open a GUI from raylib
  
  with:
    >a window for 16x16 8-bit screen or a larger screeen

  >don't close GUI when done
*/

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

#include "computer.h"
#include "parser.h"
#include "instructionSet.h"

int main(){ // do the the core logic first
  bool askClockSpeed = true;
  int clockSpeed = 1; // instructions per second
  computer comp;
  std::string codeLine;
  std::vector<std::string> CodeVector;  // i store the code in a vector, for easier 
                                        // reference. some would call this 'cringe' and ' 
                                        // fucking deranged' but did i ever say i wasn't?

  
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
  
  while (std::getline(code, codeLine)){
    parser::deleteComments(codeLine);
    parser::deleteSpaces(codeLine);
    CodeVector.push_back(codeLine);
  }

  for(int line = 0; line < CodeVector.size(); ++line){
    parser::preparse(CodeVector.at(line)/*pass by copy*/, parser::label, parser::define, line);
  }

  for(comp.PC = 0; comp.PC < CodeVector.size(); comp.PC++){
    comp.instructionReg = parser::parse(CodeVector.at(comp.PC), parser::define, parser::label, parser::mnemToNum);
    comp.executeInstruction();
  }

  return 0;
}