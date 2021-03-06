#include "../cs225/HSLAPixel.h"
#include "../Point.h"
#include "../cs225/PNG.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(PNG png){
  png_ = png;
}

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  //return the pixels held at x and y
  if(x > png_.width() || y > png_.height()){
    return HSLAPixel(0, 0, 0);
  }
  return png_.getPixel(x, y);
  
}
