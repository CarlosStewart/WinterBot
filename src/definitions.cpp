#include "main.h"

void aLineSensor(){
  while(line_follower.get() > 2500){
    intk.setSpeed(-100.0);
    intk.setState(state_intk::precise);
  }
  while(line_follower.get() < 2500){
    intk.setSpeed(100.0);
    intk.setState(state_intk::precise);
  }
  intk.setState(state_intk::hold);

}

void mcroStack() {
  // moves the tray to vertical
  tray.setState(state_tray::stack);
  // intk.setSpeed(-20.0);
  // intk.setState(state_intk::precise);
  pros::delay(500);
  intk.setState(state_intk::coast);
  while (tray.getLocation() < (double)heights_tray::slowZone)
    pros::delay(20);
  intk.setState(state_intk::coast);
  tray.pauseUntilSettled();
  pros::delay(500);
  // spins the intake out
  intk.setSpeed(-50.0);
  intk.setState(state_intk::precise);
  // backs up the drivetrain
  pros::delay(400);
  dvtn.setState(state_dvtn::idle);
  dvtn.ctrl.moveArcade(-50.0, 0.0);
  // continues backing up for a bit, then lowers the tray
  pros::delay(1500);
  dvtn.setState(state_dvtn::plain);
  tray.setState(state_tray::moveDown);
  // turns off the intake
  intk.setState(state_intk::hold);
}

/*
void mcroStackAuton() {
  tray.setTarget(heights_tray::vertical);
  while (tray_pot.get() < (double)heights_tray::dropSpot)
    pros::delay(20);
  intk.stop(false);
  intk.spin(-50);
  pros::delay(900);
  dvtn.ctrl.moveArcade(-50, 0.0);
  pros::delay(2000);
  dvtn.ctrl.moveArcade(0.0, 0.0);
  intk.stop(true);
}

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

Potentiometer line_follower(LF);
