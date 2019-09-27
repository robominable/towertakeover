//all definitions go here
//basic inits
#include "vex.h"
using namespace vex;

vex::brain       Brain;
vex::competition Competition;
vex::controller controller = vex::controller(vex::controllerType::primary);

//motors
vex::motor FLdrive = vex::motor(PORT1, vex::gearSetting::ratio18_1, false); //ports may need to be changed later based on dead ports
vex::motor FRdrive = vex::motor(PORT2, vex::gearSetting::ratio18_1, true); //ports may need to be changed later based on dead ports
vex::motor BLdrive = vex::motor(PORT3, vex::gearSetting::ratio18_1, false); //ports may need to be changed later based on dead ports
vex::motor BRdrive = vex::motor(PORT4, vex::gearSetting::ratio18_1, true); //ports may need to be changed later based on dead ports 

//sensors
