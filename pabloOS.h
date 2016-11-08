#include "Presets.h"
// Include libraries for drawing to the OLED screen
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

// Include libraries for the stepper motors
#include <AccelStepper.h>
#include <AFMotor.h>

// ==================================================================
// START: motor stuff

const int MOTOR_STEPS = 2048;

// wheel diameter of robot
const float WHEEL_DIAMETER = 79;

// Default configurations for stepper motor control
const float MAX_SPEED = 400;
const float ACCELERATION = 100;


// Declare the motors (for AFMotor lib)
AF_Stepper motorRight(MOTOR_STEPS, 1);
AF_Stepper motorLeft(MOTOR_STEPS, 2);

// These methods are used as 'wrappers' so that we can use 2 motor libraries together
// Note that each step can be SINGLE, DOUBLE, INTERLEAVE or MICROSTEP
void forwardStepRight() {
  motorRight.onestep(FORWARD, SINGLE);
}
void backwardStepRight() {
  motorRight.onestep(BACKWARD, SINGLE);
}
// wrappers for the second motor!
void forwardStepLeft() {
  motorLeft.onestep(BACKWARD, SINGLE);
}
void backwardStepLeft() {
  motorLeft.onestep(FORWARD, SINGLE);
}

// Declare the AccelStepper motors (which 'wrap' the AFMotor lib motors)
AccelStepper stepperRight(forwardStepRight, backwardStepRight);
AccelStepper stepperLeft(forwardStepLeft, backwardStepLeft);

// These are settings captured by the UI settings
long setting_right_wheel_distance = 93;	// in mm
long setting_right_wheel_speed = 25;	// arbitrary scale
long setting_left_wheel_speed = 35;		// in mm
long setting_left_wheel_distance = 100;	// arbitrary scale



//  END:  motor stuff
// ==================================================================
// START: physical UI


// button pin positions
byte buttonIncThousands= 22;		// K0: 22
byte buttonIncHundreds = 23;		// K1: 23
byte buttonIncTens     = 24;		// K2: 24
byte buttonIncOnes	  = 25;	 	// K3: 25

byte buttonDrawingMode = 26;		// K4: 26
byte buttonUnused = 27;			// K5: 27
byte buttonPresets = 28;			// K6: 28
byte buttonStart = 29;			// K7: 29

// toggle button states
int buttonDrawingMode_state = 0;

// Many values are required for the action of the rotary controllers
byte rotaryEncoderClkPin = 49;
byte rotaryEncoderDtPin = 47;
byte rotaryEncoderBtnPin = 45;
int rotaryEncoderClkValue;
int rotaryEncoderDtValue;
int rotaryEncoderClkValuePrevious;

// Determines which of the 4 displayed values that the Rotary controller will modify
int rotaryMode = 0;
// holds the increment amount that the rotary controller uses
int rotaryIncrement = 1;
// current index of drawingMode
int drawingMode = 0;
// current index of preset array
int presetIndex = -1;



//  END:  physical UI
// ==================================================================

