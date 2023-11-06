#include "vex.h"

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 0.87, 0.75, 17, 0); // good enough, fix at school
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, 0.5, 0, 0, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

void drive_test(){
  chassis.drive_distance(6);
  chassis.drive_distance(12);
  chassis.drive_distance(18);
  chassis.drive_distance(-36);
}

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0,50, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(0,70, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(0,90, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(0,110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(0,130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_point(0, 18, 90);
  chassis.holonomic_drive_to_point(18, 0, 180);
  chassis.holonomic_drive_to_point(0, 18, 270);
  chassis.holonomic_drive_to_point(0, 0, 0);
}

void myAuton(){
  chassis.set_heading(0);
  chassis.drive_distance(10);
  chassis.turn_to_angle(180);

}
// it's called boring because its boring, we cant score very much
void BoringAuton(){
  default_constants();
  IntakeUp.set(true);

  //go forward

  //turn left

  //outtake triball

  //turn 180

  //drive forward, intake triball

  //drive forward, attempt to push other triball over

  //drive backwards, push alliance triball in

  //turn right ~35 degrees

  //drive forward, touch bar
}
//called FunAuton because it's fun, hopefully 5 ball auton + bar for quals
void FunAuton(){
  IntakeUp.set(false);

  //drive back
  
  //swing turn back right a little

  // deploy wings

  //swing turn back right the full 90 degrees

  //go backwards, push 2 triballs in, preload and one from matchload

  //go forwards, (maybe) swing turn forward right to face the middle triball

  //go forwards to the triball, almost touching

  //deploy wings, turn right, hopefully knocking middle triball

  //outtake triball

  //deploy wings, turn just over 180, go forward

  //intake triball

  //set_heading to 0

  //drive backwards full speed

  // drive forward, set_heading to 180

  //outtake, drive_forward

  // turn to bar, drive forward to touch bar
}

//it's called really fun because we get a lot of triballs hopefully :)
//hopefully 6 ball auton if pid is tuned well
//elims auton
void ReallyFunAuton(){
  //pretty much same thing as FunAuton, just don't go for bar and grab last triball
}