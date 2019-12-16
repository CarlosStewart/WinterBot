#include "main.h"

MotorGroup intk_motors({IL, IR});

// default constructor
Intake::Intake() { intk_motors.setBrakeMode(AbstractMotor::brakeMode::hold); }

// overload constructor
Intake::Intake(bool tPID) {
  if (tPID) {
    intk_motors.setBrakeMode(AbstractMotor::brakeMode::hold);
  } else {
    intk_motors.setBrakeMode(AbstractMotor::brakeMode::coast);
  }
}

// toggles the intake between on or off
void Intake::toggle() {
  if (intk_motors.getTargetVelocity() == 0) {
    intk_motors.moveVelocity(speed);
  } else {
    intk_motors.moveVelocity(0.0);
  }
}
// sets the intake to on (true) or off (false)
void Intake::toggle(bool tOn) {
  if (tOn) {
    intk_motors.moveVelocity(speed);
  } else {
    intk_motors.moveVelocity(0.0);
  }
}

// spins the intake in at the default speed
void Intake::spinIn() { intk_motors.moveVelocity(speed); }
// spins the intake in with a specific speed
void Intake::spinIn(double tSpeed) { intk_motors.moveVelocity(tSpeed); }
// spins the intake out at the default speed
void Intake::spinOut() { intk_motors.moveVelocity(-speed); }
// spins the intake out with a specific speed
void Intake::spinOut(double tSpeed) { intk_motors.moveVelocity(-tSpeed); }
// sets the intake to a specific speed (in or out)
void Intake::spin(double tSpeed) { intk_motors.moveVelocity(tSpeed); }

// toggles the intake PID between on or off
void Intake::togglePID() {
  if (intk_motors.getBrakeMode() == AbstractMotor::brakeMode::coast) {
    intk_motors.setBrakeMode(AbstractMotor::brakeMode::hold);
  } else {
    intk_motors.setBrakeMode(AbstractMotor::brakeMode::coast);
  }
}
// sets the intake PID to on (true) or off (false)
void Intake::togglePID(bool tOn) {
  if (tOn) {
    intk_motors.setBrakeMode(AbstractMotor::brakeMode::hold);
  } else {
    intk_motors.setBrakeMode(AbstractMotor::brakeMode::coast);
  }
}

// creates an Intake object with starting PID on.
Intake intk(true);
