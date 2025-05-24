#include <iostream>
#include "raylib.h"

// asserting dominance
#undef windowHeight
#define windowHeight 400
#undef windowWidth
#define windowWidth 800

// i have asserted enough dominance now
#ifndef clockSpeed
  #define clockSpeed 1 //operations per second
#endif

typedef enum tabScreen {SETUP = 0, CONTROL, CODE, RAM} tabScreen;

int main(){

  tabScreen currentTab = SETUP;
  InitWindow(windowWidth, windowHeight, "EmulatOwOr");
  //did window initialize correctly

  if(!IsWindowReady()){
    std::cerr << "something fucked up dude, window is glitched apparently\n";
  }

  //window can only close with the little cross
  SetExitKey(KEY_SPACE);

  //window icon
  SetWindowIcon(LoadImage("/home/peter/Documents/CPUwUproject/emulatOwOr/resources/appICON2.png"));

  while (!WindowShouldClose())
  {
    switch(currentTab)
    {
      case SETUP:
      break;
      default:
      break;
    }
  }
  CloseWindow();
  return 0;
}