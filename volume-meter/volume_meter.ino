#include <SPI.h>

#include <TFT.h>

#include <Esplora.h>

int y_offset = 59;

// TFT screen is 160-wide by 128-high
#define BAR_MAX (159)
#define BAR_MIN (0)

// adjust these as-needed to get a decent range of sampled volume
#define VOL_MIN (0)
#define VOL_MAX (100)

// the cutoffs for the green and yellow zones
#define GREEN_THRESH (25)
#define YELLOW_THRESH (50)

// width of our volume bar
#define BAR_WIDTH (10)

void setup() {
  // start the Esplora's TFT screen
  EsploraTFT.begin();
  
  clearScreen();
}

void loop() {
  
  // read an amplitude from the microphone
  int amp = Esplora.readMicrophone();
  
  // map the amplitude to something in the TFT screen's
  // 160-pixel screen width
  amp = map(amp, VOL_MIN, VOL_MAX, BAR_MIN, BAR_MAX);
  
  // the green zone
  if (amp < GREEN_THRESH) {
    setGreen();
    EsploraTFT.rect(BAR_MIN, y_offset, amp, BAR_WIDTH);
  }
  
  // the yellow zone
  if (amp >= GREEN_THRESH && amp < YELLOW_THRESH) {
    fullGreen();
    
    // partial yellow
    setYellow();
    EsploraTFT.rect(GREEN_THRESH, y_offset, amp-GREEN_THRESH, BAR_WIDTH);
  }
  
  // the red zone
  if (amp >= YELLOW_THRESH) {
    fullGreen();
    fullYellow();
    
    // partial red
    setRed();
    EsploraTFT.rect(YELLOW_THRESH, y_offset, amp-YELLOW_THRESH, BAR_WIDTH);
  }
  
  // draw the remainder of the bar as "blank"  
  setFillAndStroke(0, 0, 0);
  EsploraTFT.rect(amp + 1, y_offset, BAR_MAX-amp, BAR_WIDTH);
}

void setFillAndStroke(int red, int green, int blue) {
  EsploraTFT.fill(blue, green, red);
  EsploraTFT.stroke(blue, green, red);
}

void fullGreen() {
  setGreen();
  EsploraTFT.rect(BAR_MIN, y_offset, GREEN_THRESH, BAR_WIDTH);
}

void fullYellow() {
   setYellow();
   EsploraTFT.rect(GREEN_THRESH, y_offset, YELLOW_THRESH-GREEN_THRESH, BAR_WIDTH);
}

void setRed() {
  setFillAndStroke(255, 0, 0); 
}

void setYellow() {
  setFillAndStroke(255, 255, 0); 
}

void setGreen() {
 setFillAndStroke(0, 255, 0); 
}

void clearScreen() {
  EsploraTFT.background(0, 0, 0);
}
