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

void drive(float driveTarget){
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setPosition(0, deg);

  float driveKp = .3; //needs tuned
  float driveKi = .3; //needs tuned
  float driveKd = .3; //needs tuned
  float driveError = driveTarget - (fLDrive.position(deg) + bLDrive.position(deg) + mLDrive.position(deg) + 
  fRDrive.position(deg) + bRDrive.position(deg) + mRDrive.position(deg)) / 6; //our drive targey minus the avg position of the motors
  
  while (fabs(driveError) > 3){
  float previousDriveError = driveError;
  float driveP = driveKp * driveError;
  float driveI = driveI + (.02 * driveError * driveKi);
  float driveD = driveKd * (driveError - previousDriveError)/1;

    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spin(fwd, (driveP + driveI + driveD), pct);
    wait (20, msec);
  }
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setStopping(brake);
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spin(fwd, 0, pct);
}