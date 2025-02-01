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
using namespace std;

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
sense1.calibrate();
sense1.setHeading(1, degrees);
sense2.setHeading(1, degrees);

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

//Score on alliance stake
arm.spinFor(reverse, .5, sec);
wait(1, msec);
drive(-85);
arm.spinFor(fwd, .5, sec);

//Grab First Goal
turn(95);
wait(10, msec);
drive(-140);
moGo.set(true);
wait(30, msec);

//First Corner
//First Ring
turn(100); 
thread colorThread(colorSort);
drive(160);

//Second Ring
turn(115);
drive(180);

//third/fourth ring
turn(155);
drive(140);
wait(500, msec);
drive(122);

//5th ring
drive(-177);
turn(220);
drive(75);

//Goal in Corner
turn(275);
turn(25);
drive(-131.83);
moGo.set(false);

//Second Corner
//Grab Goal
drive(80);
turn(77);
wait(500, msec);
drive(-225);
drive(-260);
wait(400, msec);
drive(-100);
moGo.set(true);
wait(250, msec);

//First Ring
turn(272.5);
drive(150);

//Second Ring
turn(250);
drive(110);

//third/fourth ring
turn(250);
drive(140);
wait(500, msec);
drive(122);


}

void usercontrol(void) {
while (1) {
  arm.setStopping(hold);
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