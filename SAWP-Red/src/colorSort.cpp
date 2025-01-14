#include "robot-config.h"
#include "vex.h"

void colorSort(bool waitForCompletion) {
intake.setVelocity(95, pct);
  while(!(color_sort.color() == blue)) {
    intake.spin(fwd);
    wait(5,msec);
  }
wait(160, msec);
intake.stop();
wait(50,msec);
this_thread::sleep_for(10);
}
