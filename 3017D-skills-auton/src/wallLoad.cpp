#include "robot-config.h"
#include "vex.h"

void wallLoad() {
intake.setVelocity(95, pct);
  bool wIntake = true;
  while (wIntake == true) {
    while(!(color_sort.color() == red)) {
      intake.spin(fwd);
      wait(5,msec);
    }
    wait(160, msec);
    intake.stop();
    wait(50,msec);
    intake.spinFor(reverse, .25, sec);
  }
  intake.spinFor(1,sec);
  wIntake = false;
}