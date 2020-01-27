#include "main.h"

Motor tray_motor(TRAY);
Potentiometer tray_pot(PT);
auto controllerTray = AsyncControllerFactory::posIntegrated(tray_motor, 200);

// default constructor
Tray::Tray() { disable(); }

// enables the controller
void Tray::enable() { controllerTray.flipDisable(false); }
// disables the controller
void Tray::disable() { controllerTray.flipDisable(true); }

// sets the controller to 0
void Tray::setBottom() { controllerTray.tarePosition(); }
// sets the targetHeight
void Tray::setTarget(heights_tray tHeight) {
  enable();
  controllerTray.setTarget((double)tHeight);
}
void Tray::setTarget(double tHeight) {
  enable();
  controllerTray.setTarget(tHeight);
}
// returns the target height of the tray
double Tray::getTarget() { return controllerTray.getTarget(); }
// returns the current location of the controller
double Tray::getLocation() {
  return controllerTray.getTarget() - controllerTray.getError();
}
// returns whether or not the tray should be going slow
bool Tray::isInSlowZone() {
  return getLocation() > (double)heights_tray::slowZone;
}
// sets the maximum speed of the controller
void Tray::limitSpeedTo(double tMaxSpeed) {
  controllerTray.setMaxVelocity(tMaxSpeed);
}
// returns whether or not the controller has settled
bool Tray::controllerSettled() { return controllerTray.isSettled(); }
// stops the thread until the controller has settled
void Tray::pauseUntilSettled() { controllerTray.waitUntilSettled(); }

// state Control
// sets the state
void Tray::setState(state_tray tState) { state = tState; }
// returns the state
state_tray Tray::getState() { return state; }

Tray tray;
