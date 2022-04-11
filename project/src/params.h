#pragma once

#include "geom.h"

struct RRTParameters {
  const double window_height = 650;
  const double window_width = 1100;
  const double steer_radius = 30;
  const Point start_point{window_width/2, window_height/2};
  const double min_distance_to_obstacles = 10.0;
  const size_t num_closest = 7;
};

struct VisualizatorParameters {
  const double window_height = 650;
  const double window_width = 1100;
};

struct Parameters {
  Parameters() = default;
  RRTParameters rrt_params;
  VisualizatorParameters viz_params;
};
