/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Theron Tyler                                              */
/*    Created:      9/20/2024, 8:15:00 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "setup.h"
//#include "turnHeading.h"

using namespace vex;

// A global instance of competition
void pre_auton(void) {

//Speed
intake.setVelocity(95,pct);

//Stopping
motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setStopping(brake);
intake.setStopping(coast);
}

void load(){
  intake.spin(fwd);
  ai.takeSnapshot(aivision::ALL_COLORS);
  if(ai.objectCount){
    bPack.stop();
    }
  else{
    bPack.spinTo(5, deg);
  }
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
    intake.setVelocity(100,pct);
    intake.spinFor(fwd, revolutions, rev, false);
    wait(delay, sec);
    intake.stop();
    break;
  }
}
/* ---- Possible New Auton Functions
void drive(float revolutions, float speed){
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setVelocity(speed, pct);
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spinFor(fwd, revolutions, rev);
}

void turnLeft(float revolutions, float speed){
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setVelocity(speed, pct);
  motor_group(fLDrive, bLDrive, mLDrive ).spinFor(reverse, revolutions, rev, false);
  motor_group(fRDrive, bRDrive, mLDrive).spinFor(fwd, revolutions, rev, false);
}

void turnRight(float revolutions, float speed){
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setVelocity(soeed, pct);
  motor_group(fLDrive, bLDrive, mLDrive ).spinFor(fwd, revolutions, rev, false);
  motor_group(fRDrive, bRDrive, mLDrive).spinFor(reverse, revolutions, rev, false);
}
*/

void autonomous(void) {
mind('w',.4,-.5); //goal
moGo.set(true);
intake.spinFor(fwd, 60, rev, false); //first ring
wait(.5, sec);
mind('a',1,0.87); 
mind('w',1,.7); //second ring
wait(.5, sec);
mind('a',1,-0.38);
mind('w',1,.8); //third ring
wait(.3, sec);
mind('a',1,-0.4);
mind('S',3,0.65); //fourth ring
wait(.3, sec);
mind('S',3,0.65); //fifth ring
mind('w',1,-0.4); 
mind('a',1,0.5);
mind('w',1,0.4); //sixth ring
wait(.3, sec);
mind('w',1,-0.4);
mind('a',1,0.5);
mind('w',1,-0.7);
moGo.set(false); //goal in corner
mind('w',1,0.4);
mind('a',1,0.9);
mind('w',1,-3);


}
void usercontrol(void) {
while (1) {
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

  //Arm
  if (Controller.ButtonR1.pressing()) {
    bPack.spin(fwd);
  }
  else if (Controller.ButtonR2.pressing()) {
    bPack.spin(reverse);
  }
  else {
    bPack.stop();
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