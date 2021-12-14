// Copyright 2021 Gleb "belgad" Danshin
#include "point.hh"

Point::Point(double x, double y) : X(x), Y(y) {}

Point::Point(const Point& other) : X(other.X), Y(other.Y) {}

Point::Point(const Point&& other) : X(other.X), Y(other.Y) {}

Point& Point::operator=(const Point& other) {
  if (this != &other) {
    this->X = other.X;
    this->Y = other.Y;
  }
  return *this;
}

Point Point::operator+(const Point& other) {
  Point tmp = Point(this->X + other.X, this->Y + other.Y);
  return tmp;
}

Point Point::operator-(const Point& other) {
  Point tmp = Point(this->X - other.X, this->Y - other.Y);
  return tmp;
}

Point& Point::operator+=(const Point& other) {
  this->X += other.X; this->Y += other.Y;
  return *this;
}

Point& Point::operator-=(const Point& other) {
  this->X -= other.X; this->Y -= other.Y;
  return *this;
}

bool Point::operator==(const Point& other) const {
  return this->X == other.X && this->Y == other.Y;
}

bool Point::operator!=(const Point& other) const {
  return this->X != other.X || this->Y != other.Y;
}

bool Point::operator<(const Point& other) const {
  double d = det(*this, other);
  if (d > 0) {
    return true;
  } else if (d == 0) {
    return (this->X * this->X + this->Y * this->Y) <
    (other.X * other.X + other.Y * other.Y);
  } else {
    return false;
  }
}

bool Point::operator>(const Point& other) const {
  return (other < *this);
}

bool Point::operator<=(const Point& other) const {
  return !(other < *this);
}

bool Point::operator>=(const Point& other) const {
  return !(*this < other);
}

double Point::det(const Point& first, const Point& second) {
  return -(first.Y * second.X - first.X * second.Y);
}

void swap(Point& first, Point& second) {
  Point tmp = first;
  first = second;
  second = tmp;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
  os << point.X << '\t' << point.Y;
  return os;
}
