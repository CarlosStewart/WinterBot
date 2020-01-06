#include "main.h"

Motor tray_motor(TRAY);
Potentiometer tray_pot(PT);
auto controllerTray =
    AsyncControllerFactory::posPID(tray_motor, tray_pot, 0.01, 0.0, 0.0);

// default constructor
Tray::Tray(bool isThisDumb) {
  tray_motor.setBrakeMode(AbstractMotor::brakeMode::hold);
}

// enables the controller
void Tray::enable() { controllerTray.flipDisable(false); }
// disables the controller
void Tray::disable() { controllerTray.flipDisable(true); }

// moves the tray to the lowest availible position
void Tray::rest() {
  disable();
  tray_motor.setBrakeMode(AbstractMotor::brakeMode::coast);
}

// sets the targetHeight
void Tray::setTarget(heights_tray tHeight) {
  controllerTray.setTarget((double)tHeight);
}
void Tray::setTarget(double tHeight) { controllerTray.setTarget(tHeight); }
// makes the tray stop as soon as possible without jerking
void Tray::brake() {
  tray_motor.setBrakeMode(AbstractMotor::brakeMode::coast);
  tray_motor.moveVelocity(0.0);
  while (tray_motor.getActualVelocity() >= brakeVelRange ||
         tray_motor.getActualVelocity() <= -brakeVelRange) {
    pros::delay(50);
  }
  tray_motor.setBrakeMode(AbstractMotor::brakeMode::hold);
}

// state Control
// sets the state
void Tray::setState(state_tray tState) { state = tState; }
// returns the state
state_tray Tray::getState() { return state; }

Tray tray(true);
