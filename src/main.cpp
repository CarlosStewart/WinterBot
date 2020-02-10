#include "main.h"

Controller con(ControllerId::master);

void intkControl(void *) {
  ControllerButton btn_intk_tgl(BTN_INTK_TGL);
  ControllerButton btn_intk_in(BTN_INTK_IN);
  ControllerButton btn_intk_out(BTN_INTK_OUT);
  intk.setState(state_intk::hold);

  while (true) {
    if (btn_intk_tgl.changedToPressed()) {
      if (intk.getState() == state_intk::hold ||
          intk.getState() == state_intk::coast)
        intk.setState(state_intk::in);
      else
        intk.setState(state_intk::hold);
    } else if (btn_intk_in.changedToPressed()) {
      intk.setState(state_intk::in);
    } else if (btn_intk_out.changedToPressed()) {
      intk.setState(state_intk::out);
    } else if (btn_intk_in.changedToReleased() ||
               btn_intk_out.changedToReleased()) {
      intk.setState(state_intk::hold);
    }

    switch (intk.getState()) {
    case state_intk::in:
      intk.spinIn();
      break;
    case state_intk::out:
      intk.spinOut();
      break;
    case state_intk::precise:
      intk.spin();
      break;
    case state_intk::hold:
      intk.stop(true);
      break;
    case state_intk::coast:
      intk.stop(false);
      break;
    }
    pros::delay(20);
  }
}

void trayControl(void *) {
  ControllerButton btn_tray_up(BTN_TRAY_UP);
  ControllerButton btn_tray_down(BTN_TRAY_DOWN);
  tray.setState(state_tray::moveDown);

  while (true) {
    if (btn_tray_up.changedToPressed()) {
      tray.setState(state_tray::moveUp);
    } else if (btn_tray_down.changedToPressed()) {
      tray.setState(state_tray::moveDown);
    } else if (btn_tray_up.changedToReleased() ||
               btn_tray_down.changedToReleased()) {
      tray.setState(state_tray::hold);
    }

    switch (tray.getState()) {
    case state_tray::moveUp:
      tray.limitSpeedTo(200.0);
      tray.setTarget(heights_tray::forward);
      tray.setState(state_tray::idle);
      break;
    case state_tray::moveDown:
      tray.limitSpeedTo(200.0);
      tray.setTarget(heights_tray::rest);
      tray.setState(state_tray::idle);
      break;
    case state_tray::lift:
      tray.limitSpeedTo(200.0);
      tray.setTarget(heights_tray::lifted);
      tray.setState(state_tray::idle);
      break;
    case state_tray::stack:
      tray.setTarget((double)heights_tray::vertical + 50);
      if (tray.isInSlowZone())
        tray.limitSpeedTo(100);
      break;
    case state_tray::hold:
      tray.setTarget(tray.getLocation());
      tray.setState(state_tray::idle);
      break;
    case state_tray::idle:
      pros::delay(10);
      break;
    }

    pros::delay(20);
  }
}

