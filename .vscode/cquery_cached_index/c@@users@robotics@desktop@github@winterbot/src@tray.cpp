#include "main.h"

Motor tray_motor(TRAY);
Potentiometer tray_pot(PT);
auto controller = AsyncControllerFactory::posPID(
    tray_motor, ADIEncoder('A', 'B'), 0.001, 0.0, 0.0001);
Tray tray(true);
