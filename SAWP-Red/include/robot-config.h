#pragma once
#include "vex.h"
using namespace vex;

static competition Competition;

static brain Brain;
static controller Controller;

static motor fLDrive = motor(PORT8, ratio36_1, true);
static motor bLDrive = motor(PORT9, ratio36_1, true);
static motor mLDrive = motor(PORT10, ratio36_1, true);
static motor fRDrive = motor(PORT2, ratio36_1);
static motor bRDrive = motor(PORT5, ratio36_1);
static motor mRDrive = motor(PORT4, ratio36_1);

static motor intake = motor(PORT7);

static motor arm = motor(PORT3);

static inertial sense = inertial(PORT6);
static rotation armAngle = rotation(PORT20);
static aivision ai = aivision(PORT10);

static digital_out moGo = digital_out(Brain.ThreeWirePort.H);

static digital_out doinker = digital_out(Brain.ThreeWirePort.G);

static digital_out wallStake = digital_out(Brain.ThreeWirePort.F);