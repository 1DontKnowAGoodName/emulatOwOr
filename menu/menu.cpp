#include <iostream>
#include <bitset>
#include <array>
#include "raylib.h"

// asserting dominance
#undef windowHeight
#define windowHeight 640
#undef windowWidth
#define windowWidth 1280

inline std::bitset<8> bitifier(uint8_t inp){
return inp; 
}

int main(){
  std::array<std::array<bool, 64>, 32>  screen; //[height][width]
  std::array<uint8_t, 256> vidRAM;

  for (int i = 0; i < 256; i++){
    vidRAM.at(i) = rand() % 255;
  }

  InitWindow(windowWidth, windowHeight, "EmulatOwOr");
  if(!IsWindowReady()){
    std::cerr << "something fucked up dude, window is glitched apparently\n";
  }
  SetExitKey(KEY_END);
  SetWindowIcon(LoadImage("/home/peter/Documents/CPUwUproject/emulatOwOr/resources/appICON2.png"));

  for(int i = 0; i < 32; i++){
    for (int j = 0; j < 8; j++){
      for (int k = 0; k < 8; k++){
        screen.at(i).at((j * 8) + k) = bitifier(vidRAM.at(i * 8 + j))[7-k];
      }
    }
  }

  BeginDrawing();

  for (int i = 0; i < 32; ++i){
    for (int j = 0; j < 64; ++j){
      if(screen.at(i).at(j)){
        DrawRectangle(j*20, i*20, 20, 20, WHITE);
      }
      else{
        DrawRectangle(j*20, i*20, 20, 20, BLACK);
      }
    }
  }

  EndDrawing();

  CloseWindow();
  return 0;
}