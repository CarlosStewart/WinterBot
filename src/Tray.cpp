#include "main.h"

Motor tray_motor(TRAY);
Potentiometer tray_pot(PT);
auto controller =
    AsyncControllerFactory::posPID(tray_motor, tray_pot, 0.0, 0.0, 0.0);

Tray::Tray() {}

Tray tray();
