#include <Esplora.h>
#include <Adafruit_NeoPixel.h>

// tell students to include this!
#include <math.h>

// see http://21stdigitalhome.blogspot.com/2012/12/esplora-expansion-header-pinouts.html
// for description of how esplora pins map to arduino uno pins
#define NEOPIXEL_PIN 7
 
// adapted from: https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel ring = Adafruit_NeoPixel(16, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  ring.begin();
  ring.show();
}

int lastAngle = -1;
void loop() {
  int x = Esplora.readJoystickX();
  int y = Esplora.readJoystickY();
  
  // convert x,y into an integer angle between -pi and pi, but
  // multiple by 100 to preserve some resolution
  int angle = int(atan2(x, y)*100);
  
  // map the angle into discrete led ordinals
  angle = map(angle, -314, 314, 15, 0);
  
  // must do this to keep from constantly changing the color!
  if (lastAngle != angle) {
    allOff();
    ring.setPixelColor(angle, getRandomColor());
    ring.show();
    lastAngle = angle;
  }
}

uint32_t getRandomColor() {
  int red = random() % 255;
  int green = random() % 255;
  int blue = random() % 255;
 
  return ring.Color(red, green, blue); 
}

void allOff() {
  for (int i=0; i<16; i++) {
    ring.setPixelColor(i, 0, 0, 0);
  } 
}
