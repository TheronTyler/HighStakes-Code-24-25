/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Theron Tyler                                              */
/*    Created:      9/20/2024, 8:15:00 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "robot-config.h"
#include "PID.h"
#include "colorSort.h"
#include "wallLoad.h"

using namespace vex;

// A global instance of competition
void pre_auton(void) {

//Speed
intake.setVelocity(95,pct);
arm.setVelocity(50,pct);

//Stopping
motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setStopping(brake);
intake.setStopping(coast);
arm.setStopping(hold);

//Optical
color_sort.setLightPower(100, pct);

//PID
sense.calibrate();
sense.setHeading(1, degrees);
}

void autonomous(void) {
arm.setStopping(hold);

//Doinker Alliance ring stack
doinker.set(true);
turn(90);
doinker.set(false);
wait(75,msec);
turn(268);
wait(75,msec);

//Pre-Load on alliance stake
drive(110); //10" 
wait(150, msec);
turn(270);
drive(60); //3"
arm.spinFor(-.75, rev, false);
drive(-60.85); //6"
arm.spinFor(.75, rev, false);

//Grab mobile stake
turn(146.5);
drive(-250.31); //41.94"
moGo.set(true);
wait(260, msec);

//Pick-up Doinked Ring
turn(220);
thread this_thread(colorSort); //Starts the color sorting intake
drive(125);
wait(200, msec);

//Pickup 4 stack of rings
turn(260);
wait(25,msec);
turn(245);
drive(225);
wait(100,msec);
turn(155);
drive(50);

//Touch Ladder
drive(-150);
turn(240);

motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setVelocity(100,pct);
motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spinFor(fwd, .5, rev);

//
threadRunning = false;
} 

void usercontrol(void) {
while (1) {
  arm.setStopping(hold);
  //Drive
  int rotational = Controller.Axis3.position(pct);
  int lateral = Controller.Axis1.position(pct);

  motor_group(fLDrive, bLDrive, mLDrive).spin(fwd,(lateral)*.5 + rotational,pct);
  motor_group(fRDrive, bRDrive, mRDrive).spin(reverse,(lateral)*.5 - rotational,pct);
  
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