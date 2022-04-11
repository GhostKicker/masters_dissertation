#pragma once

#include "geom.h"

#include <vector>

class DynamicObstacle {
public:
  DynamicObstacle() = default;
  DynamicObstacle& operator=(const DynamicObstacle& rhs) {
    trajectory = rhs.trajectory;
    object = rhs.object;
    trajectory_index = rhs.trajectory_index;
    between_index = rhs.between_index;
    return *this;
  }
  DynamicObstacle(const std::vector<Point>& _trajectory, double radius)
      : trajectory(_trajectory)
      , object(trajectory.front(), radius)
  {}
  void GoNextState() {
    if (trajectory.size() == 0) {
      return;
    }
    ++between_index;
    if (between_index >= between_cnt) {
      between_index = 0;
      ++trajectory_index;
    }
    if (trajectory_index + 1 >= static_cast<int>(trajectory.size())) {
      trajectory_index = 0;
      between_index = 0;
    }
    object.c = 
      (trajectory[trajectory_index] * (between_cnt - between_index) +
      trajectory[trajectory_index + 1] * between_index) / between_cnt;
  }
  const std::vector<Point>& GetTrajectory() const {
    return trajectory;
  }
  const Circle& GetObject() const {
    return object;
  }
private:
  std::vector<Point> trajectory;
  Circle object;
  int trajectory_index = 0;
  int between_index = 0;
  const int between_cnt = 100;
};

