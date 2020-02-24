#include "main.h"

Motor lift_motor(LIFT);
auto controllerLift = AsyncControllerFactory::posIntegrated(lift_motor);

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
// waits until the controller has reached its target
void Lift::waitForController() { controllerLift.waitUntilSettled(); }
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
// sets the maxumum speed of the controller
void Lift::limitSpeedTo(double tVelocity) {
  controllerLift.setMaxVelocity(tVelocity);
}
// returns the target height of the controller
double Lift::getTarget() { return controllerLift.getTarget(); }
// returns the current location of the controller
double Lift::getLocation() {
  return controllerLift.getTarget() - controllerLift.getError();
}
// makes the lift stop as soon as possible without jerking
void Lift::brake() {
  lift_motor.setBrakeMode(AbstractMotor::brakeMode::brake);
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
