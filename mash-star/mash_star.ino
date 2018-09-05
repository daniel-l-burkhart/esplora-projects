#include <Esplora.h>
#include <SPI.h>
#include <TFT.h>
#include <limits.h>

#include "mash_directive.h"

// how long, in ms, before the next pattern
// if we hit the pattern timeout, lose points
#define PATTERN_TIMEOUT (2000)

#define LVL2_THRESH (1000)

#define TIMEOUT_PENALTY (50)

MashDirective md(0, 0);
int score = 0;
unsigned long lastPatternStart;

void setup() {
  EsploraTFT.begin();
  EsploraTFT.background(0, 0, 0);
  EsploraTFT.setTextSize(2);
  
  md.changePattern();
  md.draw();
  lastPatternStart = millis();
}


void loop() {
  if (score >= LVL2_THRESH) {
    md.startLevel2();
  }
  
  printScore();
  unsigned long now = millis();
  
  // didn't get the pattern in time, so lose points and begin a new pattern
  if (now > (lastPatternStart + PATTERN_TIMEOUT)) {
    score -= TIMEOUT_PENALTY;
    score = constrain(score, 0, INT_MAX);
    md.changePattern();
    md.draw();
    lastPatternStart = millis();
    return;
  } 
  
  // we got the pattern, so add points and begin a new pattern
  if(md.checkPattern() == PATTERN_CORRECT) {
    score += (now - lastPatternStart) / 10;
    md.changePattern();
    md.draw();
    lastPatternStart = millis();
    return;
  }
  
  if(md.checkPattern() == PATTERN_INCORRECT) {
    score -= TIMEOUT_PENALTY;
    score = constrain(score, 0, INT_MAX);
    return;
  }
}

int lastScore = INT_MAX;
void printScore() {
  
  if (lastScore != score) {
    lastScore = score;
    //erase teh last score
    EsploraTFT.stroke(0, 0, 0);
    EsploraTFT.fill(0, 0, 0);
    EsploraTFT.rect(0, 107, 160, 20);
    
    // write the new text
    EsploraTFT.stroke(255, 255, 255);
    EsploraTFT.text("Score:", 3, 85);
    String s = "";
    s += score;
    EsploraTFT.text(s.c_str(), 3, 107);
  }
}
