#include "vex.h"

#include "devices.h"

using namespace vex;

void Drive(double distance){
    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).spinFor(fwd,distance,rev);
    motor_group(fLDrive, bLDrive, mLDrive, fRDrive, bRDrive, mRDrive).stop();
}