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
#include "wallreset.h"

using namespace vex;
using namespace std;

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
sense.setHeading(1, degrees);

}

void mind(char cmd,float delay,float revolutions) {
  switch (cmd) {
  case 'w': //forward motion
    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setVelocity(60, pct);
    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spinFor(fwd, revolutions, rev, false);
    wait(delay, sec);
    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).stop();
    break;
  case 's': //slow forward motion
    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setVelocity(35, pct);
    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spinFor(fwd, revolutions, rev, false);
    wait(delay, sec);
    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).stop();
    break;
  case 'S': //super slow forward motion
    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setVelocity(15, pct);
    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spinFor(fwd, revolutions, rev, false);
    wait(delay, sec);
    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).stop();
    break;
  case 'a': //clockwise turn
    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setVelocity(70, pct);
    motor_group(fLDrive, bLDrive, mLDrive ).spinFor(fwd, revolutions, rev, false);
    motor_group(fRDrive, bRDrive, mRDrive).spinFor(reverse, revolutions, rev, false);
    wait(delay, sec);
    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).stop();
    break;
  case 'i': //intake
    intake.setVelocity(75,pct);
    intake.spinFor(fwd, revolutions, rev, false);
    wait(delay, sec);
    intake.stop();
    break;
  }
}

void autonomous(void) {
arm1.setStopping(hold);
arm2.setStopping(hold);

//Score on alliance stake
motor_group(arm1, arm2).spinFor(reverse, .5, sec);
wait(1, msec);
drive(-85);
motor_group(arm1, arm2).spinFor(fwd, .5, sec);

//Grab First Goal
turn(92);
wait(10, msec);
drive(-180);
moGo.set(true);
wait(30, msec);

//first ring
turn(86);
wall(0);
intake.spinFor(fwd, 100, rev, false);
drive(170);

//second ring
turn(103);
wait(75,msec);
drive(170);

//3-4 ring
turn(110);
drive(130);
drive(130);

//5 ring
drive(-130);
turn(215);
drive(70);

//goal in corner
turn(270);
turn(240);
drive(-75);
moGo.set(false);

//first wall reset
drive(60);
turn(240);
drive(350);
turn(90);
wall(0);
}

void usercontrol(void) {
while (1) {
  arm1.setStopping(hold);
  arm2.setStopping(hold);
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setStopping(brake);
  //Drive
  int rotational = Controller.Axis3.position(pct);
  int lateral = Controller.Axis1.position(pct);

  motor_group(fLDrive, bLDrive, mLDrive).spin(fwd,(lateral*0.5) + rotational,pct);
  motor_group(fRDrive, bRDrive, mRDrive).spin(reverse,(lateral*0.5) - rotational,pct);
  
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