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

motor bPack = motor(PORT4);

inertial sense = inertial(PORT5);
rotation bPackAngle = rotation(PORT9);
aivision ai = aivision(PORT10);

digital_out moGo = digital_out(Brain.ThreeWirePort.B);

digital_out doinker = digital_out(Brain.ThreeWirePort.H);