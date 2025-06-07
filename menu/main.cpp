#include <iostream>
#include "raylib.h"

// asserting dominance
#undef windowHeight
#define windowHeight 450
#undef windowWidth
#define windowWidth 800

// i have asserted enough dominance now
#ifndef clockSpeed
  #define clockSpeed 1 //operations per second
#endif

typedef enum tabScreen {SETUP = 0, CONTROL, CODE, RAM, SCREEN} tabScreen; 
//screensizes: 2048p : 45x45, 32x64you
//             1024p : 32x32
//              512p : 22x22
//              256p : 16x16

void inline drawIcon(const std::string& icon, const unsigned int x, const unsigned int y){
  if (icon == "bars"){  // 22x26
    DrawRectangle(x, y, 8, 26, LIGHTGRAY);
    DrawRectangle(x + 14, y, 8, 26, LIGHTGRAY);
  }
  else if (icon == "triangle"){ // 26x20
    DrawTriangle({(float)(x), (float)(y)}, 
                 {(float)(x), (float)(26+y)}, 
                 {(float)(20+x), (float)(13+y)}, 
                  LIGHTGRAY);
  }
  else if (icon == "stepright"){ // 23x26
    DrawTriangle({(float)(x), (float)(y)}, 
                 {(float)(x), (float)(26+y)}, 
                 {(float)(18+x), (float)(13+y)}, 
                 LIGHTGRAY);
    DrawRectangle(x + 18, y + 1, 5, 24, LIGHTGRAY);
  }
  else if (icon == "stepleft"){ // 23x26
    DrawRectangle(x, y+1, 5, 24, LIGHTGRAY);
    DrawTriangle({(float)(23+x), (float)(y)}, 
                 {(float)(5+x), (float)(13+y)}, 
                 {(float)(23+x), (float)(26+y)}, 
                 LIGHTGRAY);
  }
  else {
    std::cerr << "\nWHOOP WHOOP\n";
  }
  return;
}

void inline drawToolbar(unsigned short int h = 50){
  unsigned short int sW = GetScreenWidth();
  unsigned short int sH = GetScreenHeight();

  DrawRectangle(0, sH - h, sW, h, DARKGRAY);
  drawIcon("bars", (sW/2) - 11, sH - 38);
  drawIcon("stepleft", (sW/2) - 52, sH - 38);
  drawIcon("stepright", (sW/2) + 29, sH - 38);

  //DrawRectangle((sW/2)- 20, sH - h, 40, h, {60, 60, 60, 255});
  return;
}

int main(){
  tabScreen currentTab = SETUP;
  InitWindow(windowWidth, windowHeight, "EmulatOwOr");

  while (!WindowShouldClose()){
    switch(currentTab){
      case SETUP:
        //did window initialize correctly
        if(!IsWindowReady()){
          std::cerr << "something fucked up dude, window is glitched apparently\n";
        }
        //window can only close with the little cross
        SetExitKey(KEY_END);

        //window icon
        SetWindowIcon(LoadImage("/home/peter/Documents/CPUwUproject/emulatOwOr/resources/appICON2.png"));
        
        BeginDrawing();
          ClearBackground(LIGHTGRAY);
          drawToolbar();
        EndDrawing();

        currentTab = CONTROL;
      break;
      case CONTROL:
        
      break;
      case CODE:
      break;
      case RAM:
      break;

      default:
      break;
    }
  }
  CloseWindow();
  return 0;
}