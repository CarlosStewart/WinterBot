#include "main.h"

Motor lift_motor(LIFT);

// constructors
// default
Lift::Lift() { lift_motor.setBrakeMode(AbstractMotor::brakeMode::hold); }
// overload
Lift::Lift(bool tPID) {
  if (tPID) {
    lift_motor.setBrakeMode(AbstractMotor::brakeMode::hold);
  } else {
    lift_motor.setBrakeMode(AbstractMotor::brakeMode::coast);
  }
}

// used to stop the lift, without stopping suddenly (blocking?)
void Lift::brake() {
  lift_motor.setBrakeMode(AbstractMotor::brakeMode::coast);
  lift_motor.moveVelocity(0.0);
  while (lift_motor.getActualVelocity() >= brakeVelRange ||
         lift_motor.getActualVelocity() <= -brakeVelRange) {
    pros::delay(50);
  }
  lift_motor.setBrakeMode(AbstractMotor::brakeMode::hold);
}

// move the lift up, with optional speed parameter
void Lift::moveUp() { lift_motor.moveVelocity(speed); }
// move the lift up, with optional speed parameter
void Lift::moveUp(double tSpeed) { lift_motor.moveVelocity(tSpeed); }
// move the lift down, with optional speed parameter
void Lift::moveDown() { lift_motor.moveVelocity(-speed); }
// move the lift down, with optional speed parameter
void Lift::moveDown(double tSpeed) { lift_motor.moveVelocity(-tSpeed); }
// move the lift with a specific speed
void Lift::move(double tSpeed) { lift_motor.moveVelocity(tSpeed); }

// move lift to a specific height (blocking?), with optional speed parameter
void Lift::moveTo(double tHeight) { lift_motor.moveAbsolute(tHeight, speed); }
// move lift to a specific height (blocking?), with optional speed parameter
void Lift::moveTo(double tHeight, double tVelocity) {
  lift_motor.moveAbsolute(tHeight, tVelocity);
}
// move lift to a specific height (blocking?), with optional speed parameter
void Lift::moveTo(heights tHeight) { lift_motor.moveAbsolute(tHeight, speed); }
// move lift to a specific height (blocking?), with optional speed parameter
void Lift::moveTo(heights tHeight, double tVelocity) {
  lift_motor.moveAbsolute(tHeight, tVelocity);
}

// turns the lift PID on/off with optional toggle perameter
void Lift::togglePID() {
  if (lift_motor.getBrakeMode() == AbstractMotor::brakeMode::hold)
    lift_motor.setBrakeMode(AbstractMotor::brakeMode::coast);
  else if (lift_motor.getBrakeMode() == AbstractMotor::brakeMode::coast)
    lift_motor.setBrakeMode(AbstractMotor::brakeMode::hold);
}
// turns the lift PID on/off with optional toggle perameter
void Lift::togglePID(bool tOn) {
  if (!tOn)
    lift_motor.setBrakeMode(AbstractMotor::brakeMode::coast);
  else if (tOn)
    lift_motor.setBrakeMode(AbstractMotor::brakeMode::hold);
}

// go the the resting position, with optional speed parameter
void Lift::rest() { moveTo(heights::restPos, speed); }
// go the the resting position, with optional speed parameter
void Lift::rest(double tSpeed) { moveTo(heights::restPos, tSpeed); }

Lift lift(true);
