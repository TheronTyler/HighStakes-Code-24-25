#include "robot-config.h"
#include "vex.h"

void turn(float turnTarget){
  float turnTarget;
  float turnKp = 3; //needs tuned
  float turnKi = 0.1; //needs tuned
  float turnKd = 3; //needs tuned
  float turnError = turnTarget - sense.heading();
  float P = turnKp * turnError;
  float I = I + (LOOPTIME * turnError * turnKi);
  float D = turnKd * (turnError - turnErrorPrevious)/LOOPTIME;

  while(fabs(turnError)>1){
    motor_group(fLDrive, bLDrive, mLDrive).spin(fwd, 35 + (P + I + D), pct);
    motor_group(fRDrive, bRDrive, mRDrive).spin(fwd, 35 - (P + I + D), pct);
  }
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).stop();
}
/*
void TurnHeading(double targetHeading) {
  double currentError = targetHeading - sense.heading();
  
  double Kp = 10; //Needs Tested
  double Ki = 0;
  double Kd = 0;
  

  double motorSpeed;

  while(fabs(currentError)>4) {
    motorSpeed = Kp*currentError;
    motor_group(fLDrive, bLDrive, mLDrive).spin(fwd,-motorSpeed,pct);
    motor_group(fRDrive, bRDrive, mRDrive).spin(fwd,motorSpeed,pct);
    currentError = targetHeading - sense.heading();
  }
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).stop();
}
*/
