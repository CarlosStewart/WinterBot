#include "main.h"

void mcroStack() {
  // moves the tray to vertical
  tray.setTarget(heights_tray::vertical);
  tray.setState(state_tray::moveToTarget);
  // waits until a certain height before letting the cubes free
  while (tray_pot.get() < (double)heights_tray::dropSpot)
    pros::delay(20);
  intk.setState(state_intk::coast);
}

void mcroReverse() {
  // spins the intake out
  intk.setSpeed(-50.0);
  intk.setState(state_intk::precise);
  // backs up the drivetrain
  dvtn.setState(state_dvtn::idle);
  dvtn.ctrl.moveArcade(-50.0, 0.0);
  // continues backing up for a bit, then lowers the tray
  pros::delay(1500);
  dvtn.setState(state_dvtn::plain);
  tray.setTarget(heights_tray::bottom);
  tray.setState(state_tray::moveToTarget);
  // turns off the intake
  intk.setState(state_intk::hold);
}

void mcroGetRow() {
  intk.setSpeed(100.0);
  intk.setState(state_intk::precise);
  dvtn.setState(state_dvtn::idle);
  dvtn.ctrl.moveArcade(70.0, 0.0);
  pros::delay(3000);
  dvtn.setState(state_dvtn::plain);
}
