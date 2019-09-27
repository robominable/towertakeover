/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Todd Rylaarsadm                                           */
/*    Created:      Sat Sep 07 2019                                           */
/*    Description:  TowerTakeover Competition Program for 4454A               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "auton.cpp"
#include "failsafes.cpp"
#include "definitions.h"

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
