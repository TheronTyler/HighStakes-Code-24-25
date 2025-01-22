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
//#include "turnHeading.h"

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
arm.setStopping(hold);

//Doinker Alliance ring stack
doinker.set(true);

turn(90);
doinker.set(false);
wait(75,msec);
turn(273);
wait(75,msec);

//Pre-Load on alliance stake
drive(120); //10" 
wait(250, msec);
turn(265);
drive(50); //3"
arm.spinFor(-.75, rev, false);
wait(3, msec);
drive(-60.85); //6"
arm.spinFor(.25, rev);

//Grab mobile stake
turn(145);
drive(-250.31); //41.94"
wait(350, msec);
moGo.set(true);
wait(350, msec);

//Pick-up Doinked Ring
turn(230);
vex::thread this_thread(colorSort); //Starts the color sorting intake
drive(100);
wait(1000, msec);

//Pick-up Solo Stack
turn(250);
drive(125); //24"

//intake 2 red from 4-grid
turn(270);
drive(100);
wait(50, msec);
drive(-10.14); //1"
turn(210);
drive(10.14); //1"
wait(50, msec);
drive(-10.14); //1"
turn(165);

//Sweep and intake corner rings
drive(-608.45);
turn(90);

  /*
  mind('w',.3,1);
  mind('a',.35,-1);
  mind('s',.55,.5); //Score alliance stake
  mind('s',.13,-.07);
  arm.spinFor(reverse, .75, sec);
  
  mind('w',.5,-0.15); //grab goal
  mind('a',.3,.065);
  mind('w',.95,-1.4);
  moGo.set(true);

  mind('w',.25,.5); //Grab ring
  mind('a',.4,-.55);
  wait(100,msec);
  intake.spinFor(fwd, 10, rev, false);
  mind('w',.55,.85);
  wait(100,msec);
  mind('a',.4,.475);
  wait(100,msec);
  doinker.set(true);
  mind('w',.7,1);
  mind('a',.2,.6);
  */
} 

void usercontrol(void) {
while (1) {
  arm.setStopping(hold);
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