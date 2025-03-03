#include "robot-config.h"
#include "vex.h"

void turn(float turnTarget){
  sense.setHeading(180, degrees);
  float turnKp = .25; //needs tuned
  float turnKi = .27; //needs tuned
  float turnKd = .35; //needs tuned
  float turnError = turnTarget - sense.heading();
  
  while(fabs(turnError) > 3){
  turnError = turnTarget - sense.heading();
  float previousTurnError = turnError;
  float turnP = turnKp * turnError;
  float turnI = turnI + (.02 * turnError * turnKi);
  float turnD = turnKd * (turnError - previousTurnError)/1;

    motor_group(fLDrive, bLDrive, mLDrive).spin(fwd,  1*(turnP  + turnI + turnD), pct);
    motor_group(fRDrive, bRDrive, mRDrive).spin(fwd,  -1*(turnP  + turnI + turnD), pct);
    wait (20, msec);
  }
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setStopping(brake);
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spin(fwd, 0, pct);
}

void drive(float driveTarget){ //  (DISTANCE / 35.5)*360
  fLDrive.setPosition(0, deg);
  fRDrive.setPosition(0, deg);

  float driveKp = .15; //needs tuned
  float driveKi = .255; //needs tuned
  float driveKd = .25; //needs tuned
  float driveError = driveTarget - ((fLDrive.position(deg) + fRDrive.position(deg)) / 2); 
  
  while (fabs(driveError) > 10){
  driveError = driveTarget - (fLDrive.position(deg));
  float previousDriveError = driveError;
  float driveP = driveKp * driveError;
  float driveI = driveI + (.02 * driveError * driveKi);
  float driveD = driveKd * (driveError - previousDriveError)/1;

    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spin(fwd, 2*(driveP + driveI + driveD)*1.3, pct);
    wait (20, msec);
  }
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setStopping(brake);
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spin(fwd, 0, pct);
}