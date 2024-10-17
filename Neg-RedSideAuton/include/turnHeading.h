#include "vex.h"

#include "devices.h"

using namespace vex;

void TurnHeading(double targetHeading) {
  double currentError = targetHeading - sense.heading();
  double Kp = 10; //Needs Tested
  double motorSpeed;

  while(fabs(currentError)>4) {
    motorSpeed = Kp*currentError;
    motor_group(fLDrive, bLDrive, mLDrive).spin(fwd,-motorSpeed,pct);
    motor_group(fRDrive, bRDrive, mRDrive).spin(fwd,motorSpeed,pct);
    currentError = targetHeading - sense.heading();
  }
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).stop();
}