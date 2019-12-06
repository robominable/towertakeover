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
vex::controller Controller = vex::controller(vex::controllerType::primary);

//motors
vex::motor FLdrive = vex::motor(PORT14, vex::gearSetting::ratio18_1, false); //ports may need to be changed later based on dead ports
vex::motor FRdrive = vex::motor(PORT13, vex::gearSetting::ratio18_1, true); //ports may need to be changed later based on dead ports
vex::motor DR4B1 = vex::motor(PORT15, vex::gearSetting::ratio36_1, false);
vex::motor DR4B2 = vex::motor(PORT18, vex::gearSetting::ratio36_1, true);
vex::motor liftMotor = vex::motor(PORT20, vex::gearSetting::ratio36_1, true);
vex::motor intakeL = vex::motor(PORT12, vex::gearSetting::ratio6_1, false);
vex::motor clawMotor = vex::motor(PORT19, vex::gearSetting::ratio18_1, true);
vex::motor intakeR = vex::motor(PORT21, vex::gearSetting::ratio6_1, true);
vex::motor_group DR4B( DR4B1, DR4B2);
vex::motor_group intake( intakeL, intakeR );
//sensors

//jumpers
//vex::digital_in brainDebug = vex::digital_in(vex::triport::A, vex::triportType::digitalInput); //idk wth is going on here, triport errors galore

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
float DR4Btemp = 0;
float DR4Befficiency = 100;
//2bar motors
float liftTemp = 0;
float liftEfficiency = 100;
//claw motor
float clawTemp = 0;
float clawEfficiency = 100;
//intake motor
float intakeTemp = 0;
float intakeEfficiency = 100;

//controller setup
bool backButtonToggle = true;
bool upDownButtonToggle = true;
bool leftRightButtonToggle = true;

//auton setup
uint32_t loopCount = 12*1000;
uint8_t     myTestData[15000];
uint8_t     myReadBuffer[15000];
int nWritten = 0;

//failsafe code goes here. would apply in all circumstances
//variables for sanity. called continuously in task main of main.cpp
void variable_set() {
  //drive variables
  FLtemp = FLdrive.temperature(percentUnits::pct);
  FRtemp = FRdrive.temperature(percentUnits::pct);
  FLefficiency = FLdrive.efficiency(percentUnits::pct);
  FRefficiency = FRdrive.efficiency(percentUnits::pct);
  //DR4B variables
  DR4Btemp = DR4B.temperature(percentUnits::pct);
  DR4Befficiency = DR4B.efficiency(percentUnits::pct);
  //2bar variables
  liftTemp = liftMotor.temperature(percentUnits::pct);
  liftEfficiency = liftMotor.efficiency(percentUnits::pct);
  //claw variables
  clawTemp = clawMotor.temperature(percentUnits::pct);
  clawEfficiency = clawMotor.efficiency(percentUnits::pct);

}

void brainDebugMode() {

}


void pre_auton( void ) {
  
}

void autonomous( void ) {
  int nRead = Brain.SDcard.loadfile( "test.txt", myReadBuffer, sizeof(myReadBuffer) );

        // display on screen how many bytes we read
        Brain.Screen.setCursor( 3, 2 );
        Brain.Screen.print( "We read %d bytes from the SD Card", nRead );

        // and display some of the data
        Brain.Screen.setCursor( 6, 2 );
        for(int i=0;i<8;i++)
            Brain.Screen.print("%i ", myReadBuffer[i]);

    for(int i=0;i<loopCount;i=i+12)
    {
      if((int)myReadBuffer[i+0]){
        FLdrive.spin(forward, (int)myReadBuffer[i+0], pct);
      }
      
      if((int)myReadBuffer[i+3]){
        FLdrive.spin(reverse, ((float)myReadBuffer[i+3]), pct);
      }
      
      //else{
      //  Lmotor.stop();
      //}

      if((int)myReadBuffer[i+1]){
        FRdrive.spin(forward, (int)myReadBuffer[i+1], pct);
      }
      
      if((int)myReadBuffer[i+4]){
        FRdrive.spin(reverse, ((float)myReadBuffer[i+4]), pct);
      }
      //else {
      //  Rmotor.stop();
      //}

      if((int)myReadBuffer[i+2]){
        DR4B.spin(forward, (int)myReadBuffer[i+2], pct);
      }
      else if((int)myReadBuffer[i+5]){
        DR4B.spin(reverse, (int)myReadBuffer[i+5], pct);
      }
      else{
        DR4B.stop();
      }
      //else {
        //Lift.stop(brakeType::brake);
      //}      
      vex::task::sleep(15);
  

    }
}

void usercontrol( void ) {
  while (1) {
    int creep;
        creep = float(0.05);
        if (Controller.Axis3.position(vex::percentUnits::pct) > creep || Controller.Axis3.position(vex::percentUnits::pct) < -creep){
            FLdrive.spin(vex::directionType::fwd,(Controller.Axis3.position(vex::percentUnits::pct)),vex::velocityUnits::pct);
        }
            else{
                FLdrive.stop();
            }
        if (Controller.Axis2.position(vex::percentUnits::pct) > creep || Controller.Axis2.position(vex::percentUnits::pct) < -creep){
            FRdrive.spin(vex::directionType::fwd,(Controller.Axis2.position(vex::percentUnits::pct)),vex::velocityUnits::pct);
        }
            else{
                FRdrive.stop();
              }
    if(Controller.ButtonA.pressing() == 1){
      liftMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
      else if(Controller.ButtonX.pressing() == 1){
        liftMotor.spin(vex::directionType::rev, 100, vex::percentUnits::pct);
      }
      else{
        liftMotor.stop(vex::brakeType::hold);
      }
    
    if(Controller.ButtonR1.pressing() == 1){
      DR4B.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
      else if(Controller.ButtonR2.pressing() == 1){
        DR4B.spin(vex::directionType::rev, 30, vex::percentUnits::pct);
      }
      else{
        DR4B.stop(vex::brakeType::hold);
      }
    if(Controller.ButtonL1.pressing() == 1){
      clawMotor.spin(vex::directionType::fwd, 75, vex::percentUnits::pct);
    }
      else if(Controller.ButtonL2.pressing() == 1){
        clawMotor.spin(vex::directionType::rev, 75, vex::percentUnits::pct);
      }
      else{
        clawMotor.stop(vex::brakeType::hold);
      }
    if(Controller.ButtonRight.pressing() == 1){
    intake.spin(vex::directionType::fwd, 75, vex::percentUnits::pct);
  }
    else if(Controller.ButtonLeft.pressing() == 1){
      intake.spin(vex::directionType::rev, 75, vex::percentUnits::pct);
    }
    else if(Controller.ButtonDown.pressing() == 1){
      intake.stop(vex::brakeType::hold);
    }
    vex::task::sleep(10);
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

