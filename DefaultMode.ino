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
    if (digitalRead(rotaryEncoderBtnPin) == LOW) {
      rotaryMode = (rotaryMode + 1) % 4;
      report();
      delay(300);
    }

    // Choose drawingMode
    readModeButton();

    // Change increment.
    if (digitalRead(buttonIncThousands) == LOW) {
      rotaryIncrement = 1000; report();
      // cycleRotaryIncrement();
    } else if (digitalRead(buttonIncHundreds) == LOW){
      rotaryIncrement = 100; report();
    } else if (digitalRead(buttonIncTens) == LOW){
      rotaryIncrement = 10; report();
    } else if (digitalRead(buttonIncOnes) == LOW){
      rotaryIncrement = 1; report();
    }

    // Choose preset
    if (digitalRead(buttonPresets) == LOW) {
      // increment presetIndex
      presetIndex = presetIndex + 1;

      // check if at end of preset length, wrap
      if (presetIndex >= (sizeof (presets) / sizeof (*presets)) ){
        presetIndex = 0;
      }

      // make sure preset values are captured
      setting_left_wheel_distance = presets[presetIndex][0];
      setting_left_wheel_speed = presets[presetIndex][1];   // in mm
      setting_right_wheel_speed = presets[presetIndex][2];  // arbitrary scale
      setting_right_wheel_distance = presets[presetIndex][3]; // in mm

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
    if (stepperLeft.distanceToGo() == 0) {
      stepperLeft.moveTo(-stepperLeft.currentPosition());
    }

    // Bounce the left wheel direction
    if (stepperRight.distanceToGo() == 0) {
      stepperRight.moveTo(-stepperRight.currentPosition());
    }

    // Look for stop button
    if (digitalRead(buttonStart) == LOW) {
      messageLarge("Stop!");
      stopAndResetSteppers();
      report();
    }

    // Go!
    stepperLeft.run();
    stepperRight.run();

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
