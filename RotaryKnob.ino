/*
  Handles the rotary controller
*/

void setupRotaryEncoder(){
  pinMode(rotaryEncoderClkPin, INPUT); // clk
  pinMode(rotaryEncoderDtPin, INPUT); // dt
  pinMode(rotaryEncoderBtnPin, INPUT_PULLUP); // btn
}

/*
 * This method reads all the rotary encoders
 */
void readRotaryEncoders() {
  rotaryEncoderClkValue = digitalRead(rotaryEncoderClkPin); // orange cable, CLK
  rotaryEncoderDtValue = digitalRead(rotaryEncoderDtPin);

  // rotaryMode; // Can be 0 1 2 or 3 (depending on which value we are changing)

  if ((rotaryEncoderClkValue != rotaryEncoderClkValuePrevious) && (rotaryEncoderClkValue == LOW)) { // Knob Rotated l when aVal changes, BUT use only if aVal is LOW.
    if (rotaryEncoderDtValue == LOW) {
      // INCREMENT
      if (rotaryMode == 0) {
        setting_right_wheel_distance += rotaryIncrement;
        if (setting_right_wheel_distance > 99999) setting_right_wheel_distance = 99999;
      }
      else if (rotaryMode == 1) {
        setting_right_wheel_speed += 1;
        if (setting_right_wheel_speed > 50) setting_right_wheel_speed = 50;
      }
      else if (rotaryMode == 2) {
        setting_left_wheel_speed += 1;
        if (setting_left_wheel_speed > 50) setting_left_wheel_speed = 50;
      }
      else {
        setting_left_wheel_distance += rotaryIncrement;
        if (setting_left_wheel_distance > 99999) setting_left_wheel_distance = 99999;
      }
      report();
    }
    else {
      // DECREMENT
      if (rotaryMode == 0) {
        setting_right_wheel_distance -= rotaryIncrement;
      }
      else if (rotaryMode == 1) {
        setting_right_wheel_speed -= 1;
      }
      else if (rotaryMode == 2) {
        setting_left_wheel_speed -= 1;
      }
      else {
        setting_left_wheel_distance -= rotaryIncrement;
      }
      report();
    }
  }

  rotaryEncoderClkValuePrevious = rotaryEncoderClkValue; // Don’t forget this
}

void cycleRotaryIncrement(){
  if (rotaryIncrement == 1) {
    rotaryIncrement = 10;
  }
  else if (rotaryIncrement == 10) {
    rotaryIncrement = 100;
  }
  else if (rotaryIncrement == 100) {
    rotaryIncrement = 1000;
  }
  else if (rotaryIncrement == 1000) {
    rotaryIncrement = 1;
  }
}
