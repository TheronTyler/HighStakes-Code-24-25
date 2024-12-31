#include "vex.h"
using namespace vex;

competition Competition;

brain Brain;
controller Controller;

motor fLDrive = motor(PORT8, true);
motor bLDrive = motor(PORT9, true);
motor mLDrive = motor(PORT10, true);
motor fRDrive = motor(PORT2);
motor bRDrive = motor(PORT5);
motor mRDrive = motor(PORT4);

motor intake = motor(PORT7);

motor arm = motor(PORT3);

inertial sense = inertial(PORT6);
rotation armAngle = rotation(PORT20);
aivision ai = aivision(PORT10);

digital_out moGo = digital_out(Brain.ThreeWirePort.H);

digital_out doinker = digital_out(Brain.ThreeWirePort.G);

digital_out wallStake = digital_out(Brain.ThreeWirePort.F);