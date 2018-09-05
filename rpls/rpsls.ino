#include <Esplora.h>

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int lastButtonState;

void setup() {
  lastButtonState = HIGH;
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = Esplora.readButton(SWITCH_UP);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (lastButtonState == HIGH && buttonState == LOW) {
    randomColor();
    lastButtonState = LOW;
  }
  else if(lastButtonState == LOW && buttonState == LOW) {
    lastButtonState = LOW;
  }
  else if(lastButtonState == LOW && buttonState == HIGH) {
    // turn LED off:
    Esplora.writeRGB(0, 0, 0);
    lastButtonState = HIGH;
  } else { // lastButtonState == HIGH && buttonState == HIGH
    // do nothing
  }
}

void randomColor() {
  int x = random() % 5;
  switch(x) {
   case 0:
     Esplora.writeRGB(255, 0, 0);
     break;
   case 1:
     Esplora.writeRGB(0, 0, 255);
     break;
   case 2:
     Esplora.writeRGB(255, 0, 255);
     break;
   case 3:
     Esplora.writeRGB(0, 255, 0);
     break;
   case 4:
     Esplora.writeRGB(255, 255, 0);
     break;
   default:
     break;
  }
}
