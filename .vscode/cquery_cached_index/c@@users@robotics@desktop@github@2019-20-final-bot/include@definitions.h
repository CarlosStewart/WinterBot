#pragma once
#include "main.h"

// functions
void mcroStak();
void mcroStk2();
void mcroDply();

// motors
const int DLF = 11;
const int DRF = -13;
const int DRB = -17;
const int DLB = 16;
extern Motor dvtn_left_front_motor;
extern Motor dvtn_left_back_motor;
extern Motor dvtn_right_front_motor;
extern Motor dvtn_right_back_motor;
extern MotorGroup dvtn_left_motors;
extern MotorGroup dvtn_right_motors;

const int IL = 1;
const int IR = -2;
extern MotorGroup intk_motors;

const int TRAY = -14;
extern Motor tray_motor;

const int LIFT = 10;
extern Motor lift_motor;

// sensors
const char TL_TOP = 'A';
const char TL_BOTTOM = 'B';
const bool TL_REV = false;

const char TR_TOP = 'C';
const char TR_BOTTOM = 'D';
const bool TR_REV = false;

// const char TS_TOP = 'E';
// const char TS_BOTTOM = 'F';
// const bool TS_REV = false;

const char PT = 'G';

// buttons
#define BTN_DVTN_TGL_SLEW ControllerDigital::down

#define BTN_INTK_TGL ControllerDigital::Y
#define BTN_INTK_IN ControllerDigital::R1
#define BTN_INTK_OUT ControllerDigital::R2

#define BTN_TRAY_UP ControllerDigital::L1
#define BTN_TRAY_DOWN ControllerDigital::L2

#define BTN_LIFT_UP ControllerDigital::R1
#define BTN_LIFT_DOWN ControllerDigital::R2
#define BTN_LIFT_LOW ControllerDigital::left
#define BTN_LIFT_MED ControllerDigital::up
#define BTN_LIFT_HIGH ControllerDigital::B

#define BTN_MCRO_STAK ControllerDigital::right
