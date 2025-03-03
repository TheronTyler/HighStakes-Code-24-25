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
#include "wallReset.h"


//#include "turnHeading.h"

using namespace vex;

// A global instance of competition
void pre_auton(void) {

//Speed
intake.setVelocity(95,pct);
arm1.setVelocity(50,pct);
arm2.setVelocity(50,pct);

//Stopping
motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setStopping(brake);
intake.setStopping(coast);
arm1.setStopping(hold);
arm2.setStopping(hold);

//Optical
color_sort.setLightPower(100, pct);

//PID
sense.calibrate();
sense.setHeading(1, degrees);
}

void autonomous(void) {
arm1.setStopping(hold);
arm2.setStopping(hold);
//double temp = bLDrive.temperature(temperatureUnits ::fahrenheit);
//Controller.Screen.clearScreen();
//Controller.Screen.print(temp);
wall(0);

/*
//Pre-Load on alliance stake
drive(103); //10" 
wait(150, msec);
intake.spinTo(1800, degrees, false);
turn(259.5);
drive(60); //3"
motor_group(arm1, arm2).spinFor(-.75, rev, false);
wait(100,msec);
drive(-60.85); //6"
motor_group(arm1, arm2).spinFor(.75, rev, false);
wait(150,msec);

//goal grab
turn(149);
drive(-260);
moGo.set(true);

//single stack
turn(210);
turn(250);
intake.spinFor(5, rev, false);
drive(120);
wait(300, msec);

//knocked over stack
turn(85);
moGo.set(false);
drive(155);
wait(450, msec);
turn(142);
thread this_thread(loadIntake);
drive(170);
drive(175);

//2nd moGo grab
wait(750, msec);
turn(264);
drive(-130);
moGo.set(true);
wait(200, msec);
load = false;

//other single stack
turn(108);
intake.spinFor(fwd, 2000, rev, false);
drive(150);

//touch ladder
turn(95);
turn(95);
motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setStopping(coast);
motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spinFor(fwd, 1, sec);
*/

} 

void usercontrol(void) {
while (1) {
  threadRunning = false;
  load = false;
  arm1.setStopping(hold);
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setStopping(brake);
  arm2.setStopping(hold);
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