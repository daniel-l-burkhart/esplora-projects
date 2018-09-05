#include <Esplora.h>
#include <TFT.h>
#include <SPI.h>

// TFT screen is 160-wide by 128-high
#define X_MAX (159)
#define X_MIN (0)

#define Y_MAX (127)
#define Y_MIN (0)

// min and max raw accelerometer values
// determined experimentally from the Esplora accelerometer demo
// note the x-values are axis-reversed from the screen orientation
#define ACCEL_MIN_X (150)
#define ACCEL_MAX_X (-150)
#define ACCEL_MIN_Y (-150)
#define ACCEL_MAX_Y (150)

// min and max *mapped* (normalized) accelerometer values
#define NORMALIZED_ACCEL_MAX (5)
#define NORMALIZED_ACCEL_MIN (-5)

int x;
int y;

void setup() {
  EsploraTFT.begin();
  EsploraTFT.background(0, 0, 0);
  
  // start in the middle of the screen
  x = 80;
  y = 64;
}

void loop() {
  bool brushDown = false;
  if( Esplora.readButton(SWITCH_UP) == LOW ) {
     redStroke();
     brushDown = true;
  } else if( Esplora.readButton(SWITCH_LEFT) == LOW ) {
     purpleStroke();
     brushDown = true;
  } else if( Esplora.readButton(SWITCH_RIGHT) == LOW ) {
     yellowStroke();
     brushDown = true;
  } else if( Esplora.readButton(SWITCH_DOWN) == LOW ) {
     greenStroke();
     brushDown = true;
  } else {
     
     brushDown = false;
  }
  
  int x_accel = Esplora.readAccelerometer(X_AXIS);
  int y_accel = Esplora.readAccelerometer(Y_AXIS);
  
  int nextX = x + map(x_accel, ACCEL_MIN_X, ACCEL_MAX_X, NORMALIZED_ACCEL_MIN, NORMALIZED_ACCEL_MAX);
  int nextY = y + map(y_accel, ACCEL_MIN_Y, ACCEL_MAX_Y, NORMALIZED_ACCEL_MIN, NORMALIZED_ACCEL_MAX);
  
  // keep from going off the screen
  if (nextX > X_MAX) {
    nextX = X_MAX;
  }
  
  if (nextX < X_MIN) {
    nextX = X_MIN;
  }
  
  if (nextY > Y_MAX) {
    nextY = Y_MAX;
  }
  
  if (nextY < Y_MIN) {
    nextY = Y_MIN;
  }
  
  if (brushDown) {
    EsploraTFT.line(x, y, nextX, nextY);
  } else {
    // erase previous cursor point
    blackStroke();
    EsploraTFT.point(x, y);
    
    // draw new cursor point
    whiteStroke();
    EsploraTFT.point(nextX, nextY);
  }
  
  x = nextX;
  y = nextY;
  
  
  
  delay(100);
}

void whiteStroke() {
  EsploraTFT.stroke(255, 255, 255);
}

void blackStroke() {
  EsploraTFT.stroke(0, 0, 0);
}

void redStroke() {
  EsploraTFT.stroke(0, 0, 255); 
}

void purpleStroke() {
   EsploraTFT.stroke(255, 0, 255);
}

void yellowStroke() {
  EsploraTFT.stroke(0, 255, 255); 
}

void greenStroke() {
  EsploraTFT.stroke(0, 255, 0); 
}
