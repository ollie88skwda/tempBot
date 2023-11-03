using namespace vex;

extern brain Brain;

// VEXcode devices

extern motor LF;
extern motor LB;
extern motor RF;
extern motor RB;
extern motor RT;
extern motor LT;
extern inertial Inertial20;
extern controller Controller1;
extern limit CataLimit;
extern motor intake;
extern motor cata;
extern motor blocker;
extern digital_out IntakeUp;
extern digital_out wings;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );