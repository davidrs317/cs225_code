#include <cmath>
#include <iterator>
#include <iostream>
#include <vector>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

double ImageTraversal::calculateDelta1(const HSLAPixel& p1, const HSLAPixel& p2){
  double delta = calculateDelta(p1, p2);
  return delta;
}
/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  location_ = nullptr;
  viewed_ = std::vector<int>(location_->getHeight()*location_->getWidth(), 0);
}

/**
 * iterator constructor that includes an ImageTraversal pointer as a parameter
 */
ImageTraversal::Iterator::Iterator(ImageTraversal* travel){
  location_ = travel;
  viewed_ = std::vector<int>(location_->getHeight()*location_->getWidth(), 0);
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  //Point current = location_->peek();
  //if(current == Point(-1, -1)){
    //return *this;
  //}
  //if(location_ == nullptr){
    //return *this;
  //}
  //current = location_->pop();
  //location_->add(current);
  Point current = location_->pop();
  if(current == Point(-1,-1)){
    return *this;
  }
  unsigned h = location_->getHeight();
  unsigned w = location_->getWidth();
  unsigned x = current.x;
  unsigned y = current.y;
  double tolerance = location_->getTol();

  Point starter = location_->getStart();
  PNG* howdy = location_->getPNG();
  viewed_[x*h + y] = 1;
  Point n1(x+1, y);
  Point n2(x, y+1);
  Point n3(x-1, y);
  Point n4(x, y-1);
  
  if(valid(n1, starter, tolerance, howdy) && viewed_[(x+1)*h + y] != 1){
    location_->add(n1);
    viewed_[(x+1)*h + y] = 1;
  }
  if(valid(n2, starter, tolerance, howdy) && viewed_[x*h + (y+1)] != 1){
    location_->add(n2);
    viewed_[x*h + (y+1)] = 1;
  }
  if(valid(n3, starter, tolerance, howdy) && viewed_[(x-1)*h + y] != 1){
    location_->add(n3);
    viewed_[(x-1)*h + y] = 1;
  }
  if(valid(n4, starter, tolerance, howdy) && viewed_[x*h + (y-1)] != 1){
    location_->add(n4);
    viewed_[x*h + (y-1)] = 1;
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  Point cur = location_->peek();
  return cur;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if(location_ == nullptr && other.location_ == nullptr){
    return false;
  }
  if((location_ != nullptr && other.location_ == nullptr) || (location_ == nullptr && other.location_ != nullptr)){
    return true;
  }
  if(location_->empty() && other.location_->empty()){
    return false;
  }
  return !(location_->peek() == other.location_->peek());
  //return false;
}

bool ImageTraversal::Iterator::valid(Point& point, Point& start, double tolerance, const PNG* png){
  if(point.x >= png->width() || point.y >= png->height()){
    return false;
  }
  HSLAPixel p1 = png->getPixel(start.x, start.y);
  HSLAPixel p2 = png->getPixel(point.x, point.y);
  double delta = calculateDelta(p1, p2);
  if(delta >= tolerance){
    return false;
  }
  return true;
}

