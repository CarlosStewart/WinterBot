#include "main.h"

void deploy() {
  lift.setTarget(heights_lift::raisedThreshold);
  lift.setState(state_lift::moveToTarget);
  lift.waitForController();
  lift.setTarget(heights_lift::bottom);
  lift.setState(state_lift::moveToTarget);
  lift.waitForController();
}

void skillsDeploy() {
  lift.setTarget(200);
  lift.setState(state_lift::moveToTarget);
  pros::delay(200);
  intk.setState(state_intk::out);
  pros::delay(400);
  lift.setTarget(0);
  lift.setState(state_lift::moveToTarget);
}

void mcroStack(bool ten) {
  tray.setState(state_tray::stack);
  if (!ten) {
    intk.setSpeed(-30.0);
    intk.setState(state_intk::precise);
  } else {
    pros::delay(1000);
    intk.setState(state_intk::coast);
  }
  while (tray.getLocation() < (double)heights_tray::slowZone)
    pros::delay(20);
  intk.setState(state_intk::coast);
  tray.pauseUntilSettled();
  tray.setState(state_tray::moveDown);
  intk.setSpeed(-100.0);
  intk.setState(state_intk::precise);
  pros::delay(400);
  intk.setState(state_intk::coast);
  // pros::delay(500);
  // spins the intake out
  // backs up the drivetrain
  pros::delay(400);
  dvtn.setState(state_dvtn::idle);
  dvtn.ctrl.moveArcade(-100.0, 0.0);
  // continues backing up for a bit, then lowers the tray
  pros::delay(500);
  dvtn.setState(state_dvtn::plain);
  tray.setState(state_tray::moveDown);
  // turns off the intake
  intk.setState(state_intk::hold);
}

void mcroStackAuton(void *) {
  /*
  tray.setTarget((double)heights_tray::vertical + 50);
  tray.limitSpeedTo(70.0);
  intk.spin(-20.0);
  while (tray.getLocation() < (double)heights_tray::slowZone)
    pros::delay(20);
  intk.stop(false);
  tray.pauseUntilSettled();
  // spins the intake out
  intk.spin(-200.0);
  // backs up the drivetrain
  pros::delay(400);
  dvtn.ctrl.moveArcade(-200.0, 0.0);
  // continues backing up for a bit, then lowers the tray
  pros::delay(500);
  dvtn.setState(state_dvtn::plain);
  tray.setState(state_tray::moveDown);
  // turns off the intake
  intk.setState(state_intk::hold);
  */
  tray.setState(state_tray::stack);
  intk.setSpeed(-20.0);
  intk.setState(state_intk::precise);

  while (tray.getLocation() < (double)heights_tray::slowZone)
    pros::delay(20);
  intk.setState(state_intk::coast);
  tray.pauseUntilSettled();
  // pros::delay(500);
  // spins the intake out
  intk.setSpeed(-100.0);
  intk.setState(state_intk::precise);
  // backs up the drivetrain
  pros::delay(400);
  dvtn.setState(state_dvtn::idle);
  dvtn.ctrl.moveArcade(-100.0, 0.0);
  // continues backing up for a bit, then lowers the tray
  pros::delay(500);
  dvtn.setState(state_dvtn::plain);
  tray.setState(state_tray::moveDown);
  // turns off the intake
  intk.setState(state_intk::hold);
}

void mcroStackAfterTime(void *) {
  pros::delay(10500);
  tray.setState(state_tray::stack);
  intk.setSpeed(-30.0);
  intk.setState(state_intk::precise);

  while (tray.getLocation() < (double)heights_tray::slowZone)
    pros::delay(20);
  intk.setState(state_intk::coast);
  tray.pauseUntilSettled();
  // pros::delay(500);
  // spins the intake out
  intk.setSpeed(-100.0);
  intk.setState(state_intk::precise);
  // backs up the drivetrain
  pros::delay(400);
  dvtn.setState(state_dvtn::idle);
  dvtn.ctrl.moveArcade(-100.0, 0.0);
  // continues backing up for a bit, then lowers the tray
  pros::delay(500);
  dvtn.setState(state_dvtn::plain);
  tray.setState(state_tray::moveDown);
  // turns off the intake
  intk.setState(state_intk::hold);
}
/*
void mcroStackNoRev() {
  tray.setTarget(heights_tray::vertical);
  while (tray_pot.get() < (double)heights_tray::dropSpot)
    pros::delay(20);
  intk.stop(false);
  intk.spin(-50);
  pros::delay(900);
}
*/
void mcroReverse() {
  // spins the intake out
  intk.setSpeed(-100.0);
  intk.setState(state_intk::precise);
  // backs up the drivetrain
  dvtn.setState(state_dvtn::idle);
  dvtn.ctrl.moveArcade(-100.0, 0.0);
  // continues backing up for a bit
  pros::delay(1500);
  dvtn.setState(state_dvtn::plain);
}

void mcroGetRow() {
  intk.setSpeed(100.0);
  intk.setState(state_intk::precise);
  dvtn.setState(state_dvtn::idle);
  dvtn.ctrl.moveArcade(70.0, 0.0);
  pros::delay(3000);
  dvtn.setState(state_dvtn::plain);
}

double adjustControl(double tInput, double tStrength, double tMin,
                     double tMax) {
  return abs(tInput) > 2
             ? (tInput < 0 ? -1 : 1) *
                       ((tMax - tMin) / tMax * pow(tInput, tStrength)) /
                       pow(tMax, tStrength - 1) +
                   (tInput < 0 ? -tMin : tMin)
             : 0;
}

double adjustControl(double tInput, double tStrength) {
  return adjustControl(tInput, tStrength, 0.0, 200.0);
}

Potentiometer line_follower(LF);
