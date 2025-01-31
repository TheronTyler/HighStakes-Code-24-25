#include "robot-config.h"
#include "vex.h"

bool keepRunning = true;

void colorSort() {
while (keepRunning){
intake.setVelocity(95, pct);
  while(!(color_sort.color() == blue)) {
    intake.spin(fwd);
    wait(5,msec);
  }
wait(160, msec);
intake.stop();
wait(50,msec);
intake.spin(fwd);

this_thread::sleep_for(10);
}

}