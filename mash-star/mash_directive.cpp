#include <Esplora.h>
#include <SPI.h>
#include <TFT.h>


#include "mash_directive.h"
#define X0 (x)
#define X1 (x + MD_WIDTH/4)
#define X2 (x + MD_WIDTH/2)
#define X3 (x + 3*MD_WIDTH/4)
#define X4 (x + MD_WIDTH)
#define Y0 (y)
#define Y1 (y + MD_WIDTH/4)
#define Y2 (y + MD_WIDTH/2)
#define Y3 (y + 3*MD_WIDTH/4)
#define Y4 (y + MD_WIDTH)

#define MD_RADIUS (MD_WIDTH/8)

MashDirective::MashDirective(int x, int y) {
  this->x = x;
  this->y = y;
  this->changePattern();
  this->atLevel2 = false;
}

void MashDirective::erase() {
  EsploraTFT.stroke(0, 0, 0);
  EsploraTFT.fill(0, 0, 0);
  EsploraTFT.rect(x, y, MD_WIDTH, MD_WIDTH);
}

void MashDirective::draw() {
  erase();
  EsploraTFT.stroke(255, 255, 255);
  
  // draw the outer box
  EsploraTFT.line(X2, Y0, X0, Y2);
  EsploraTFT.line(X2, Y0, X4, Y2);
  EsploraTFT.line(X0, Y2, X2, Y4);
  EsploraTFT.line(X2, Y4, X4, Y2);
  
  // draw the dividing lines
  EsploraTFT.line(X1, Y1, X3, Y3);
  EsploraTFT.line(X3, Y1, X1, Y3);
  
  EsploraTFT.fill(255, 255, 255);
  if (pattern[UP]) {
    EsploraTFT.circle(X2, Y1, MD_RADIUS);
  }
  
  if (pattern[DOWN]) {
    EsploraTFT.circle(X2, Y3, MD_RADIUS);
  }
  
  if (pattern[LEFT]) {
    EsploraTFT.circle(X1, Y2, MD_RADIUS);
  }
  
  if (pattern[RIGHT]) {
    EsploraTFT.circle(X3, Y2, MD_RADIUS);
  }
}

void MashDirective::changePattern() {
  // right now, just selects a single direction at random
  for (int i = 0; i < 4; i++) {
    pattern[i] = false;
  }
  
  pattern[ random() % 4 ] = true;
  
  if (atLevel2) {
    pattern[ random() % 4 ] = true;
  }
}

int MashDirective::checkPattern() {
  bool buttons[4];
  buttons[UP] = (LOW == Esplora.readButton(SWITCH_UP));
  buttons[DOWN] = (LOW == Esplora.readButton(SWITCH_DOWN));
  buttons[LEFT] = (LOW == Esplora.readButton(SWITCH_LEFT));
  buttons[RIGHT] = (LOW == Esplora.readButton(SWITCH_RIGHT));
  
  if (!(buttons[UP] || buttons[DOWN] || buttons[LEFT] || buttons[RIGHT])) {
    return PATTERN_INCOMPLETE; 
  }
  
  for (int i = 0; i < 4; i++) {
    // wrong button pressed
    if (!pattern[i] && buttons[i]) {
      return PATTERN_INCORRECT;
    }
    if (pattern[i] && !buttons[i]) {
      return PATTERN_INCOMPLETE;
    }
  }
  
  return PATTERN_CORRECT;
}

void MashDirective::startLevel2() {
  atLevel2 = true;  
}
