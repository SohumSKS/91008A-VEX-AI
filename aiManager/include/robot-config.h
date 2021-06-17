#pragma once

using namespace vex;

extern brain Brain;
enum State{STATE_STARTUP,STATE_SEARCHING,STATE_COLLECTING,STATE_SCORING,STATE_DONE};

// VEXcode devices
extern motor leftIntake;
extern motor rightIntake;
extern motor bottomRoller;
extern motor topRoller;
extern motor drive_left;
extern motor drive_right;
extern encoder leftEncoder;
extern encoder rightEncoder;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );