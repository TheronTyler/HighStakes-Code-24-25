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
motor_group(arm1, arm2).setVelocity(50,pct);

//Stopping
motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setStopping(brake);
intake.setStopping(coast);
motor_group(arm1, arm2).setStopping(hold);

//Optical
color_sort.setLightPower(100, pct);

//PID
sense.calibrate();
sense.setHeading(1, degrees);
}

void autonomous(void) {
motor_group(arm1, arm2).setStopping(hold);

//Pre-Load on alliance stake
drive(110); //10" 
wait(150, msec);
intake.spinTo(1800, degrees, false);
turn(259.5);
drive(60); //3"
motor_group(arm1, arm2).spinFor(-.75, rev, false);
drive(-60.85); //6"
motor_group(arm1, arm2).spinFor(.5, rev, false);
wait(150,msec);

//goal grab
turn(148);
drive(-260);
moGo.set(true);

//4 grid
turn(90);
wait(100, msec);
drive(-40);
turn(120);
thread this_thread(colorSort);
drive(70);
turn(165);
drive(55);

//single stack
drive(-50);
turn(115);
drive(90);
/*
//Pre-Load on alliance stake
drive(110); //10" 
wait(150, msec);
intake.spinTo(1800, degrees, false);
turn(260);
drive(60); //3"
motor_group(arm1, arm2).spinFor(-.75, rev, false);
drive(-60.85); //6"
motor_group(arm1, arm2).spinFor(.5, rev, false);
wait(150,msec);

//Grab mobile stake
turn(155);
drive(-285.31); //41.94"
moGo.set(true);
wait(260, msec);

//Pickup 4 stack of rings
turn(265);
thread this_thread(colorSort); //Starts the color sorting intake
wait(25,msec);
turn(245);
wait(50, msec);
drive(95);
wait(450,msec);
drive(-20);
turn(167);
drive(80);

//grab single stack 
drive(-70);
turn(132);
drive(80);

//go towards pos corner
turn(120);
drive(196);
turn(140);
drive(125);
wait(300, msec);
drive(50);
turn(90);
drive(50);
threadRunning = (false);
*/
} 

void usercontrol(void) {
while (1) {
  motor_group(arm1, arm2).setStopping(hold);
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
    motor_group(arm1, arm2).spin(fwd);
  }
  else if (Controller.ButtonR2.pressing()) {
    motor_group(arm1, arm2).spin(reverse);
  }
  else {
    motor_group(arm1, arm2).stop();
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