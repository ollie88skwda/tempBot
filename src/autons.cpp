#include "vex.h"

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(12, 2, 0.1, 12, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, 0.7, 0.05, 2.7, 15);
  chassis.set_swing_constants(12, 1, 0.005, 2.4, 15);

  // Each exit condition set is in the form (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 3000);
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
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print(Inertial17.angle());
  chassis.turn_to_angle(30);
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print(Inertial17.angle());
  chassis.turn_to_angle(90);
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print(Inertial17.angle());
  chassis.turn_to_angle(225);
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print(Inertial17.angle());
  chassis.turn_to_angle(0);
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print(Inertial17.angle());
}

void swing_test(){
  chassis.left_swing_to_angle(90);
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print(Inertial17.angle());
  chassis.right_swing_to_angle(0);
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print(Inertial17.angle());
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
  chassis.turn_to_angle(180);
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print(Inertial17.angle());
  chassis.turn_to_angle(0);
  
}
// it's called boring because its boring, we cant score very much
void BoringAuton(){
  // set velocities
  blocker.setVelocity(75, percent);
  intake.setVelocity(100, percent);

  //set blocker up so doesn't get stuck
  blocker.spinFor(-100, degrees, false);

  //drive forward and back to take out with wings
  chassis.drive_distance(10);
  wingLeft.set(true);
  chassis.drive_distance(-10);
  chassis.turn_to_angle(-20);
  chassis.turn_to_angle(0);
  wingLeft.set(false);

  //drive forward, swing turn
  chassis.drive_distance(8);
  chassis.left_swing_to_angle(45);

  //push ball in and come back out
  chassis.drive_distance(18);
  chassis.drive_distance(-6);

  //drive to get ready to get middle ball
  chassis.turn_to_angle(135);
  chassis.drive_distance(35);
  chassis.turn_to_angle(45);

  //prepare to intake
  IntakeUp.set(true);
  intake.spin(reverse);

  //get ball
  chassis.drive_distance(29);
  chassis.drive_distance(-5);

  //score for other side
  chassis.turn_to_angle(135);
  intake.spin(forward);
  IntakeUp.set(false);
  chassis.drive_distance(15.5);
  chassis.drive_distance(-15);

  //touch bar
  blocker.spinFor(-385, degrees, false);
  chassis.turn_to_angle(15);
  chassis.drive_distance(-25);


  /*
  intake.setVelocity(69, percent);
  blocker.setVelocity(50, percent);
  blocker.spinTo(-50, degrees);
  IntakeUp.set(true);
  wait(0.5, seconds);
  // blocker.spinFor(100, deg);
  // intake.spinFor(240, deg);
  // IntakeUp.set(false);
  chassis.drive_distance(27, 3);
  chassis.drive_distance(-18);
  chassis.right_swing_to_angle(65);
  IntakeUp.set(true);
  // wait(0.25, seconds);
  chassis.drive_distance(6);
  blocker.spinTo(-605, deg);
  // wait(0.25, seconds);
  chassis.drive_distance(-3);
  blocker.spinTo(-665, deg);
  // IntakeUp.set(false);
  chassis.drive_distance(45);
  blocker.spinTo(-505, deg);
  chassis.turn_to_angle(-20);
  chassis.drive_distance(-17);
  // intake.spin(reverse);
  // IntakeUp.set(true);
  // wait(.1, seconds);
  // intake.stop();
  // chassis.right_swing_to_angle(-70);
  */



}
//called FunAuton because it's fun, hopefully 5 ball auton + bar for quals
void FunAuton(){
  IntakeUp.set(true);
  intake.setVelocity(100, percent);
  chassis.drive_distance(-20);
  chassis.left_swing_to_angle(110);
  intake.spin(reverse);
  chassis.drive_distance(40);
  // IntakeUp.set(true);
  // chassis.drive_distance(2);
  wait(0.5, seconds);
  chassis.turn_to_angle(-105);
  chassis.drive_distance(3);
  intake.stop();
  IntakeUp.set(false);
  chassis.drive_distance(7, -115);
  wait(0.25, seconds);
  chassis.turn_to_angle(180);
  IntakeUp.set(true);
  intake.spin(reverse);
  chassis.drive_distance(5);
  chassis.turn_to_angle(-90);
  IntakeUp.set(false);
  chassis.turn_to_angle(90);
  wingLeft.set(false);
  wingRight.set(false);
  chassis.drive_distance(-25);
  blocker.spinFor(-300, degrees, false);
  chassis.drive_distance(10);
  chassis.turn_to_angle(-135);
  chassis.drive_distance(-30);
  
}

//it's called really fun because we get a lot of triballs hopefully :)
//hopefully 6 ball auton if pid is tuned well
//elims auton
void ReallyFunAuton(){
  //pretty much same thing as FunAuton, just don't go for bar and grab last triball
}