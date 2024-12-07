#pragma once
#include "vex.h"

void turn(float turnTarget);
void drive(float driveTarget);

extern float turnTarget;
extern float turnKp;   
extern float turnKi;
extern float turnKd;
extern float turnError;
extern float previousTurnError;
extern float turnP;
extern float turnI;
extern float turnD;

extern float driveTarget;
extern float driveKp;
extern float driveKi;
extern float driveKd;
extern float driveError;
extern float previousDriveError;
extern float driveP;
extern float driveI;
extern float driveD;