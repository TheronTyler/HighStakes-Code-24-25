#include "vex.h"
using namespace vex;

competition Competition;

brain Brain;
controller Controller;

motor fLDrive = motor(PORT13, true);
motor bLDrive = motor(PORT11, true);
motor mLDrive = motor(PORT12, true);
motor fRDrive = motor(PORT1);
motor bRDrive = motor(PORT2);
motor mRDrive = motor(PORT3);

motor intake = motor(PORT14);

motor arm = motor(PORT9);

inertial sense = inertial(PORT5);
rotation armAngle = rotation(PORT20);
aivision ai = aivision(PORT10);

digital_out moGo = digital_out(Brain.ThreeWirePort.A);

digital_out doinker = digital_out(Brain.ThreeWirePort.H);