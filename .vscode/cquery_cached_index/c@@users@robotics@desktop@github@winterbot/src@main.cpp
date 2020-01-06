#include "main.h"

Controller con(ControllerId::master);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() { pros::lcd::initialize(); }

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
  tray.setState(state_tray::rest);

  while (true) {
    if (btn_tray_up.changedToPressed()) {
      tray.setTarget(heights_tray::vertical);
      tray.setState(state_tray::moveToTarget);
    } else if (btn_tray_down.changedToPressed()) {
      tray.setTarget(heights_tray::bottom);
      tray.setState(state_tray::moveToTarget);
    } else if (btn_tray_up.changedToReleased() ||
               btn_tray_down.changedToReleased()) {
      tray.setState(state_tray::brake);
    }

    switch (tray.getState()) {
    case state_tray::hold:
      tray.disable();
      tray.setState(state_tray::idle);
      break;
    case state_tray::moveToTarget:
      tray.enable();
      tray.setState(state_tray::idle);
      break;
    case state_tray::brake:
      tray.disable();
      tray.brake();
      tray.setState(state_tray::idle);
      break;
    case state_tray::rest:
      tray.rest();
      tray.setState(state_tray::idle);
      break;
    case state_tray::idle:
      pros::delay(10);
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

    switch (lift.getState()) {
    case state_lift::hold:
      lift.disable();
      lift.setState(state_lift::idle);
      printf("in state : hold\n");
      break;
    case state_lift::moveToTarget:
      lift.enable();
      lift.setState(state_lift::idle);
      printf("in state : moveToTarget\n");
      printf("is disabled? : %i", lift.isDisabled());
      break;
    case state_lift::brake:
      lift.disable();
      lift.brake();
      lift.setState(state_lift::idle);
      printf("in state : brake\n");
      printf("is disabled? : %i", lift.isDisabled());
      break;
    case state_lift::rest:
      lift.rest();
      lift.setState(state_lift::idle);
      printf("in state : rest\n");
      break;
    case state_lift::idle:
      pros::delay(10);
      printf("in state : idle\n");
      break;
    }
    pros::delay(20);
  }
}
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
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  pros::Task intkTask(intkControl);
  pros::Task trayTask(trayControl);
  pros::Task liftTask(liftControl);

  ControllerButton btn_dt_tgl_slew(BTN_DVTN_TGL_SLEW);
  dvtn.setState(state_dvtn::plain);
  while (true) {
    if (btn_dt_tgl_slew.changedToPressed()) {
      if (dvtn.getState() == state_dvtn::plain)
        dvtn.setState(state_dvtn::slew);
      else if (dvtn.getState() == state_dvtn::slew)
        dvtn.setState(state_dvtn::plain);
    }

    switch (dvtn.getState()) {
    case state_dvtn::plain:
      dvtn.updateArcade(con.getAnalog(ControllerAnalog::leftY),
                        con.getAnalog(ControllerAnalog::rightX), false);
      break;
    case state_dvtn::slew:
      dvtn.updateArcade(con.getAnalog(ControllerAnalog::leftY),
                        con.getAnalog(ControllerAnalog::rightX), true);
      break;
    case state_dvtn::off:
      dvtn.ctrl.stop();
    }

    pros::delay(20);
  }
}
