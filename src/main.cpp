#include "vex.h"
using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors using the V5 port icon in the top right of the screen. Doing     */
/*  so will update robot-config.cpp and robot-config.h automatically, so     */
/*  you don't have to. Ensure that your motors are reversed properly. For    */
/*  the drive, spinning all motors forward should drive the robot forward.   */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your robot manually with the sidebar configurer. */
/*---------------------------------------------------------------------------*/
bool IntakeIsUp = false;
Drive chassis(

    // Specify your drive setup below. There are eight options:
    // ZERO_TRACKER_NO_ODOM, ZERO_TRACKER_ODOM, TANK_ONE_ENCODER, TANK_ONE_ROTATION, TANK_TWO_ENCODER, TANK_TWO_ROTATION, HOLONOMIC_TWO_ENCODER, and HOLONOMIC_TWO_ROTATION
    // For example, if you are not using odometry, put ZERO_TRACKER_NO_ODOM below:
    ZERO_TRACKER_NO_ODOM,

    // Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
    // You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

    // Left Motors:
    motor_group(LF, LB, LT),

    // Right Motors:
    motor_group(RF, RB, RT),

    // Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
    PORT17,

    // Input your wheel diameter. (4" omnis are actually closer to 4.125"):
    3.25,

    // External ratio, must be in decimal, in the format of input teeth/output teeth.
    // If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
    // If the motor drives the wheel directly, this value is 1:
    0.6,

    // Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
    // For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
    360,

    /*---------------------------------------------------------------------------*/
    /*                                  PAUSE!                                   */
    /*                                                                           */
    /*  The rest of the drive constructor is for robots using POSITION TRACKING. */
    /*  If you are not using position tracking, leave the rest of the values as  */
    /*  they are.                                                                */
    /*---------------------------------------------------------------------------*/

    // If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

    // FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
    // LF:      //RF:
    PORT1, -PORT2,

    // LB:      //RB:
    PORT3, -PORT4,

    // If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
    // If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
    // If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
    3,

    // Input the Forward Tracker diameter (reverse it to make the direction switch):
    2.75,

    // Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
    // For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
    // This distance is in inches:
    -2,

    // Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
    1,

    // Sideways tracker diameter (reverse to make the direction switch):
    -2.75,

    // Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
    5.5

);

int current_auton_selection = 0;
bool auto_started = false;

void autonSelector(){
  Controller1.Screen.setCursor(3,4);
  switch(current_auton_selection){       //Tap the brain screen to cycle through autons.
      case 0:
        Brain.Screen.printAt(180, 120, "Goal Side");
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("Goal Side");
        break;
      case 1:
        Brain.Screen.printAt(180, 120, "Bar Side");
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("Bar Side");
        break;
      
      case 2:
        Brain.Screen.printAt(180, 120, "Skills");
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("Skills");
        break;
        /*
      case 3:
        Brain.Screen.printAt(180, 120, "Opp Side Blue");
        //controllerPTOUpdate();
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("Opp Side Blue");
        break;
  
      case 4:
        Brain.Screen.printAt(180,120, "Skills");
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("Skills");*/
    }
    if(Brain.Screen.pressing()){
      while(Brain.Screen.pressing()) {}
      Brain.Screen.clearScreen();
      current_auton_selection ++;
      Controller1.Screen.clearLine(3);
    
    } else if (current_auton_selection == 3){
      current_auton_selection = 0;
    } /*else if (Controller1.ButtonY.pressing() && Controller1.ButtonRight.pressing()){
      current_auton_selection ++;
      Brain.Screen.clearScreen();
    }*/
    wait(50, msec);
}

void printMotorTemps(){
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Chassis:");
  Brain.Screen.newLine();
  Brain.Screen.print(LF.temperature(percent));
  Brain.Screen.setCursor(2, 8);
  Brain.Screen.print(LB.temperature(percent));
  Brain.Screen.setCursor(2, 16);
  Brain.Screen.print(LT.temperature(percent));
  Brain.Screen.setCursor(2, 24);
  Brain.Screen.print(RF.temperature(percent));
  Brain.Screen.setCursor(2, 32);
  Brain.Screen.print(RB.temperature(percent));
  Brain.Screen.setCursor(2, 40);
  Brain.Screen.print(RT.temperature(percent));
  Brain.Screen.newLine();
  Brain.Screen.print("Lift:");
  Brain.Screen.newLine();
  Brain.Screen.print(lift.temperature(percent));
  Brain.Screen.newLine();
  Brain.Screen.print("Intake:");
  Brain.Screen.newLine();
  Brain.Screen.print(intake.temperature(percent));
  Brain.Screen.newLine();
  Brain.Screen.print("Cata:");
  Brain.Screen.newLine();
  Brain.Screen.print(cata.temperature(percent));
}

