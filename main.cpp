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

int main(){
  // computer Computer();
  std::vector<std::pair<std::string, int>> pair;
  std::string str {"NOP r1; 124; comment"};

  parser::deleteComments(str);
  std::cout << str << '\n';

  return 0;
}