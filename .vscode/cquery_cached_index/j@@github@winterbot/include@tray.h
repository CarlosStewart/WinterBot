#ifndef TRAY_H
#define TRAY_H
#include "main.h"
class Tray {
  state_tray state;
  heights_tray targetHeight;
  double restHeight;

public:
  // "default" constructor
  Tray(bool isThisDumb);

  // enables the controller
  void enable();
  // disables the controller
  void disable();

  // moves the tray to the lowest availible position
  void goToRest();
  // sets the targetHeight
  void setTarget(heights_tray tHeight);
  void setTarget(double tHeight);

  // state Control
  // sets the state
  void setState(state_tray tState);
  // returns the state
  state_tray getState();

};
extern Tray tray;
#endif
