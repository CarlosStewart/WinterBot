#pragma once
#include "main.h"

// MACROS
#define GREEN AbstractMotor::gearset::green
#define BLUE AbstractMotor::gearset::blue
#define DEGREES AbstractMotor::encoderUnits::degrees

// MOTORS
////////////////
const int DLF_PORT = 18;
const bool DLF_REV = true;

const int DRF_PORT = 2;
const bool DRF_REV = false;

const int DLB_PORT = 10;
const bool DLB_REV = true;

const int DRB_PORT = 1;
const bool DRB_REV = false;

////////////////
const int TILT_PORT = 3;
const bool TILT_REV = true;

////////////////
const int ROLLL_PORT = 20;
const bool ROLLL_REV = true;

const int ROLLR_PORT = 12;
const bool ROLLR_REV = false;

// CONTROLS
#define BTN_MACRO_STACK ControllerDigital::right
#define BTN_TILT_DOWN_AUTO ControllerDigital::down
#define BTN_TILT_UP ControllerDigital::L1
#define BTN_TILT_DOWN ControllerDigital::L2
#define BTN_TILT_LOW ControllerDigital::A
#define BTN_TILT_MID ControllerDigital::B
#define BTN_TILT_HIGH ControllerDigital::X
#define BTN_ROLL_TOGGLE ControllerDigital::Y
#define BTN_ROLL_IN ControllerDigital::R1
#define BTN_ROLL_OUT ControllerDigital::R2
#define BTN_ROLL_COAST ControllerDigital::down

// SENSORS
const char TP_PORT = 'A';
///////////////
const char TRACK_SIDE = 'B';
const char TRACK_RIGHT = 'D';
const char TRACK_LEFT = 'F';
