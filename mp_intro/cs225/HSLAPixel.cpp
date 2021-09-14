/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {
  //default constructor, opaque and white
  HSLAPixel::HSLAPixel(){
    h = 0.0;
    s = 0.0;
    l = 1.0;
    a = 1.0;
  }
  //create opaque pixel with given h, s, and l values
  HSLAPixel::HSLAPixel(double hue, double saturation, double luminance){
    h = hue;
    s = saturation;
    l = luminance;
    a = 1.0;
  }
  //create pixel with given h, s, l, and a values
  HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha){
    h = hue;
    s = saturation;
    l = luminance;
    a = alpha;
  }
}