void brainScreenPrint(){
  switch(brainCurrentScreen){
    case 0:
      autonSelector();
      //Brain.Screen.printAt(50,50,"hello");
      break;
    case 1:
    //Brain Image
      Brain.Screen.drawImageFromFile("file.png", 0, 0);
      break;
    case 2:
    //motor temps
    printMotorTemps();
    break;
  }
  if(Controller1.ButtonRight.pressing() && !Controller1.ButtonY.pressing()){
    while(Controller1.ButtonRight.pressing());
    Brain.Screen.clearScreen();
    brainCurrentScreen++;
  }

  if (brainCurrentScreen == 3){
    Brain.Screen.clearScreen();
    brainCurrentScreen = 0;
  }
}

void pre_auton(void)
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();
  while (auto_started == false)
  {                             // Changing the names below will only change their names on the
    Brain.Screen.clearScreen(); // brain screen for auton selection.
    brainScreenPrint();
    task::sleep(10);
  }
}

void autonomous(void)
{
  auto_started = true;
  switch (current_auton_selection)
  {
  case 0:
    turn_test(); // This is the default auton, if you don't select from the brain.
    break;        // Change these to be your own auton functions in order to use the auton selector.
  case 1:         // Tap the screen to cycle through autons.
    BoringAuton();
    break;
  // case 2:
  //   turn_test();
  //   break;
  // case 3:
  //   swing_test();
  //   break;
  // case 4:
  //   full_test();
  //   break;
  // case 5:
  //   odom_test();
  //   break;
  // case 6:
  //   tank_odom_test();
  //   break;
  // case 7:
  //   holonomic_odom_test();
  //   break;
  }
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


void usercontrol(void)
{
  // User control code here, inside the loop
  while (1)
  {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    chassis.DriveL.setStopping(brakeType::coast);
    chassis.DriveR.setStopping(brakeType::coast);
    // ........................................................................

    // Replace this line with chassis.control_tank(); for tank drive
    // or chassis.control_holonomic(); for holo drive.
    chassis.control_arcade();

    // code
    if(Controller1.ButtonL1.pressing()){
      //Blocker Up
      blocker.spin(fwd, 100, percent);
    }else if (Controller1.ButtonL2.pressing()){
      //Blocker Down
      blocker.spin(reverse, 100, percent);
    }else if ((!Controller1.ButtonL1.pressing() && !Controller1.ButtonL2.pressing())) {
      blocker.stop(brakeType::hold);
    }

    //blocker
    if (Controller1.ButtonUp.pressing()){
      blocker.spin(reverse, 100, percent);
    }else if (Controller1.ButtonDown.pressing()){
      blocker.spin(fwd, 100, percent);
    }else if ((!Controller1.ButtonUp.pressing() && !Controller1.ButtonDown.pressing())){
      blocker.stop(brakeType::hold);
    }
    
    // intake piston up
    if (Controller1.ButtonX.pressing()){
      IntakeUp.set(!IntakeUp);
      IntakeIsUp = IntakeUp;
      while (Controller1.ButtonX.pressing()){} //these are to prevent it from firing forever on one press
    }
    
    if (Controller1.ButtonA.pressing()){
      IntakeUp.set(!IntakeUp);
      IntakeIsUp = IntakeUp;
      while (Controller1.ButtonA.pressing()){}
    }

    //intake motor intakes in
    if (Controller1.ButtonR1.pressing()){
      intake.spin(reverse, 100, percent);
    }else if (Controller1.ButtonR2.pressing()){
      //intake motor out
      intake.spin(fwd, 100, percent);
    }else if (IntakeIsUp == true && !Controller1.ButtonR2.pressing() && !Controller1.ButtonR1.pressing()){
      // intake motor out if intake is up
      intake.spin(fwd, 100, percent);
    }else if (IntakeIsUp == false && !Controller1.ButtonR2.pressing() && !Controller1.ButtonR1.pressing()){
      intake.spin(reverse, 100, percent);
    }else{
      // else statement, probably should never be used
      intake.spin(reverse, 100, percent);
    }

    // wings
    // wings left
    if (Controller1.ButtonLeft.pressing()){
      wingLeft.set(!wingLeft);
      while(Controller1.ButtonLeft.pressing()){};
    }

    //wings right
    if (Controller1.ButtonRight.pressing()){
      wingRight.set(!wingRight);
    while(Controller1.ButtonRight.pressing()){};
    }

    //both wings
    if (Controller1.ButtonY.pressing()){
      wingLeft.set(!wingLeft);
      wingRight.set(!wingRight);
       while(Controller1.ButtonY.pressing()){};
    }

    //cata
    if (!CataLimit.pressing() && !Controller1.ButtonB.pressing()){
      cata.spin(fwd, 100, percent);
    }else if (CataLimit.pressing() && !Controller1.ButtonB.pressing()){
      cata.stop(brakeType::hold);
      chassis.DriveL.setStopping(brakeType::coast);
      chassis.DriveR.setStopping(brakeType::coast);
    }else if (CataLimit.pressing() && Controller1.ButtonB.pressing()){
      cata.spin(fwd, 100, percent);
      //hold bot in place while matchloading
      chassis.DriveL.setStopping(brakeType::hold);
      chassis.DriveR.setStopping(brakeType::hold);
    }

    //hold in place
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    wait(100, msec);
  }
}
