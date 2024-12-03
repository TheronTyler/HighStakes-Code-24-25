/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Theron Tyler                                              */
/*    Created:      9/20/2024, 8:15:00 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "robot-config.h"
#include "autons.h"
#include "PID.h"

using namespace vex;
using namespace std;


int current_auton_selection = 0;
bool auto_started = false;

// A global instance of competition
void pre_auton(void) {
  
  while(!auto_started){

    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5, 20, "Team 3017D: Diffusion");
    Brain.Screen.printAt(5, 40, "Battery Percentage:");
    Brain.Screen.printAt(5, 60, "%d", Brain.Battery.capacity());
    Brain.Screen.printAt(5, 120, "Selected Auton:");
    switch(current_auton_selection){
      case 0:
        Brain.Screen.drawImageFromFile("RED_NEG_SAWP.png", 300, 140);
        break;
      case 1:
        Brain.Screen.drawImageFromFile("RED_POS_SAFE.png", 300, 140);
        break;
      case 2:
        Brain.Screen.drawImageFromFile("RED_POS_RUSH.png", 300, 140);
        break;
      case 3:
        Brain.Screen.drawImageFromFile("RED_NEG_ELIMS.png", 300, 140);
        break;
      case 4:
        Brain.Screen.drawImageFromFile("BLUE_NEG_SAWP.png", 300, 140);
        break;
      case 5:
        Brain.Screen.drawImageFromFile("BLUE_POS_SAFE.png", 300, 140);
        break;
      case 6:
        Brain.Screen.drawImageFromFile("BLUE_POS_RUSH.png", 300, 140);
        break;
      case 7:
        Brain.Screen.drawImageFromFile("BLUE_NEG_ELIMS.png", 300, 140);
        break;
      case 8:
        Brain.Screen.drawImageFromFile("Skills.png", 300, 140);
        break;
        wait(500,msec);
    }
    if(Brain.Screen.pressing()){
      while(Brain.Screen.pressing()) {}
      current_auton_selection ++;
    } else if (current_auton_selection == 5){
      current_auton_selection = 0;
    }
    task::sleep(10);
  }

}

void autonomous(void) {
auto_started = true;
  switch(current_auton_selection){ 
    case 0:
      RED_NEG_SAWP();
      break;
    case 1:         
      RED_POS_SAFE();
      break;
    case 2:
      RED_POS_RUSH();
      break;
    case 3:
      RED_NEG_ELIMS();
      break;
    case 4:
      BLUE_NEG_SAWP();
      break;
    case 5:
      BLUE_POS_SAFE();
      break;
    case 6:
      BLUE_POS_RUSH();
      break;
    case 7:
      BLUE_NEG_ELIMS();
      break;
    case 8:
      Skills();
      break;
 }
}

void usercontrol(void) {
while (1) {
  arm.setStopping(hold);
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setStopping(brake);
  //Drive
  int rotational = Controller.Axis3.position(pct);
  int lateral = Controller.Axis1.position(pct);

  motor_group(fLDrive, bLDrive, mLDrive).spin(fwd,lateral + rotational,pct);
  motor_group(fRDrive, bRDrive, mRDrive).spin(reverse,lateral - rotational,pct);
  
  //Intake
  if (Controller.ButtonL1.pressing()) {
    intake.spin(fwd, 80, pct);
  }
  else if (Controller.ButtonL2.pressing()) {
    intake.spin(reverse, 80, pct);
  }
  else {
    intake.stop();
  }

  //Moble Goal
  if (Controller.ButtonB.pressing()) {
    moGo.set(true);
  }
  else if (Controller.ButtonDown.pressing()) {
    moGo.set(false);
  }

  //Doinker
  if (Controller.ButtonLeft.pressing()) {
    doinker.set(true);
  }
  else if (Controller.ButtonUp.pressing()) {
    doinker.set(false);
  }

  //Wall Stake Expansion
  if (Controller.ButtonX.pressing()){
    wallStake.set(true);
  }
  else if (Controller.ButtonA.pressing()){
    wallStake.set(false);
  }
  
  //Arm
  if (Controller.ButtonR1.pressing()) {
    arm.spin(fwd);
  }
  else if (Controller.ButtonR2.pressing()) {
    arm.spin(reverse);
  }
  else {
    arm.stop();
  }
  wait(30, msec);

}

}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}