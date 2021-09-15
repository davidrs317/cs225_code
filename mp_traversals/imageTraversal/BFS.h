/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;
  unsigned getHeight();
  unsigned getWidth();
  double getTol();
  PNG* getPNG();
  Point getStart();


private:
  /** @todo [Part 1] */
  /** add private members here*/
  PNG* p_;
  unsigned height_;
  unsigned width_;
  double tolerance_;
  Point start_;
  //std::vector<int> viewed_;
  std::queue<Point> points_;

  /*bool exwin(const Point& point);

  bool winTol(const Point& point);*/
};