void liftControl(void *) {
  ControllerButton btn_lift_up(BTN_LIFT_UP);
  ControllerButton btn_lift_down(BTN_LIFT_DOWN);
  ControllerButton btn_lift_tower_low(BTN_LIFT_TOWER_LOW);
  ControllerButton btn_lift_tower_mid(BTN_LIFT_TOWER_MID);
  lift.setState(state_lift::hold);

  while (true) {
    if (btn_lift_up.changedToPressed()) {
      lift.setTarget(heights_lift::top);
      lift.setState(state_lift::moveToTarget);
    } else if (btn_lift_down.changedToPressed()) {
      lift.setTarget(heights_lift::bottom);
      lift.setState(state_lift::moveToTarget);
    } else if (btn_lift_tower_low.changedToPressed()) {
      lift.setTarget(heights_lift::lowTower);
      lift.setState(state_lift::moveToTarget);
    } else if (btn_lift_tower_mid.changedToPressed()) {
      lift.setTarget(heights_lift::midTower);
      lift.setState(state_lift::moveToTarget);
    } else if (btn_lift_up.changedToReleased() ||
               btn_lift_down.changedToReleased() ||
               btn_lift_tower_low.changedToReleased() ||
               btn_lift_tower_mid.changedToReleased()) {
      lift.setState(state_lift::brake);
    }
    // this section is to automatically raise the tray when the arms go up
    else if (lift.getLocation() > (double)heights_lift::raisedThreshold) {
      tray.setState(state_tray::lift);
    } else if (btn_lift_down.isPressed() &&
               lift.getLocation() < (double)heights_lift::raisedThreshold) {
      tray.setState(state_tray::moveDown);
    }

    switch (lift.getState()) {
    case state_lift::hold:
      lift.disable();
      lift.setState(state_lift::idle);
      break;
    case state_lift::moveToTarget:
      lift.enable();
      lift.setState(state_lift::idle);
      break;
    case state_lift::brake:
      lift.disable();
      lift.brake();
      lift.setState(state_lift::idle);
      break;
    case state_lift::rest:
      lift.rest();
      lift.setState(state_lift::idle);
      break;
    case state_lift::idle:
      pros::delay(10);
      break;
    }
    pros::delay(20);
  }
}

void mcroControl(void *) {
  ControllerButton btn_mcro_stack(BTN_MCRO_STACK);
  ControllerButton btn_mcro_reverse(BTN_MCRO_REVERSE);

  while (true) {
    if (btn_mcro_stack.changedToPressed()) {
      mcroStack(false);
    } else if (btn_mcro_reverse.changedToPressed()) {
      mcroStack(true);
    }

    pros::delay(50);
  }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  line_follower.get();
  tray.disable();
  pros::lcd::initialize();
  tray_motor.moveVelocity(-200);
  do {
    pros::delay(200);
  } while (tray_motor.getActualVelocity() != 0);
  tray.setBottom();
  tray.setTarget(heights_tray::rest);
  tray.enable();
  intk.setLineVal(line_follower.get());
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  enum autons { uRed9, uRed5, uBlue5, oneCube, progSkills, testing };
  autons auton = uRed9;
  switch (auton) {
  case uRed9:
    // 9Red - gets 9 cubes
    deploy();
    intk.spin(200);
    dvtn.ctrl.driveDistance(3_ft, 100.0);
    dvtn.ctrl.turnToFace(-35_deg, 30.0);
    dvtn.ctrl.driveDistance(-3.3_ft);
    dvtn.ctrl.turnToFace(0_deg, 30.0);
    dvtn.ctrl.driveDistance(3_ft, 45.0);
    dvtn.ctrl.turnToFace(-15_deg, 40.0);
    dvtn.ctrl.driveDistance(1_ft, 30.0);
    dvtn.ctrl.driveDistance(-2_ft, 100.0);
    dvtn.ctrl.turnToFace(150_deg);
    break;
  case uRed5:
    // 5Red - stacks 5 cubes
    intk.spin(-200);
    pros::delay(800);
    intk.spin(200);
    dvtn.ctrl.driveDistance(3_ft, 65.0);
    dvtn.ctrl.turnToFace(150_deg, 40.0);
    dvtn.ctrl.driveDistance(1.8_ft, 70.0);
    intk.spin(-50);
    pros::delay(800);
    intk.spin(0);
    mcroStack(false);
    pros::delay(800);
    mcroReverse();
    dvtn.ctrl.moveArcade(0.0, 0.0);
    break;
  case uBlue5:
    // 5blue - stacks 5 cubes
    intk.spin(-200);
    lift.setTarget(100);
    lift.waitForController();
    lift.setTarget(0);
    lift.waitForController();
    intk.spin(200);
    dvtn.ctrl.driveDistance(3_ft, 65.0);
    dvtn.ctrl.turnToFace(-150_deg, 40.0);
    dvtn.ctrl.driveDistance(1.9_ft, 70.0);
    intk.spin(-200);
    pros::delay(150);
    intk.spin(0);
    mcroStackAuton();
    break;
  case oneCube:
    dvtn.ctrl.moveArcade(50.0, 0.0);
    pros::delay(2000);
    dvtn.ctrl.moveArcade(-50.0, 0.0);
    pros::delay(3000);
    dvtn.ctrl.moveArcade(0.0, 0.0);
    deploy();
    break;
  case progSkills:
    // prgramming
    intk.spin(-200);
    lift.setTarget(100);
    lift.waitForController();
    lift.setTarget(0);
    lift.waitForController();
    intk.spin(200);
    dvtn.ctrl.driveDistance(3_ft, 65.0);
    dvtn.ctrl.driveDistance(-2.2_ft, 80.0);
    dvtn.ctrl.turnToFace(75_deg, 50.0);
    dvtn.ctrl.driveDistance(-2.4_ft, 50.0);
    dvtn.ctrl.turnToFace(0_deg, 30.0);
    dvtn.ctrl.driveDistance(3_ft, 45.0);
    dvtn.ctrl.turnToFace(-160_deg, 40.0);
    dvtn.ctrl.driveDistance(1.9_ft, 40.0);
    dvtn.ctrl.turnToFace(-140_deg, 30.0);
    dvtn.ctrl.driveDistance(5_in, 50.0);
    intk.spin(125.0);
    pros::delay(200);
    intk.spin(0);
    mcroStackNoRev();
    dvtn.ctrl.driveDistance(-3.2_ft, 50.0);
    dvtn.ctrl.turnToFace(0_deg, 50.0);
    tray.setTarget(heights_tray::bottom);
    intk.spin(200);
    dvtn.ctrl.driveDistance(2.5_ft, 50.0);
    pros::delay(2000);
    intk.spin(-200);
    pros::delay(150);
    intk.spin(0);
    dvtn.ctrl.driveDistance(-6_in, 50.0);
    lift.setTarget(heights_lift::lowTower);
    intk.spin(-200);
    pros::delay(2000);
    dvtn.ctrl.driveDistance(-3.2_ft, 50.0);
    dvtn.ctrl.turnToFace(90_deg, 50.0);
    dvtn.ctrl.driveDistance(2.8_ft, 50.0);
    pros::delay(2000);
    intk.spin(-200);
    pros::delay(150);
    intk.spin(0);
    dvtn.ctrl.driveDistance(-6_in, 50.0);
    lift.setTarget(heights_lift::midTower);
    dvtn.ctrl.driveDistance(1_in, 50.0);
    intk.spin(-200);
    pros::delay(2000);
    break;
  case testing:
    // stacks a bunch in the protected zone
    deploy();

    break;
  }
}

