#include "main.h"

Motor lift_motor(LIFT);
auto controllerLift =
    AsyncControllerFactory::posPID(lift_motor, 0.01, 0.0, 0.0);

// overload constructor
Lift::Lift(bool tBrakeModeHold) {
  if (tBrakeModeHold)
    lift_motor.setBrakeMode(AbstractMotor::brakeMode::hold);
  else
    lift_motor.setBrakeMode(AbstractMotor::brakeMode::coast);
}
// enables the controller
void Lift::enable() { controllerLift.flipDisable(false); }
// disables the controller
void Lift::disable() { controllerLift.flipDisable(true); }
// returns wheather or not it is disabled
int Lift::isDisabled() {
  if (controllerLift.isDisabled())
    return 1;
  else
    return 0;
}

// turns off the controller, and sets the brakeMode to coast
void Lift::rest() {
  disable();
  lift_motor.setBrakeMode(AbstractMotor::brakeMode::coast);
}
// sets the target height of the controller
void Lift::setTarget(heights_lift tHeight) {
  controllerLift.setTarget((double)tHeight);
}
void Lift::setTarget(double tHeight) { controllerLift.setTarget(tHeight); }
// makes the lift stop as soon as possible without jerking
void Lift::brake() {
  lift_motor.setBrakeMode(AbstractMotor::brakeMode::coast);
  lift_motor.moveVelocity(0.0);
  while (lift_motor.getActualVelocity() >= brakeVelRange ||
         lift_motor.getActualVelocity() <= -brakeVelRange) {
    pros::delay(50);
  }
  lift_motor.setBrakeMode(AbstractMotor::brakeMode::hold);
}

// state Control
// sets the state
void Lift::setState(state_lift tState) { state = tState; }
// returns the state
state_lift Lift::getState() { return state; }

Lift lift(true);
