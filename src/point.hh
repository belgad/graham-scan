// Copyright 2021 Gleb "belgad" Danshin
#ifndef GRAHAM_SCAN_SRC_POINT_HH_
#define GRAHAM_SCAN_SRC_POINT_HH_

#include <iostream>

struct Point {
public:
  double X, Y;
public:
  Point(double x = 0.0, double y = 0.0);
  Point(const Point& other);
  Point(const Point&& other);
  Point& operator=(const Point& other);
  Point operator+(const Point& other);
  Point operator-(const Point& other);
  Point& operator+=(const Point& other);
  Point& operator-=(const Point& other);
  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const;
  bool operator<(const Point& other) const;
  bool operator>(const Point& other) const;
  bool operator<=(const Point& other) const;
  bool operator>=(const Point& other) const;
  static double det(const Point& first, const Point& second);
};

void swap(Point& first, Point& second);
std::ostream& operator<<(std::ostream& os, const Point& point);

#endif  // GRAHAM_SCAN_SRC_POINT_HH_
