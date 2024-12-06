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
//#include "turnHeading.h"

using namespace vex;

// A global instance of competition
void pre_auton(void) {

//Speed
intake.setVelocity(95,pct);
arm.setVelocity(90,pct);

//Stopping
motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setStopping(brake);
intake.setStopping(coast);
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
  wallStake.set(true); //Prep Robot
  wait(200, msec);
  mind('i', 1, -1); //outake ring to redirect
  wait(0.000000000000000000001, msec);
  arm.spinFor(2, rev);  //spin arm up
  mind('w', 1.5, 0.17);  //drive forward to stake
  arm.spinFor(-2, rev);  //spin redirect down
  //wait(0.005, msec);
  mind('w', 1.5, -0.75);
  wait(5, msec);
  arm.spinFor(-0.75, rev);
  wallStake.set(false);
  wait(0.000000000000000000001, msec);
  moGo.set(true);

  /*arm.spinFor(40, deg); //Score on Allience
  turn(90);
  drive(33);
  arm.spinFor(-40, deg);
  drive(-33);

  turn(155); //Grab Mobile Goal
  drive(294.08);
  moGo.set(true);

  turn(225); //Ring 1
  intake.spinFor(fwd, 10, sec);
  drive(182.53);

  turn(230); //Ring 2
  drive(121.69);
  drive(-30.42);

  turn(165); //RIng 3
  drive(81.12);

  drive(-517.18); //Touch ladder
  turn(240);
  drive(152.11);*/
  







 /*arm.setStopping(coast);
    mind('w',.75,-1.55); //Rush goal
    wait(25, msec);
    moGo.set(true);

    mind('i',1,2.5); //score preload

    mind('a',.7,.2); //first stack
    intake.spinFor(fwd,40,rev,false);
    mind('w',.5,.85);
    mind('s',.25,.4);

    wait(1, sec);
    mind('S',.25,1);
    mind('a',1.5,.5);//second stack
    mind('s',.4,.9);

    mind('a',.25,-.3);
    mind('s',.2,.25);

    mind('s',1.5,-2);//retreat to ladder
/*  intake.spinFor(115, degrees); //on top of power button, works to score preload on alliance stake. could utilize in starting skills
  drive(180); //Grab Goal
  wait(250,msec);
  turn(265);
  wait(300,msec);
  drive(-265);
  //wait(100,msec);
  moGo.set(true);
  wait(100,msec);

  turn(115); //Turn to 1st ring
  intake.spinFor(fwd, 80, rev, false);//Spin intake for the rest of run
  wait(200,msec);
  drive(223); //Pickup 1st ring
  wait(250,msec);

  turn(100); //Turn to 2nd ring
  wait(500,msec);
  drive(223); //Pickup 2nd ring
  wait(250,msec);

  turn(240); //Pickup 3rd ring; in front of neutral stake
  wait(250,msec);
  drive(223); //Pickup 3rd ring
  wait(500,msec);
  drive(-233); //Backup to previous spot
  wait(250,msec);

  turn(40);//turn to 4th and 5th ring
  wait(250,msec);
  drive(223); //Pickup 4th ring
  wait(1500,msec);
  drive(130); //Pickup 5th ring
  drive(-135);

  turn(220); //Turn to 6th ring
  drive(130); //Pickup 6th ring
*/
  /*wait(250,msec);
  turn(90);
  wait(250,msec);
  drive(223);
  wait(500,msec);
  drive(112);*/
  //drive();

 /* intake.spinFor(fwd, 60, rev, false); //Score Preload
  wait(500, msec);

  turn(280); //Fill Goal
  wait(250,msec);

  drive(200);
  wait(350,msec);
  drive(150);
  wait(100,msec);

  drive(-121.21);
  wait(250,msec);

  turn(90);
  wait(250,msec);

  drive(130);
  wait(250,msec);

  drive(-121.21);
  wait(250,msec);
 
  turn(5);
  wait(250,msec);

  drive(242.42);
  wait(250,msec);*/
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