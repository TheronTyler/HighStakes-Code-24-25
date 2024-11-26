#include "robot-config.h"
#include "vex.h"

void turn(float turnTarget){
  sense.setHeading(180, deg);
  float turnKp = .25; //needs tuned
  float turnKi = .25; //needs tuned
  float turnKd = .35; //needs tuned
  float turnError = turnTarget - sense.heading();
  
  while(fabs(turnError) > 3){
  turnError = turnTarget - sense.heading();
  float previousTurnError = turnError;
  float turnP = turnKp * turnError;
  float turnI = turnI + (.02 * turnError * turnKi);
  float turnD = turnKd * (turnError - previousTurnError)/1;

    motor_group(fLDrive, bLDrive, mLDrive).spin(fwd,  (turnP  + turnI + turnD), pct);
    motor_group(fRDrive, bRDrive, mRDrive).spin(fwd,  -1*(turnP  + turnI + turnD), pct);
    wait (20, msec);
  }
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setStopping(brake);
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spin(fwd, 0, pct);
}

void drive(float driveTarget){ //480 deg = ---"
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setPosition(0, deg);

  float driveKp = 40; //needs tuned
  float driveKi = 10; //needs tuned
  float driveKd = 9; //needs tuned
  float driveError = driveTarget - (fLDrive.position(deg)); //our drive targey minus the avg position of the motors
  
  while (fabs(driveError) > 3){
  driveError = driveTarget - (fLDrive.position(deg));
  float previousDriveError = driveError;
  float driveP = driveKp * driveError;
  float driveI = driveI + (.02 * driveError * driveKi);
  float driveD = driveKd * (driveError - previousDriveError)/1;

    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spin(fwd, (driveP + driveI + driveD)*0.125, pct);
    wait (20, msec);
  }
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setStopping(brake);
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spin(fwd, 0, pct);
}