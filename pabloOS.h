#include "Presets.h"
// Include libraries for drawing to the OLED screen
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

// Include libraries for the stepper motors
#include <AccelStepper.h>
#include <AFMotor.h>

// Declare the motors (for AFMotor lib)
AF_Stepper motor1(2048, 1);
AF_Stepper motor2(2048, 2);

// These methods are used as 'wrappers' so that we can use 2 motor libraries together
// Note that each step can be SINGLE, DOUBLE, INTERLEAVE or MICROSTEP
void forwardstep1() {
  motor1.onestep(FORWARD, SINGLE);
}
void backwardstep1() {
  motor1.onestep(BACKWARD, SINGLE);
}
// wrappers for the second motor!
void forwardstep2() {
  motor2.onestep(BACKWARD, SINGLE);
}
void backwardstep2() {
  motor2.onestep(FORWARD, SINGLE);
}

// Declare the AccelStepper motors (which 'wrap' the AFMotor lib motors)
AccelStepper stepper_r(forwardstep1, backwardstep1);
AccelStepper stepper_l(forwardstep2, backwardstep2);

// These are settings captured by the UI settings
long setting_right_wheel_distance = 93;	// in mm
long setting_right_wheel_speed = 25;	// arbitrary scale
long setting_left_wheel_speed = 35;		// in mm
long setting_left_wheel_distance = 100;	// arbitrary scale

// button pin positions
int buttonIncThousands= 22;		// K0: 22
int buttonIncHundreds = 23;		// K1: 23
int buttonIncTens     = 24;		// K2: 24
int buttonIncOnes	  = 25;	 	// K3: 25

int buttonDrawingMode = 26;		// K4: 26
int buttonUnused = 27;			// K5: 27
int buttonPresets = 28;			// K6: 28
int buttonStart = 29;			// K7: 29

// toggle button states
int buttonDrawingMode_state = 0;

// Many values are required for the action of the rotary controllers
int rotaryEncoder1_set_clkPin = 49;
int rotaryEncoder1_set_dtPin = 47;
int rotaryEncoder1_set_btnPin = 45;
int rotaryEncoder1_read_clkPin;
int rotaryEncoder1_read_dtPin;
int rotaryEncoder1_previousRead_clkPin;

// Determines which of the 4 displayed values that the Rotary controller will modify
int rotaryMode = 0;
// holds the increment amount that the rotary controller uses
int rotary_increment = 1;
// current index of drawingMode
int drawingMode = 0;
// current index of preset array
int preset_index = -1;

