/**
 * @file DFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;
  unsigned getWidth();
  unsigned getHeight();
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
  Point ender_;
  //std::vector<int> viewed_;
  std::stack<Point> points_;

  //bool exwin(const Point& point);

  //bool winTol(const Point& point);
};
