#include "vex.h"
#include "robot-config.h"
#include "PID.h"

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

void RED_NEG_SAWP(){
  turn(90);
  /*
  intake.setVelocity(100, pct);
  drive(-350); //Rush goal
  wait(20, msec);
  moGo.set(true);

  intake.spinFor(fwd,60,rev,false); //Score preload
  wait(700, msec);

  turn(100); //First stack
  drive(8.58);
  drive(4.04);

  wait(1000, msec);
  drive(10.10);
  */
    /*
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
    */
}

void RED_POS_SAFE(){

}

void RED_POS_RUSH(){

}

void RED_NEG_ELIMS(){

}

void BLUE_NEG_SAWP(){
    arm.setStopping(coast);
    mind('w',.75,-1.55); //Rush goal
    wait(25, msec);
    moGo.set(true);

    mind('i',1,2.5); //score preload

    mind('a',.7,-.2); //first stack
    intake.spinFor(fwd,40,rev,false);
    mind('w',.5,.85);
    mind('s',.25,.4);

    wait(1, sec);
    mind('S',.25,1);
    mind('a',1.5,-.5);//second stack
    mind('s',.4,.9);

    mind('a',.25,.3);
    mind('s',.2,.25);

    mind('s',1.5,-2);//retreat to ladder
}

void BLUE_POS_SAFE(){

}

void BLUE_POS_RUSH(){

}

void BLUE_NEG_ELIMS(){

}

void Skills(){
  drive(-121.21); //Grab Goal
  moGo.set(true);

  intake.spinFor(fwd, 60, rev, false); //Score Preload

  turn(270); //Fill Goal
  drive(323.23);
  drive(-121.21);
  turn(90);
  drive(121.21);
  wait(30,msec);
  drive(-121.21);
  turn(0);
  drive(242.42);

  /*
  mind('w',.4,-.5); //goal
  moGo.set(true);

  intake.spinFor(fwd, 60, rev, false); //first ring
  wait(.5, sec);
  mind('a',1,0.87); 

  mind('w',1,.7); //second ring
  wait(.5, sec);
  mind('a',1,-0.34);

  mind('w',1,.8); //third ring
  wait(.3, sec);
  mind('a',1,-0.4);

  mind('S',3,0.65); //fourth ring
  wait(.3, sec);

  mind('S',3,0.65); //fifth ring
  mind('w',1,-0.4); 
  mind('a',1,0.42);

  mind('w',1,0.4); //sixth ring
  wait(.3, sec);
  mind('w',1,-0.4);
  mind('a',1,0.5);
  mind('w',1,-0.7);

  moGo.set(false); //goal in corner
  mind('w',1,0.4);
  mind('a',1,0.9);
  mind('w',1,-3);
  */
}