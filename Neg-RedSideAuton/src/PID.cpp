#include "robot-config.h"
#include "vex.h"

void turn(float turnTarget){
  sense.setHeading(180, degrees);
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

void drive(float driveTarget){ //360 deg = 35.5" //1 deg = 0.099"
  fLDrive.setPosition(0, degrees);

  float driveKp = .5; //needs tuned
  float driveKi = .0003; //needs tuned
  float driveKd = 1; //needs tuned
  float driveError = driveTarget - ((fLDrive.position(deg) + fRDrive.position(deg)) / 2); 
  
  while (fabs(driveError) > 100){
  driveError = driveTarget - (fLDrive.position(deg));
  float previousDriveError = driveError;
  float driveP = driveKp * driveError;
  float driveI = driveI + (.02 * driveError * driveKi);
  float driveD = driveKd * (driveError - previousDriveError)/1;

    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spin(fwd, (driveP + driveI + driveD)*0.75, pct);
    wait (20, msec);
  }
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setStopping(brake);
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spin(fwd, 0, pct);
}