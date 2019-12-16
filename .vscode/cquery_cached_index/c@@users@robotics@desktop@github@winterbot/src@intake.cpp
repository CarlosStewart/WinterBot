#include "main.h"

MotorGroup intk_motors({IL, IR});

// default constructor
Intake::Intake() {
  intk_motors.setBrakeMode(AbstractMotor::brakeMode::hold);
  speed = 0;
}

// overload constructor
Intake::Intake(bool tHold) {
  if (tHold) {
    intk_motors.setBrakeMode(AbstractMotor::brakeMode::hold);
  } else {
    intk_motors.setBrakeMode(AbstractMotor::brakeMode::coast);
  }
  speed = 0;
}

// control
// moves the intake in or out, based on the sign (and optional perameter)
void Intake::spin() { intk_motors.moveVelocity(speed); }
void Intake::spin(double tSpeed) { intk_motors.moveVelocity(tSpeed); }
// moves the intake in (optional perameter)
void Intake::spinIn() { intk_motors.moveVelocity(fullSpeed); }
void Intake::spinIn(double tSpeed) { intk_motors.moveVelocity(tSpeed); }
// moves the intake out (optional perameter)
void Intake::spinOut() { intk_motors.moveVelocity(-fullSpeed); }
void Intake::spinOut(double tSpeed) { intk_motors.moveVelocity(-tSpeed); }
// if the intake is spinning out, stop; otherwise, spin in
void Intake::toggle() {
  if (intk_motors.getTargetVelocity() != 0.0)
    intk_motors.moveVelocity(0.0);
  else
    intk.spinIn();
}
// stops the intake with or without braketype hold
void Intake::stop(bool tHold) {
  if (tHold)
    intk_motors.setBrakeMode(AbstractMotor::brakeMode::hold);
  else
    intk_motors.setBrakeMode(AbstractMotor::brakeMode::coast);
  intk_motors.moveVelocity(0.0);
}

// interfacing
// sets the speed
void Intake::setSpeed(double tSpeed) { speed = tSpeed; }
// returns the speed
double Intake::getSpeed() { return speed; }

// state control
// sets the state
void Intake::setState(state_intk tState) { state = tState; }
// returns the state
state_intk Intake::getState() { return state; }

// creates an Intake object with starting PID on.
Intake intk(false);
