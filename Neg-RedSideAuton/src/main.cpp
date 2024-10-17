/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Theron Tyler                                              */
/*    Created:      6/20/2024, 9:46:38 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

#include "turnHeading.h"

using namespace vex;

// A global instance of competition

void pre_auton(void) {
//Speed
lIntake.setVelocity(95,pct);
uIntake.setVelocity(95,pct);

//Stopping
motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setStopping(brake);
motor_group(lIntake, uIntake).setStopping(coast);
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
    motor_group(fRDrive, bRDrive, mLDrive).spinFor(reverse, revolutions, rev, false);
    wait(delay, sec);
    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).stop();
    break;
  case 'i': //intake
    motor_group(lIntake, uIntake).setVelocity(100,pct);
    motor_group(lIntake, uIntake).spinFor(fwd, revolutions, rev, false);
    wait(delay, sec);
    motor_group(lIntake, uIntake).stop();
    break;
  }
}

void autonomous(void) {
mind('w',.75,-1.3); //Rush goal
moGo.set(true);

mind('i',1,2.5); //score preload

mind('a',.5,1); //first stack
motor_group(lIntake,uIntake).spinFor(fwd,40,rev,false);
mind('s',2.5,1.2);

mind('a',1,2);//second stack
mind('s',.5,.5);

mind('a',.25,-.3);
mind('S',.2,.2);

mind('s',1.5,-3.3);//retreat to ladder
}

void usercontrol(void) {
while (1) {
  //Drive
  int lateral = Controller.Axis2.position(pct);
  int rotational = Controller.Axis1.position(pct);

  motor_group(fLDrive, bLDrive, mLDrive).spin(fwd,lateral + rotational,pct);
  motor_group(fRDrive, bRDrive, mRDrive).spin(reverse,lateral - rotational,pct);
  
  //Intake
  if (Controller.ButtonL1.pressing()) {
    motor_group(lIntake, uIntake).spin(fwd, 80, pct);
  }
  else if (Controller.ButtonL2.pressing()) {
    motor_group(lIntake, uIntake).spin(reverse, 80, pct);
  }
  else {
    motor_group(lIntake, uIntake).stop();
  }

  //Moble Goal
  if (Controller.ButtonB.pressing()) {
    moGo.set(true);
  }
  else if (Controller.ButtonDown.pressing()) {
    moGo.set(false);
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