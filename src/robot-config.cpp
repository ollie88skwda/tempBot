#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LF = motor(PORT1, ratio6_1, true);
motor LB = motor(PORT2, ratio6_1, true);
motor RF = motor(PORT4, ratio6_1, false);
motor RB = motor(PORT5, ratio6_1, false);
motor LT = motor(PORT3, ratio6_1, false);
motor RT = motor(PORT6, ratio6_1, true);
inertial Inertial20 = inertial(PORT20);
controller Controller1 = controller(primary);
limit CataLimit = limit(Brain.ThreeWirePort.B);
motor intake = motor(PORT7, ratio18_1, true);
motor cata = motor(PORT9, ratio36_1, true);
motor blocker = motor(PORT8, ratio18_1, true);
digital_out IntakeUp = digital_out(Brain.ThreeWirePort.C);
digital_out wingLeft = digital_out(Brain.ThreeWirePort.E);
digital_out wingRight = digital_out(Brain.ThreeWirePort.F);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}