#include "main.h"

Motor tray_motor(TRAY);
Potentiometer tray_pot(PT);
auto controller =
    AsyncControllerFactory::posPID(tray_motor, tray_pot, 0.0, 0.0, 0.0);

// default constructor
Tray::Tray(bool isThisDumb) {
  restHeight = (double)heights_tray::bottom;
  tray_motor.setBrakeMode(AbstractMotor::brakeMode::hold);
}

// enables the controller
void Tray::enable() { controller.flipDisable(true); }
// disables the controller
void Tray::disable() { controller.flipDisable(false); }

// moves the tray to the lowest availible position
void Tray::goToRest() { controller.setTarget(restHeight); }

// sets the targetHeight
void Tray::setTarget(heights_tray tHeight) {
  controller.setTarget((double)tHeight);
}
void Tray::setTarget(double tHeight) { controller.setTarget(tHeight); }

// returns the restHeight
double Tray::getRestHeight() { return restHeight; }

// state Control
// sets the state
void Tray::setState(state_tray tState) { state = tState; }
// sets the lastState
void Tray::setLastState(state_tray tState) { lastState = tState; }
// returns the state
state_tray Tray::getState() { return state; }
// returns the state
state_tray Tray::getLastState() { return lastState; }

Tray tray(true);
