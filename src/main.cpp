/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Todd Rylaarsadm                                           */
/*    Created:      Sat Sep 07 2019                                           */
/*    Description:  TowerTakeover Competition Program for 4454A               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

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

//jumpers


//variables

//drive motors
float FLtemp = 0;
float FRtemp = 0;
float BLtemp = 0;
float BRtemp = 0;
float FLefficiency = 100;
float FRefficiency = 100;
float BLefficiency = 100;
float BRefficiency = 100;
//DR4B motors
float DR4BleftTemp = 0;
float DR4BrightTemp = 0;
float DR4BleftEfficiency = 100;
float DR4BrightEfficiency = 100;
//2bar motors
float left2barTemp = 0;
float right2barTemp = 0;
float left2barEfficiency = 100;
float right2barEfficiency = 100;
//claw motor
float clawTemp = 0;
float clawEfficiency = 100;
//intake motor
float intakeTemp = 0;
float intakeEfficiency = 100;

//failsafe code goes here. would apply in all circumstances
//variables for sanity. called continuously in task main of main.cpp
void variable_set() {

}

void brainDebugMode() {

}


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
    variable_set();
    
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(75);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}

