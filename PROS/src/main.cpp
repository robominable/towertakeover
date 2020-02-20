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
	pros::Motor Ldrive(1); //motor port declaration
	pros::Motor Rdrive(2); //motor port declaration
	pros::Motor Ltilter(3); //motor port declaration
	pros::Motor Rtilter(4); //motor port declaration
	pros::Motor Lintake(5); //motor port declaration
	pros::Motor Rintake(6); //motor port declaration
	pros::Motor Llift(7); //motor port declaration
	pros::Motor Rlift(8); //motor port declaration
	while (true) {
		//pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		//                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		//                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int left = master.get_analog(ANALOG_LEFT_Y); //sets joystick value to variable used for Ldrive control
		int right = master.get_analog(ANALOG_RIGHT_Y); //sets joystick value to variable used for Rdrive control
		float creep = 10; //virtual deadzone amount
		int tilterButtonUp = master.get_digital(DIGITAL_X); //tilter up button
		int tilterButtonDown = master.get_digital(DIGITAL_A); //tilter down button
		int tilterControl = 0; //tilter velocity value (set in later function)
		int tilterUpPower = 127; //speed to be set when tilterButtonUp is pressed
		int tilterDownPower = -127; //speed to be set when tilterButtonDown is pressed

		Ldrive.set_brake_mode(pros::E_MOTOR_BRAKE_COAST); //universal coast braketype for Ldrive
		Rdrive.set_brake_mode(pros::E_MOTOR_BRAKE_COAST); //universal coast braketype for Rdrive
		Ltilter.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD); //universal hold braketype for Ltilter
		Rtilter.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD); //universal hold braketype for Rtilter
		Lintake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD); //universal hold braketype for Lintake
		Rintake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD); //universal hold braketype for Rintake
		Llift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD); //universal hold braketype for Llift
		Rlift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD); //universal hold braketype for Rlift

		Ldrive.set_gearing(pros::E_MOTOR_GEARSET_18); //sets Ldrive encoder to use default cartridge
		Rdrive.set_gearing(pros::E_MOTOR_GEARSET_18); //sets Rdrive encoder to use default cartridge
		Ltilter.set_gearing(pros::E_MOTOR_GEARSET_36); //sets Ltilter encoder to use torque cartridge
		Rtilter.set_gearing(pros::E_MOTOR_GEARSET_36); //sets Rtilter encoder to use torque cartridge
		Lintake.set_gearing(pros::E_MOTOR_GEARSET_18); //sets Lintake encoder to use default cartridge
		Rintake.set_gearing(pros::E_MOTOR_GEARSET_18); //sets Rintake encoder to use default cartridge
		Llift.set_gearing(pros::E_MOTOR_GEARSET_36); //sets Llift encoder to use torque cartridge
		Rlift.set_gearing(pros::E_MOTOR_GEARSET_36); //sets Rlift encoder to use torque cartridge


		//power is multiplied by 1 for gearset_36, 2 for gearset_18, and 6 for gearset_06
		float Ldrive_power = 0; //is the variable that is used to set PID velocity control for Ldrive
		float Rdrive_power = 0; //is the variable that is used to set PID velocity control for Rdrive
		int Ltilter_power = 0; //is the variable that is used to set PID velocity control for Ltilter
		int Rtilter_power = 0; //is the variable that is used to set PID velocity control for Rtilter
		int Lintake_power = 0; //is the variable that is used to set PID velocity control for Lintake
		int Rintake_power = 0; //is the variable that is used to set PID velocity control for Rintake
		int Llift_power = 0; //is the variable that is used to set PID velocity control for Llift
		int Rlift_power = 0; //is the variable that is used to set PID velocity control for Rlift

		if(tilterButtonUp){
			tilterControl = tilterUpPower; //set tilter power to forward  at tilterUpPower amount
		}
		else if(tilterButtonDown){
			tilterControl = tilterDownPower; //set tilter power to backward at tilterDownPower amount
		}

		if(abs(left) > creep || abs(right) > creep){ //eliminate miscalibration in motors
			Ldrive.move(left); //move Ldrive
			Rdrive.move(right); //move Rdrive
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
