#pragma once

#include "rrt.h"
#include "state.h"
#include "static_obstacle.h"

#include <opencv2/opencv.hpp>

class Visualizator {
public:

  Visualizator() = delete;
  Visualizator(const Parameters& params)
      : picture(cv::Mat3b(params.viz_params.window_height, params.viz_params.window_width)) {
    picture.setTo(cv::Scalar::all(255));
  }

  void Show() {
    cv::imshow("viz", picture);
    auto current_key = cv::waitKey(10);
    if (current_key == 27) {
      cv::destroyAllWindows();
      exit(0);
    }
  }

  void DrawLine(const Point& from, const Point& to, cv::Scalar color = cv::Scalar(0, 125, 0)) {
    cv::line(
        picture,
        cv::Point(from.x, picture.rows - from.y),
        cv::Point(to.x, picture.rows - to.y),
        color,
        2);
  }

  void DrawPoint(const Point& pt) {
    cv::circle(
        picture,
        cv::Point(pt.x, picture.rows - pt.y),
        3,
        cv::Scalar(100, 0, 0),
        -1);
  }

  void DrawCircle(const Circle& c) {
    cv::circle(
      picture,
      cv::Point(c.c.x, picture.rows - c.c.y),
      c.r,
      cv::Scalar(0, 0, 100),
      -1);
  }

  void DrawState(const State& state) {
    DrawDynamicObstacles(state.dynamic_obstacles);
    DrawRRT(state.rrt);
    DrawStaticObstacles(state.static_obstacles);
  }

private:

  void DrawDynamicObstacle(const DynamicObstacle& obstacle) {
    const std::vector<Point>& trajectory = obstacle.GetTrajectory();
    for (const auto& pt : trajectory) {
      DrawPoint(pt);
    }
    for (int i = 0; i + 1 < static_cast<int>(trajectory.size()); ++i) {
      DrawLine(trajectory[i], trajectory[i + 1], cv::Scalar(100, 100, 0));
    }
    const Circle& object = obstacle.GetObject();
    DrawCircle(object);
  }

  void DrawDynamicObstacles(const std::vector<DynamicObstacle>& dynamic_obstacles) {
    for (const auto& obstacle : dynamic_obstacles) {
      DrawDynamicObstacle(obstacle);
    }
  }

  void DrawStaticObstacle(const StaticObstacle& obstacle) {
    std::vector<cv::Point> points;
    const Polygon& poly = obstacle.GetPolygon();
    points.reserve(poly.points.size());
    for (int i = 0; i < static_cast<int>(poly.points.size()); ++i) {
      DrawLine(poly.points[i], poly.points[(i + 1) % poly.points.size()], cv::Scalar(0, 0, 0));
    }
    for (const auto& pt : poly.points) {
      points.push_back(cv::Point(pt.x, picture.rows - pt.y));
    }
    cv::fillConvexPoly(picture, points, cv::Scalar(0, 200, 200));
  }

  void DrawStaticObstacles(const std::vector<StaticObstacle>& static_obstacles) {
    for (const auto& obstacle : static_obstacles) {
      DrawStaticObstacle(obstacle);
    }
  }

  void DrawRRT(const RRT& rrt) {
    const auto& vertices = rrt.GetVertices();
    const auto& graph = rrt.GetGraph();
    for (const auto& connect_list : graph) {
      for (const auto& edge : connect_list) {
        if (edge.state == Edge::EdgeState::NORMAL) {
          DrawLine(vertices[edge.from].coords, vertices[edge.to].coords);
        } else if (edge.state == Edge::EdgeState::BLOCKED) {
          DrawLine(vertices[edge.from].coords, vertices[edge.to].coords, cv::Scalar(0, 0, 255));
        } else if (edge.state == Edge::EdgeState::ORPHANED) {
          DrawLine(vertices[edge.from].coords, vertices[edge.to].coords, cv::Scalar(0, 200, 200));
        }
      }
    }
    for (const auto& vertex : vertices) {
      DrawPoint(vertex.coords);
    }
  }

  cv::Mat3b picture;
  std::string window_name{"viz"};
};
