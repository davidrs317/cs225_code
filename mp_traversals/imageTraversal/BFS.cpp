#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  p_ = new PNG(png);
  height_ = png.height();
  width_ = png.width();
  tolerance_ = tolerance;
  //viewed_ = std::vector<int>(height_*width_, 0);
  start_ = start;
  points_.push(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  BFS* prim = new BFS(*p_, start_, tolerance_);
  return ImageTraversal::Iterator(prim);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  BFS* fin = new BFS(*p_, Point(-1, -1), tolerance_);
  return ImageTraversal::Iterator(fin);
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  points_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  if(points_.empty()){
    return Point(-1,-1);
  }
  Point looker = points_.front();
  points_.pop();
  return looker;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  if(points_.empty()){
    return Point(-1, -1);
  }
  Point current = points_.front();
  return current;
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  bool status = points_.empty();
  return status;
}

unsigned BFS::getHeight(){
  return height_;
}

unsigned BFS::getWidth(){
  return width_;
}

double BFS::getTol(){
  return tolerance_;
}

PNG* BFS::getPNG(){
  return p_;
}

Point BFS::getStart(){
  return start_;
}