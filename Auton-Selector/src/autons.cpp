#include "vex.h"
#include "robot-config.h"

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

void Neg_Red(){
arm.setStopping(coast);
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
}

void Pos_Red(){

}

void Neg_Blue(){

}

void Pos_Blue(){

}

void Skills(){

}