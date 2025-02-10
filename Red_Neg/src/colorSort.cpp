#include "robot-config.h"
#include "vex.h"

bool threadRunning = true;

void colorSort() {
  while(threadRunning) {
  intake.setVelocity(95, pct);
    while(!(color_sort.color() == blue) && threadRunning) {
      intake.spin(fwd);
      wait(5,msec);
    }
  wait(160, msec);
  intake.stop();
  wait(50,msec);
  intake.spin(fwd);
  }
  intake.stop();
}