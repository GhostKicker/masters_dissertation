#pragma once

#include "geom.h"

#include <vector>

class StaticObstacle {
public:
  StaticObstacle() = default;
  StaticObstacle(const Polygon& _polygon)
      : polygon(_polygon)
  {}

  const Polygon& GetPolygon() const {
    return polygon;
  }

private:
  Polygon polygon;
};
