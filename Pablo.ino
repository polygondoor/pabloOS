#include "Pablo.h"

// A Custom mode example
void customDrawingMode(){

  // Displays a message on Artbot's little screen
  message("Press Start");

  // Wait for the start button to be pressed
  while ( waitForStartButton() ){
    readModeButton();
    if (drawingMode != 1) return;
  }

  delay(2000);

  // Turn both wheels in the same directiom
  turn_wheels_mm(100, 100);


}
