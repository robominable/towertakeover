#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello Robominable!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {

}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

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
void autonomous() {

}

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
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor Ldrive(1);
	pros::Motor Rdrive(2);
	pros::Motor Ltilter(3);
	pros::Motor Rtilter(4);
	pros::Motor Lintake(5);
	pros::Motor Rintake(6);
	pros::Motor Llift(7);
	pros::Motor Rlift(8);
	while (true) {
		//pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		//                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		//                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);
		float creep = 10;
		int tilterButtonUp = master.get_digital(DIGITAL_X);
		int tilterButtonDown = master.get_digital(DIGITAL_A);
		int tilterControl = 0;
		int tilterUpPower = 127;
		int tilterDownPower = -127;

		Ldrive.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		Rdrive.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		Ltilter.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		Rtilter.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		Lintake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		Rintake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		Llift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		Rlift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

		if(tilterButtonUp){
			tilterControl = tilterUpPower;
		}
		else if(tilterButtonDown){
			tilterControl = tilterDownPower;
		}

		if(abs(left) > creep || abs(right) > creep){
			Ldrive.move(left);
			Rdrive.move(right);
	  }
		else{}

		if(tilterControl==127){
			Ltilter.move(tilterControl);
			Rtilter.move(tilterControl);
		}
		else if(tilterControl==-127){
			Ltilter.move(tilterControl);
			Rtilter.move(tilterControl);
		}
		else{
			Ltilter.move_velocity(0);
			Rtilter.move_velocity(0);
		}

		pros::delay(20);
	}
}
