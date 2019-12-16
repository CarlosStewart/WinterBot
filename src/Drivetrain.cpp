#include "main.h"

Motor dvtn_left_front_motor(DLF);
Motor dvtn_left_back_motor(DLB);
Motor dvtn_right_front_motor(DRF);
Motor dvtn_right_back_motor(DRB);
MotorGroup dvtn_left_motors({dvtn_left_front_motor, dvtn_left_back_motor});
MotorGroup dvtn_right_motors({dvtn_right_front_motor, dvtn_right_back_motor});

// overload constructor
Drivetrain::Drivetrain(double tSlewIncrement) {
  slewIncrement = tSlewIncrement;
}

// public movement methods
void Drivetrain::updateArcade(double tForwardVel, double tTurnVel,
                              bool tSlewOn) {
  if (tSlewOn) {
    // update target forward velocity
    if (tForwardVel > nextForwardVel) {
      nextForwardVel += slewIncrement;
    } else if (tForwardVel < nextForwardVel) {
      nextForwardVel -= slewIncrement;
    }

    // update target turn velocity
    if (tTurnVel > nextTurnVel) {
      nextTurnVel += slewIncrement;
    } else if (tTurnVel < nextTurnVel) {
      nextTurnVel -= slewIncrement;
    }

    // move the motors at the target velocities
    ctrl.moveArcade(nextForwardVel, nextTurnVel);
  } else {
    ctrl.moveArcade(tForwardVel, tTurnVel);
  }
}

// state Control
// sets the state
void Drivetrain::setState(state_dvtn tState) { state = tState; }
// returns the state
state_dvtn Drivetrain::getState() { return state; }

/////////////////////////
//                     //
//    Control Class    //
//                     //
/////////////////////////

// basic movement methods
// moves the drivetrain forward, and turns at specific velocities
void Drivetrain::Control::moveArcade(double tForwardVel, double tTurnVel) {
  dvtn_left_motors.moveVelocity(tForwardVel + tTurnVel);
  dvtn_right_motors.moveVelocity(tForwardVel - tTurnVel);
}
// moves the drivetrain based on velocities of both sides
void Drivetrain::Control::moveTank(double tLeftVel, double tRightVel) {
  dvtn_left_motors.moveVelocity(tLeftVel);
  dvtn_right_motors.moveVelocity(tRightVel);
}
// sets the speed to 0
void Drivetrain::Control::stop() {
  dvtn_left_motors.moveVelocity(0.0);
  dvtn_right_motors.moveVelocity(0.0);
}

// creation of dt object
Drivetrain dvtn(5.0);
