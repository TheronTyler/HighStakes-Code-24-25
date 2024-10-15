#include "vex.h"
using namespace vex;

competition Competition;

brain Brain;
controller Controller;

motor fLDrive = motor(PORT1, true);
motor bLDrive = motor(PORT2, true);
motor mLDrive = motor(PORT3, true);
motor fRDrive = motor(PORT4);
motor bRDrive = motor(PORT5);
motor mRDrive = motor(PORT6);

motor lIntake = motor(PORT7, true);
motor uIntake = motor(PORT8);

motor arm = motor(PORT9);

inertial sense = inertial(PORT10);

digital_out moGo = digital_out(Brain.ThreeWirePort.A);