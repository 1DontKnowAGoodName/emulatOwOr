/* TODO:
  open a GUI from raylib

  make codevector start at 1 instead of zero so coding in VScode will become easier.
  
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
#include <chrono>
#include <string>
#include <thread>
#include <vector>
#include <array>

#include "computer.h"
#include "parser.h"
#include "instructionSet.h"

#include "raylib.h"

// asserting dominance
#undef windowHeight
#define windowHeight 640
#undef windowWidth
#define windowWidth 1280

int main(){ // do the the core logic first
  InitWindow(windowWidth, windowHeight, "EmulatOwOr");
  if(!IsWindowReady()){
    std::cerr << "something fucked up dude, window is glitched apparently\n";
  }
  SetExitKey(KEY_END);
  SetWindowIcon(LoadImage("/home/peter/Documents/CPUwUproject/emulatOwOr/resources/appICON2.png"));
  
  computer comp;

  for(int i = 0; i < 255; i++){ //clear ram and Vram
    comp.sram(0, i);
  }
  for(short i = 0; i < 2047; i++){ //clear ram and Vram
    comp.sVram(0 , i);
  }

  bool askClockSpeed = false;
  int clockSpeed = 100; // ms per instruction

  std::string codeLine; 
  std::vector<std::string> CodeVector;  // i store the code in a vector, for easier reference. some would call this 'cringe' and 'fucking deranged' but did i ever say i wasn't?
  CodeVector.push_back("NOP"); //this is so the VScode line counter and PC line up, so you can jump where you want without subtracting or adding one

  if (askClockSpeed){
    std::cout << "how fast do you want the clockspeed to be, in ms per instruction? >>";
    std::cin >> clockSpeed;
    std::cout << '\n';
  }

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
    
    BeginDrawing();

    for (int y = 0; y < 32; ++y){
      for (int x = 0; x < 64; ++x){
        if(comp.gVram(y * 64 + x) == true){
          DrawRectangle(x*20, y*20, 20, 20, WHITE);
        }
        else{
          DrawRectangle(x*20, y*20, 20, 20, BLACK);
        }
      }
    }

    EndDrawing();

    if(comp.PC > 256){
      std::cout << "be aware that your program is longer than that this could handle";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(clockSpeed));
  }

  getchar();
  return 0;
}