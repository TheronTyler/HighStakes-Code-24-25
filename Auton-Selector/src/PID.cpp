#include "robot-config.h"
#include "vex.h"

void turn(float turnTarget){
  float turnKp = 3; //needs tuned
  float turnKi = 0.1; //needs tuned
  float turnKd = 3; //needs tuned
  float turnError = turnTarget - sense.heading();
  float previousTurnError = turnError;
  float turnP = turnKp * turnError;
  float turnI = turnI + (LOOPTIME * turnError * turnKi);
  float turnD = turnKd * (turnError - previousTurnError)/LOOPTIME;

  while(fabs(turnError)>1){
    motor_group(fLDrive, bLDrive, mLDrive).spin(fwd, 35 + (turnP + turnI + turnD), pct);
    motor_group(fRDrive, bRDrive, mRDrive).spin(fwd, 35 - (turnP + turnI + turnD), pct);
  }
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).stop();
}

void drive(float driveTarget){
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setPosition(0, deg);

  float driveKp = 3; //needs tuned
  float driveKi = 0.1; //needs tuned
  float driveKd = 3; //needs tuned
  float driveError = driveTarget - (fLDrive.position(deg) + bLDrive.position(deg) + mLDrive.position(deg) + 
  fRDrive.position(deg) + bRDrive.position(deg) + mRDrive.position(deg)) / 6; //our drive targey minus the avg position of the motors
  float previousDriveError = driveError;
  float driveP = driveKp * driveError;
  float driveI = driveI + (LOOPTIME * driveError * driveKi);
  float driveD = driveKd * (driveError - previousDriveError)/LOOPTIME;

  while(fabs(driveError)>1){
    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spin(fwd, 60 + (driveP + driveI + driveD), pct);
  }
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).stop();
}