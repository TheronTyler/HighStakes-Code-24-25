#include "robot-config.h"
#include "vex.h"



void wall(float WturnTarget){
    sense.setHeading(180, degrees);
    float WturnKp = .05; //needs tuned
    float WturnKi = .05; //needs tuned
    float WturnKd = .1; //needs tuned
    float WturnError = disBR.objectDistance(mm) - disBL.objectDistance(mm);
    
    while(fabs(WturnError) > 4){
    WturnError = WturnTarget - (disBL.objectDistance(mm) - disBR.objectDistance(mm));
    float WpreviousTurnError = WturnError;
    float WturnP = WturnKp * WturnError;
    float WturnI = WturnI + (.02 * WturnError * WturnKi);
    float WturnD = WturnKd * (WturnError - WpreviousTurnError)/1;
  
      motor_group(fLDrive, bLDrive, mLDrive).spin(fwd,  -0.75*(WturnP  + WturnI + WturnD), pct);
      motor_group(fRDrive, bRDrive, mRDrive).spin(fwd,  0.75*(WturnP  + WturnI + WturnD), pct);
      wait (20, msec);
    }
    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).setStopping(brake);
    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spin(fwd, 0, pct);
  }


