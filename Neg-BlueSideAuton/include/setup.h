#include "vex.h"
using namespace vex;

 competition Competition;

 brain Brain;
 controller Controller;

 motor fLDrive = motor(PORT8, ratio36_1, true);
 motor bLDrive = motor(PORT9, ratio36_1, true);
 motor mLDrive = motor(PORT10, ratio36_1, true);
 motor fRDrive = motor(PORT2, ratio36_1);
 motor bRDrive = motor(PORT5, ratio36_1);
 motor mRDrive = motor(PORT4, ratio36_1);

 motor intake = motor(PORT7);

 motor arm = motor(PORT11);

 inertial sense = inertial(PORT6);
 rotation armAngle = rotation(PORT20);
 aivision ai = aivision(PORT10);

 digital_out moGo = digital_out(Brain.ThreeWirePort.H);

 digital_out doinker = digital_out(Brain.ThreeWirePort.G);

 digital_out wallStake = digital_out(Brain.ThreeWirePort.F);