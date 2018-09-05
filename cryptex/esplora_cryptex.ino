/*
Entering the proper sequence of 8 button presses causes a servo to unlock a box.  Entering the wrong sequence sounds an alarm.
Use the RESET button to try again.

Enter the code using the up/down/left/right buttons
 */

#include <Servo.h>
#include <Esplora.h>

#define LOCK_ANGLE (10)
#define UNLOCK_ANGLE (150)

// based on Esplora.h, this is exclusive of the SWITCH_UP, SWITCH_DOWN, etc. macros
#define NO_BUTTON (0)

Servo servo;

// where we are in our button sequence
int seqNum = 0;

#define COMBINATION_LENGTH (8)

// Konami code for the combination! (well, most of it anyway).
int combination[] =
{
  SWITCH_UP,
  SWITCH_UP,
  SWITCH_DOWN,
  SWITCH_DOWN,
  SWITCH_LEFT,
  SWITCH_RIGHT,
  SWITCH_LEFT,
  SWITCH_RIGHT
};

void setup() {
  Serial.begin(9600);
  servo.attach(11);
  lock();
}

void loop() {
  int button = readButtons();
  
  // nothing entered, so do nothing
  if (button == NO_BUTTON) return;
  
  // wrong button pressed, sound an alarm
  if (button != combination[seqNum]) {
    Esplora.tone(440, 2000);
    
    // game over, so wait forever (note: forever ends when the reset button is pressed)
    while(1);
  }
  
  if (button == combination[seqNum]) {
    // we've found the combination, so we're done
    if (seqNum == COMBINATION_LENGTH-1) {
      unlock();
      while(1); 
    } else {
      seqNum++;
    }
  }
}

// returns NO_BUTTON if nothing pressed, otherwise returns the macro for the pressed button
int readButtons() {
  int buttons[] = { SWITCH_UP, SWITCH_DOWN, SWITCH_LEFT, SWITCH_RIGHT };
  for (int i = 0; i < 4; i++) {
    if (Esplora.readButton(buttons[i]) == LOW) {
      String s = "pressed button: ";
      s += buttons[i];
      Serial.println(s);
      // must wait until the button is no longer pressed!
      while(Esplora.readButton(buttons[i]) == LOW);
      return buttons[i]; 
    } 
  }
  return NO_BUTTON;
}

void lock() {
  servo.write(LOCK_ANGLE); 
}

void unlock() {
  servo.write(UNLOCK_ANGLE);
}
