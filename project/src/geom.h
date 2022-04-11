#pragma once

#include <cmath>
#include <algorithm>
#include <cassert>
#include <iostream>

constexpr double EPS = 1e-6;

struct Point {
  double x, y;
  Point() = default;
  Point(double _x, double _y)
      : x(_x)
      , y(_y)
  {}
  Point operator-() const { return Point(-x, -y); }

  Point operator+(const Point& rhs) const { return Point(x + rhs.x, y + rhs.y); }
  Point operator-(const Point& rhs) const { return operator+(-rhs); }
  Point operator*(double mult) const { return Point(x * mult, y * mult); }
  Point operator/(double mult) const { return Point(x / mult, y / mult); }

  bool operator==(const Point& rhs) const {
    return std::abs(x - rhs.x) < EPS && std::abs(y - rhs.y) < EPS;
  }
};

double Norm2(const Point& pt) {
  return pt.x * pt.x + pt.y * pt.y;
}

double Norm(const Point& pt) {
  return std::sqrt(Norm2(pt));
}

double Distance(const Point& lhs, const Point& rhs) {
  return Norm(lhs - rhs);
}

double Cross(const Point& a, const Point& b) {
  return a.y * b.x - a.x * b.y;
}

double Dot(const Point& a, const Point& b) {
  return a.x * b.x + a.y * b.y;
}

struct Segment {
  Point a, b;
  Segment() = default;
  Segment(const Point& _a, const Point& _b)
      : a(_a)
      , b(_b)
  {}
};

double Distance(const Point& p, const Segment& s) {
  //std::cout << "data: " << p.x << "," << p.y << " " << s.a.x << "," << s.a.y << " " << s.b.x << "," << s.b.y << std::endl;
  if (Dot(p - s.a, s.b - s.a) < EPS) {
    //std::cout << "1: " << Distance(p, s.a) << std::endl;
    //std::cout << Dot(p - s.a, s.b - s.a) << std::endl;
    return Distance(p, s.a);
  }
  if (Dot(p - s.b, s.a - s.b) < EPS) {
    //std::cout << "2: " << Distance(p, s.b) << std::endl;
    //std::cout << Dot(p - s.b, s.a - s.b) << std::endl;
    return Distance(p, s.b);
  }
  //std::cout << "3: " << std::abs(Cross(p - s.a, p - s.b)) / Distance(s.a, s.b) << std::endl;
  return std::abs(Cross(p - s.a, p - s.b)) / Distance(s.a, s.b);
}

double Distance(const Segment& s, const Point& p) {
  return Distance(p, s);
}

bool Intersects(const Segment& s1, const Segment& s2) {
  auto bbox_condition = [&](std::pair<double, double> a, std::pair<double, double> b) {
    a = {std::min(a.first, a.second), std::max(a.first, a.second)};
    b = {std::min(b.first, b.second), std::max(b.first, b.second)};
    return std::max(a.first, b.first) - std::min(a.second, b.second) < EPS;
  };
  return bbox_condition({s1.a.x, s1.b.x}, {s2.a.x, s2.b.x}) &&
         bbox_condition({s1.a.y, s1.b.y}, {s2.a.y, s2.b.y}) &&
         Cross(s1.a - s2.a, s1.a - s2.b) * Cross(s1.b - s2.a, s1.b - s2.b) < EPS && 
         Cross(s2.a - s1.a, s2.a - s1.b) * Cross(s2.b - s1.a, s2.b - s1.b) < EPS;
}

double Distance(const Segment& s1, const Segment& s2) {
  if (Intersects(s1, s2)) {
    return 0.0;
  }
  return std::min({ Distance(s1.a, s2),
                    Distance(s1.b, s2),
                    Distance(s1, s2.a),
                    Distance(s1, s2.b) });
}

struct Polygon {
  std::vector<Point> points;
  Polygon() = default;
  Polygon(const std::vector<Point>& _points)
      : points(_points)
  {}
};

double Distance(const Polygon& poly, const Point& pt) {
  assert(poly.points.size() >= 2);
  double result = Distance(pt, Segment(poly.points.front(), poly.points.back()));
  for (int i = 0; i + 1 < (int)poly.points.size(); ++i) {
    result = std::min(result, Distance(pt, Segment(poly.points[i], poly.points[i+1])));
  }
  return result;
}

double Distance(const Point& pt, const Polygon& poly) {
  return Distance(poly, pt);
}

double Distance(const Polygon &poly, const Segment &s) {
  assert(poly.points.size() >= 2);
  double result = Distance(s, Segment(poly.points.front(), poly.points.back()));
  for (int i = 0; i + 1 < (int)poly.points.size(); ++i) {
    result = std::min(result, Distance(s, Segment(poly.points[i], poly.points[i + 1])));
  }
  return result;
}

double Distance(const Segment& s, const Polygon& poly) {
  return Distance(poly, s);
}

struct Circle {
  Point c;
  double r;
  Circle() = default;
  Circle(const Point& _c, double _r) 
      : c(_c)
      , r(_r)
  {}
};

double Distance(const Circle& c, const Point& p) {
  double dst = Distance(c.c, p);
  return dst >= c.r ? dst - c.r : 0.0;
}

double Distance(const Point& p, const Circle& c) {
  return Distance(c, p);
}

double Distance(const Circle& c, const Segment& s) {
  double dst = Distance(c.c, s);
  return dst >= c.r ? dst - c.r : 0.0;
}

double Distance(const Segment& s, const Circle& c) {
  return Distance(c, s);
}

