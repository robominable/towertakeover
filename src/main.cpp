/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Todd Rylaarsadm                                           */
/*    Created:      Sat Sep 07 2019                                           */
/*    Description:  TowerTakeover Competition Program for 4454A               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "auton.cpp"
#include "failsafes.cpp"
#include "definitions.cpp"

using namespace vex;

//basic inits
vex::brain       Brain;
vex::competition Competition;
vex::controller controller = vex::controller(vex::controllerType::primary);

//motors
vex::motor FLdrive = vex::motor(PORT1, vex::gearSetting::ratio18_1, false); //ports may need to be changed later based on dead ports
vex::motor FRdrive = vex::motor(PORT2, vex::gearSetting::ratio18_1, true); //ports may need to be changed later based on dead ports
vex::motor BLdrive = vex::motor(PORT3, vex::gearSetting::ratio18_1, false); //ports may need to be changed later based on dead ports
vex::motor BRdrive = vex::motor(PORT4, vex::gearSetting::ratio18_1, true); //ports may need to be changed later based on dead ports 
vex::motor LeftTray = vex::motor(PORT6, vex::gearSetting::ratio36_1, false); //ports may need to be changed later based on dead ports
vex::motor RightTray = vex::motor(PORT7, vex::gearSetting::ratio36_1, false); //ports may need to be changed later based on dead ports

//sensors


void pre_auton( void ) {
  
}

void autonomous( void ) {
  
}

void usercontrol( void ) {
  while (1) {
 
    vex::task::sleep(20);
  }
}

int main() {
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}