/**
 * Runs the operator control code. This function will be started in its own
 * task with the default priority and stack size whenever the robot is enabled
 * via the Field Management System or the VEX Competition Switch in the
 * operator control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart
 * the task, not resume it from where it left off.
 */
void opcontrol() {
  pros::Task intkTask(intkControl);
  pros::Task trayTask(trayControl);
  pros::Task liftTask(liftControl);
  pros::Task mcroTask(mcroControl);

  ControllerButton btn_dt_tgl_slew(BTN_DVTN_TGL_SLEW);
  dvtn.setState(state_dvtn::plain);
  while (true) {
    if (btn_dt_tgl_slew.changedToPressed()) {
      if (dvtn.getState() == state_dvtn::plain)
        dvtn.setState(state_dvtn::slew);
      else if (dvtn.getState() == state_dvtn::slew)
        dvtn.setState(state_dvtn::plain);
    }

    pros::lcd::print(1, "line_follower val: %f", line_follower.get());

    switch (dvtn.getState()) {
    case state_dvtn::plain:
      dvtn.updateArcade(con.getAnalog(ControllerAnalog::leftY) * 200,
                        con.getAnalog(ControllerAnalog::rightX) * 200, false);
      break;
    case state_dvtn::slew:
      dvtn.updateArcade(con.getAnalog(ControllerAnalog::leftY) * 200,
                        con.getAnalog(ControllerAnalog::rightX) * 200, true);
      break;
    case state_dvtn::off:
      dvtn.ctrl.stop();
      break;
    case state_dvtn::idle:
      pros::delay(20);
    }

    pros::delay(20);
  }
}
