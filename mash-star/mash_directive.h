#ifndef MASH_DIRECTIVE_H
#define MASH_DIRECTIVE_H

// easiest if this is divisible-by-2
#define MD_WIDTH 80

// these numbers are assigned to make them
// easy to randomize
#define UP (0)
#define LEFT (1)
#define RIGHT (2)
#define DOWN (3)

#define PATTERN_INCOMPLETE (0)
#define PATTERN_CORRECT (1)
#define PATTERN_INCORRECT (2)

class MashDirective {
  private:
    int x;
    int y;
    bool atLevel2;
    
    // holds the pattern state
    bool pattern[4];

    void erase();
    
  public:
    MashDirective(int x, int y);
    void draw();
    
    // randomly changes the pattern
    void changePattern();
    
    // returns PATTERN_CORRECT if the proper button(s) are pressed
    // returns PATTERN_INCORRECT if there are button(s) pressed that shouldn't be
    // returns PATTERN_NONE if no buttons are pressed
    int checkPattern();
    
    void startLevel2();
};

#endif
