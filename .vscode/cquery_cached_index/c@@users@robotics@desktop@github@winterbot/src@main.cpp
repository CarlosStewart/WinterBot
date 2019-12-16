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

void dvtnControl(void *) {
  ControllerButton btn_dt_tgl_slew(BTN_DVTN_TGL_SLEW);

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
  }
}

void intkControl(void *) {
  ControllerButton btn_intk_tgl(BTN_INTK_TGL);
  ControllerButton btn_intk_in(BTN_INTK_IN);
  ControllerButton btn_intk_out(BTN_INTK_OUT);

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
  while (true) {
    pros::delay(20);
  }
}
