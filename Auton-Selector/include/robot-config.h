#pragma once
#include "vex.h"
using namespace vex;

static competition Competition;

static brain Brain;
static controller Controller;

static motor fLDrive = motor(PORT13, ratio36_1, true);
static motor bLDrive = motor(PORT11, ratio36_1, true);
static motor mLDrive = motor(PORT12, ratio36_1, true);
static motor fRDrive = motor(PORT1, ratio36_1);
static motor bRDrive = motor(PORT2, ratio36_1);
static motor mRDrive = motor(PORT3, ratio36_1);

static motor intake = motor(PORT14);

static motor arm = motor(PORT9);

static inertial sense = inertial(PORT20);
static rotation armAngle = rotation(PORT5);
static aivision ai = aivision(PORT10);

static digital_out moGo = digital_out(Brain.ThreeWirePort.A);
static digital_out doinker = digital_out(Brain.ThreeWirePort.H);
static digital_out wallStake = digital_out(Brain.ThreeWirePort.G);

