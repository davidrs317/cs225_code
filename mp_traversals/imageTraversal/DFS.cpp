#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  p_ = new PNG(png);
  width_ = png.width();
  height_ = png.height();
  tolerance_ = tolerance;
  //viewed_ = std::vector<int>(height_*width_, 0);
  start_ = start;
  points_.push(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  DFS* prim = new DFS(*p_, start_, tolerance_);
  return ImageTraversal::Iterator(prim);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  DFS* fin = new DFS(*p_, Point(-1, -1), tolerance_);
  return ImageTraversal::Iterator(fin);
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  points_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  if(points_.empty()){
    return Point(-1, -1);
  }
  Point looker = points_.top();
  points_.pop();

  return looker;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  if(points_.empty()){
    return Point(-1, -1);
  }
  return points_.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  bool status = points_.empty();
  return status;
}

unsigned DFS::getHeight(){
  return height_;
}

unsigned DFS::getWidth(){
  return width_;
}

double DFS::getTol(){
  return tolerance_;
}

PNG* DFS::getPNG(){
  return p_;
}

Point DFS::getStart(){
  return start_;
}