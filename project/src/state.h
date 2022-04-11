#pragma once

#include "rrt.h"
#include "static_obstacle.h"
#include "dynamic_obstacle.h"
#include "params.h"

struct State {
  State() = delete;
  State(const Parameters& params)
      : rrt(params)
  {}

  void Update() {
    for (auto& dyn_obstacle : dynamic_obstacles) {
      dyn_obstacle.GoNextState();
    }
    rrt.Update();
  }

  RRT rrt;
  std::vector<StaticObstacle> static_obstacles;
  std::vector<DynamicObstacle> dynamic_obstacles;

};
