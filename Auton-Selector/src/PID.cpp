#include "robot-config.h"
#include "vex.h"

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

double setpoint; // desired output  
double processVariable; // current output  
double error; // difference between setpoint and processVariable  
double previousError; // error in previous iteration  
double integral; // integral of error  
double derivative; // derivative of error  
double kp; // proportional gain  
double ki; // integral gain  
double kd; // derivative gain  
double output; // output of the controller  

double calculateOutput(double setpoint, double processVariable) {  
    error = setpoint - processVariable;  
    integral += error;  
    derivative = error - previousError;  
    output = kp * error + ki * integral + kd * derivative;  
    previousError = error;  
    return output;  
}  

void TurnHeading(double targetHeading) {
while(fabs(error)>4) {
    motor_group(fLDrive, bLDrive, mLDrive).spin(fwd,-output,pct);
    motor_group(fRDrive, bRDrive, mRDrive).spin(fwd,output,pct);
    error = targetHeading - sense.heading();
  }
  motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).stop();
}