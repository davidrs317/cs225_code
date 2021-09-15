#include "cs225/PNG.h"
#include <list>
#include <iostream>
#include <vector>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  png_ = new PNG(png);
  size_ = 0;
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  func_.push_back(traversal.begin());
  rainbow_.push_back(&colorPicker);
  size_++;
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  animation.addFrame(*png_);
  int term = 1;
  //marker for whether an iteration has been completed
  int place = 0;
  //index variable
  ColorPicker* pick = rainbow_[place];
  //current color to print out
  ImageTraversal::Iterator lookup = func_[place];
  //holds the iterator
  std::vector<int> marker = vector<int>(png_->width()*png_->height(), 0);
  //iterate over the image creating all necessary frames 
  while(size_ != place){
    for(unsigned i = 0; i < frameInterval; i++){
      Point p = *lookup;
      //as long as the point is not null and has been looked at, continue iterating
      while(!(p == Point(-1, -1)) && marker[p.x*png_->height() + p.y] == 1){
        ++lookup;
        p = *lookup;
      }
      //if the point is null, the animation will be complete
      if(p == Point(-1, -1)){
        term = 0;
        break;
      }
      //mark the point as viewed
      marker[p.x*png_->height() + p.y] = 1;
      //set the pixel's color
      png_->getPixel(p.x, p.y) = pick->getColor(p.x, p.y);
    }
    //add the frame in
    animation.addFrame(*png_);
    if(term == 0){
      place++;
      if(place >= size_){
        break;
      }
      //go to the next color and iterator
      pick = rainbow_[place];
      lookup = func_[place];
      term = 1;
      //reset the marker for a point
      marker = vector<int>(png_->width()*png_->height(), 0);
    }
  }
  return animation;
}
