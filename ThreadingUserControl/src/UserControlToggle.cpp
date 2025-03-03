#include "robot-config.h"
#include "vex.h"

//Moble Goal
void mobileGoal() {
    
bool mogoState = false;
bool mogoPressed = false;

if (Controller.ButtonB.pressing()) {
    if (!mogoPressed) {
        mogoState = !mogoState;
        mogoPressed = true;
    }
  }
  else {
        mogoPressed = false;
  }
  if (mogoState) {
    moGo.set(true);
  }
}