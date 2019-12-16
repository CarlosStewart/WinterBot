#include "main.h"

Motor tray_motor(TRAY);
Potentiometer tray_pot(PT);
auto controller =
    AsyncControllerFactory::posPID(tray_motor, tray_pot, 0.0, 0.0, 0.0);

//default constructor
Tray::Tray(bool isThisDumb) {
  restHeight = (double) heights_tray::bottom;
}

// enables the controller
void Tray::enable(){
  controller.flipDisable(true);
}
// disables the controller
void Tray::disable(){
  controller.flipDisable(false);
}

// moves the tray to the lowest availible position
void Tray::goToRest(){
  controller.setTarget(restHeight);
}

// sets the targetHeight
void Tray::setTarget(heights_tray tHeight){
  controller.setTarget((double) tHeight);
}
void Tray::setTarget(double tHeight){
  controller.setTarget(tHeight);
}

// state Control
// sets the state
void Tray::setState(state_tray tState){
  state = tState;
}
// returns the state
state_tray Tray::getState(){
  return state;
}

Tray tray(true);
