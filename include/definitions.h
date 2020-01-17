#pragma once
#include "main.h"

// functions
void mcroStack();
void mcroReverse();
#define hfix(i)                                                                \
  fmod(i, 360) < 0 ? fmod(i, 360) + 360 : fmod(i, 360) == -0 ? 0 : fmod(i, 360)

// motors
const int DLF = 1;
const int DRF = -4;
const int DRB = -3;
const int DLB = 2;
extern Motor dvtn_left_front_motor;
extern Motor dvtn_left_back_motor;
extern Motor dvtn_right_front_motor;
extern Motor dvtn_right_back_motor;
extern MotorGroup dvtn_left_motors;
extern MotorGroup dvtn_right_motors;
const char DLT_TOP = 'B';
const char DLT_BOTTOM = 'C';
const bool DLT_REV = false;
const char DRT_TOP = 'D';
const char DRT_BOTTOM = 'E';
const bool DRT_REV = false;
extern ADIEncoder dvtn_left_track;
extern ADIEncoder dvtn_right_track;
#define LEFT_TRACK_DIST 3.0
#define RIGHT_TRACK_DIST 3.0
#define TRACK_DIAMETER 2.75

const int IL = 11;
const int IR = -13;
extern MotorGroup intk_motors;

const int TRAY = -5;
extern Motor tray_motor;

const int LIFT = 10;
extern Motor lift_motor;

/*// sensors
const char TL_TOP = 'A';
const char TL_BOTTOM = 'B';
const bool TL_REV = false;

const char TR_TOP = 'C';
const char TR_BOTTOM = 'D';
const bool TR_REV = false;

const char TS_TOP = 'E';
const char TS_BOTTOM = 'F';
const bool TS_REV = false;
*/

const char PT = 'A';
extern Potentiometer tray_pot;

// buttons
#define BTN_DVTN_TGL_SLEW ControllerDigital::A

#define BTN_INTK_TGL ControllerDigital::Y
#define BTN_INTK_IN ControllerDigital::R1
#define BTN_INTK_OUT ControllerDigital::R2

#define BTN_TRAY_UP ControllerDigital::L1
#define BTN_TRAY_DOWN ControllerDigital::L2

#define BTN_LIFT_UP ControllerDigital::X
#define BTN_LIFT_DOWN ControllerDigital::B
#define BTN_LIFT_TOWER_LOW ControllerDigital::left
#define BTN_LIFT_TOWER_MID ControllerDigital::right

#define BTN_MCRO_STACK ControllerDigital::up
#define BTN_MCRO_REVERSE ControllerDigital::down
