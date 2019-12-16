#include "main.h"

void mcroStak() {
  lift.togglePID(false);
  tray.moveUp();
  pros::delay(2000);
  tray.brake();
  intk.spinOut(50);
  dvtn.ctrl.moveArcade(-80, 0);
  pros::delay(1500);
  dvtn.ctrl.moveArcade(0, 0);
  lift.moveUp();
  intk.spinIn();
  tray.moveDown();
  pros::delay(1800);
  lift.brake();
  intk.toggle(false);
  tray.brake();
  lift.togglePID(true);
}

void mcroStk2() {
  intk.toggle(false);
  intk.togglePID(false);
  tray.moveTo(Tray::heights::stack);
  pros::delay(10000);
  intk.togglePID(true);
}

void mcroDply() {
  tray.moveUp();
  pros::delay(500);
  intk.spinOut(150.0);
  pros::delay(600);
  tray.moveDown();
  intk.spinIn();
  pros::delay(1000);
  tray.brake();
}
