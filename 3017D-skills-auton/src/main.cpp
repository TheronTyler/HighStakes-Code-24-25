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
turn(90);
wait(10, msec);
drive(-140);
moGo.set(true);
wait(30, msec);

//First Corner
//First Ring
turn(90); 
intake.spin(fwd);
drive(160);

//Second Ring
turn(115);
drive(180);

//third/fourth ring
turn(103);
drive(140);
wait(550, msec);
drive(135);
wait(150,msec);
drive(10);

//5th ring
drive(-177);
turn(210);
drive(90);

//Goal in Corner
turn(250);
wait(100,msec);
turn(223);
drive(-75);
moGo.set(false);
intake.stop();

//Second Corner
//Wall Reset
drive(80);
turn(75);
wait(250, msec);
drive(-260);
turn(245);

motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spinFor(reverse, 500, rev, false);
wait(1, sec);
motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).stop();

wait(150,msec);
drive(125);

//Grab Goal
turn(103);
drive(-240);
wait(400, msec);
drive(-60);
moGo.set(true);
wait(250, msec);

//First Ring
turn(240);
intake.spin(fwd);
drive(150);

//Second Ring
turn(240);
drive(200);

//third/fourth ring
turn(250);
drive(140);
wait(500, msec);
drive(130);

//Fith Ring
drive(-150);
turn(155);
drive(90);

//Goal in Corner
turn(120);
wait(100,msec);
turn(100);
drive(-90);
moGo.set(false);
intake.stop();

//Load Wall Stake Mech
arm.spinFor(fwd, .5, rev, false);

drive(260);
turn(110);

motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spinFor(reverse, 500, rev, false);
wait(1, sec);
motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).stop();

wait(100,msec);
drive(62);
turn(260);

intake.spin(fwd);
drive(120);
wait(400,msec);
intake.stop();
arm.spinFor(reverse, .4, rev, false);

//Third Goal
turn(130);
intake.spin(fwd);
drive(200);
wait(50,msec);
drive(100);
intake.stop();
turn(90);
wait(150,msec);
turn(90);
drive(-160);
moGo.set(true);

}

void usercontrol(void) {
while (1) {
  arm.setStopping(hold);
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