#include "main.h"

ADIEncoder track_left(TL_TOP, TL_BOTTOM, TL_REV);
ADIEncoder track_right(TR_TOP, TR_BOTTOM, TR_REV);
// ADIEncoder track_side(TS_TOP, TS_BOTTOM, TS_REV);
Potentiometer pot_tilt(PT);

// accessors
// tracking wheels
double Sensors::Track::getLeft() { return track_left.get(); }
double Sensors::Track::getRight() { return track_right.get(); }
// double Sensors::Track::getSide() { return track_side.get(); }

// creation of sensors object
Sensors sensors;
