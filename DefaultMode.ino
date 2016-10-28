// Allows knowing if the steppers are currently activated or just waiting.
boolean isDrawing = false;

void setup()
{
  setupDisplay();  
  setupRotaryEncoder();
  setupButtons();
}

void loop(){
  
  // check which mode we are
  if (drawingMode == 0) {
    default_mode();
  } else if ( drawingMode == 1) {
    customDrawingMode();
    report(); // this ensures that the screen re-displays what is going on in default mode
  }

}

void default_mode(){

  if (!isDrawing) {
    readRotaryEncoders();

    // Choose parameter. This controls which value will be modified by the knob
    if (digitalRead(rotaryEncoder1_set_btnPin) == LOW) {
      rotaryMode = (rotaryMode + 1) % 4;
      report();
      delay(300);
    }

    // Choose drawingMode
    readModeButton();

    // Change increment.
    if (digitalRead(buttonIncThousands) == LOW) {
      rotary_increment = 1000; report();
      // cycleRotaryIncrement();
    } else if (digitalRead(buttonIncHundreds) == LOW){
      rotary_increment = 100; report();
    } else if (digitalRead(buttonIncTens) == LOW){
      rotary_increment = 10; report();
    } else if (digitalRead(buttonIncOnes) == LOW){
      rotary_increment = 1; report();
    }

    // Choose preset
    if (digitalRead(buttonPresets) == LOW) {
      // increment preset_index
      preset_index = preset_index + 1;

      // check if at end of preset length, wrap
      if (preset_index >= (sizeof (presets) / sizeof (*presets)) ){
        preset_index = 0;
      }

      // make sure preset values are captured
      setting_left_wheel_distance = presets[preset_index][0]; 
      setting_left_wheel_speed = presets[preset_index][1];   // in mm
      setting_right_wheel_speed = presets[preset_index][2];  // arbitrary scale
      setting_right_wheel_distance = presets[preset_index][3]; // in mm

      report();
      delay(200);
    }

    // Push to start
    if (digitalRead(buttonStart) == LOW) {
      isDrawing = true;
      displayStartMessage();
      captureSettings();
      report();
    }

  } else {

    // Bounce the right wheel direction
    if (stepper_r.distanceToGo() == 0) {
      stepper_r.moveTo(-stepper_r.currentPosition());
    }

    // Bounce the left wheel direction
    if (stepper_l.distanceToGo() == 0) {
      stepper_l.moveTo(-stepper_l.currentPosition());
    }

    // Look for stop button
    if (digitalRead(buttonStart) == LOW) {
      messageLarge("Stop!");
      stopAndResetSteppers();
      report();
    }

    // Go!
    stepper_r.run();
    stepper_l.run();

  }
}

/*
 * Waits for start button to be pressed
 */
bool waitForStartButton(){
  return (digitalRead(buttonStart) == HIGH);
}


void readModeButton(){
  if ( digitalRead(buttonDrawingMode) == LOW ) {
    // mode button pressed

    if ( buttonDrawingMode_state == 0) {
      // if we get here then it is a fresh push
      
      buttonDrawingMode_state = 1;
      drawingMode ++;
      if (drawingMode > 1) drawingMode = 0;
    } 

  } else {
    // mode button unpressed, 
    buttonDrawingMode_state = 0;
  }
}
