#pragma once
#include "vex.h"

void wall(float WturnTarget);

extern float WturnTarget;
extern float WturnKp;   
extern float WturnKi;
extern float WturnKd;
extern float WturnError;
extern float WpreviousTurnError;
extern float WturnP;
extern float WturnI;
extern float WturnD; 
