#include "main.h"

Motor tray_motor(TRAY);

// makes a new tray object with PID on/off bool (default on)
Tray::Tray() { tray_motor.setBrakeMode(AbstractMotor::brakeMode::hold); }
// makes a new tray object with PID on/off bool (default on)
Tray::Tray(bool tPID) {
  if (tPID) {
    tray_motor.setBrakeMode(AbstractMotor::brakeMode::hold);
  } else {
    tray_motor.setBrakeMode(AbstractMotor::brakeMode::coast);
  }
}

// used to stop the tray, without stopping suddenly (blocking?)
void Tray::brake() {
  tray_motor.setBrakeMode(AbstractMotor::brakeMode::coast);
  tray_motor.moveVelocity(0.0);
  while (tray_motor.getActualVelocity() >= brakeVelRange ||
         tray_motor.getActualVelocity() <= -brakeVelRange) {
    pros::delay(50);
  }
  tray_motor.setBrakeMode(AbstractMotor::brakeMode::hold);
}

// move the tray up, with optional speed parameter
void Tray::moveUp() { tray_motor.moveVelocity(speed); }
// move the tray up, with optional speed parameter
void Tray::moveUp(double tSpeed) { tray_motor.moveVelocity(tSpeed); }
// move the tray down, with optional speed parameter
void Tray::moveDown() { tray_motor.moveVelocity(-speed); }
// move the tray down, with optional speed parameter
void Tray::moveDown(double tSpeed) { tray_motor.moveVelocity(-tSpeed); }
// move the tray with a specific speed
void Tray::move(double tSpeed) { tray_motor.moveVelocity(tSpeed); }

// move tray to a specific height (blocking?), with optional speed parameter
void Tray::moveTo(double tHeight) { tray_motor.moveAbsolute(tHeight, speed); }
// move tray to a specific height (blocking?), with optional speed parameter
void Tray::moveTo(double tHeight, double tVelocity) {
  tray_motor.moveAbsolute(tHeight, tVelocity);
}
// move lift to a specific height (blocking?), with optional speed parameter
void Tray::moveTo(heights tHeight) { tray_motor.moveAbsolute(tHeight, speed); }
// move lift to a specific height (blocking?), with optional speed parameter
void Tray::moveTo(heights tHeight, double tVelocity) {
  tray_motor.moveAbsolute(tHeight, tVelocity);
}

// go the the resting position, with optional speed parameter
void Tray::rest() { moveTo(restPos, speed); }
// go the the resting position, with optional speed parameter
void Tray::rest(double tSpeed) { moveTo(restPos, tSpeed); }

Tray tray(true);
