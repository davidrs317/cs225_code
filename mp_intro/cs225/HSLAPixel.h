/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {
  class HSLAPixel{
    public:
      //denote the hue of the pixel, in degrees [0,360)
      double h;
      //saturation of the pixel[0,1]
      double s;
      //luminance of the pixel[0,1]
      double l;
      //alpha(transparency) of the pixel[0,1]
      double a;

      //Opaque and white pixel - default
      HSLAPixel();

      //Opaque pixel with given hue, saturation, and luminance values
      HSLAPixel(double hue, double saturation, double luminance);

      //Pixel with given hue, saturation, luminance, and alpha values
      HSLAPixel(double hue, double saturation, double luminance, double alpha);
  };
}
