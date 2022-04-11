#pragma once

#include "geom.h"
#include "static_obstacle.h"
#include "dynamic_obstacle.h"
#include "params.h"

#include <algorithm>
#include <vector>
#include <optional>
#include <random>
#include <set>

struct Vertex {
  Point coords;
  std::optional<int> parent;
  int index = -1;
  double distance_to_root = 0;

  Vertex(){}
  Vertex(const Point& _coords)
      : coords(_coords)
  {}
};

struct Edge {
  enum EdgeState {
    NORMAL,
    BLOCKED,
    ORPHANED,
  };

  int from = -1, to = -1;
  EdgeState state{EdgeState::NORMAL};

  Edge() = default;
  Edge(int _from, int _to) 
      : from(_from)
      , to(_to)
  {}
};

class RRT {
public:
  RRT() = delete;
  RRT(const Parameters& params)
      : min_distance_to_obstacles(params.rrt_params.min_distance_to_obstacles)
      , height(params.rrt_params.window_height)
      , width(params.rrt_params.window_width)
      , radius(params.rrt_params.steer_radius)
      , num_closest(params.rrt_params.num_closest) {
    AddPoint(params.rrt_params.start_point);
  }

  void AddRandomPoint() {
    AddPoint(Point(std::uniform_real_distribution<double>(0, width)(rng),
                   std::uniform_real_distribution<double>(0, height)(rng)));
  }

  void AddPoint(const Point& pt) {
    Vertex new_vertex(pt);
    new_vertex.index = vertices.size();
    new_vertex.parent = GetBestParent(pt);

    if (new_vertex.parent){
      int parent = new_vertex.parent.value();
      const auto& parent_vertex = vertices[parent];
      new_vertex.coords = Steer(pt, parent_vertex.coords);
      if (IntersectsWithStaticObstacles(Segment(parent_vertex.coords, new_vertex.coords))) {
        return;
      }
      graph[parent].push_back(Edge(parent, new_vertex.index));
      new_vertex.distance_to_root = 
          parent_vertex.distance_to_root + Distance(new_vertex.coords, parent_vertex.coords);
    }

    vertices.push_back(std::move(new_vertex));
    graph.push_back({});
  }

  const std::optional<int> GetBestParent_Linear(const Point& point) const {
    auto it = std::min_element(
        vertices.begin(),
        vertices.end(),
        [&](const Vertex &lhs, const Vertex &rhs) -> bool {
          return Distance(point, lhs.coords) < Distance(point, rhs.coords);
        });
    return it != vertices.end()
      ? std::optional<int>(std::distance(vertices.begin(), it)) 
      : std::optional<int>();
  }

  const std::optional<int> GetBestParent(const Point& point) const {
    std::set<std::pair<double, int>> closest;
    for (const auto& vertex : vertices) {
      closest.insert({Distance(vertex.coords, point), vertex.index});
      if (closest.size() > num_closest) {
        closest.erase(*closest.rbegin());
      }
    }
    auto it = std::min_element(
        closest.begin(),
        closest.end(),
        [&](const std::pair<double, int>& lhs, const std::pair<double, int>& rhs) {
          return vertices[lhs.second].distance_to_root + Distance(vertices[lhs.second].coords, point)
               < vertices[rhs.second].distance_to_root + Distance(vertices[rhs.second].coords, point);
        });
    return it != closest.end()
      ? std::optional<int>(vertices[it->second].index) 
      : std::optional<int>();
  }

  const std::vector<std::vector<Edge>>& GetGraph() const {
    return graph;
  }

  const std::vector<Vertex>& GetVertices() const {
    return vertices;
  }

  void SetStaticObstacles(const std::vector<StaticObstacle>* _static_obstacles_ptr) {
    static_obstacles_ptr = _static_obstacles_ptr;
  }

  void SetDynamicObstacles(const std::vector<DynamicObstacle>* _dynamic_obstacles_ptr) {
    dynamic_obstacles_ptr = _dynamic_obstacles_ptr;
  }

  bool IsEdgeBlocked(const Edge& edge) {
    return IntersectsWithStaticObstacles(
        Segment(vertices[edge.from].coords, vertices[edge.to].coords)) ||
        IntersectsWithDynamicObstacles(
            Segment(vertices[edge.from].coords, vertices[edge.to].coords));
  }


  void Update() {
    for (auto& edges_list : graph) {
      for (auto& edge : edges_list) {
        if (IsEdgeBlocked(edge) && edge.state != Edge::EdgeState::BLOCKED) {
          edge.state = Edge::EdgeState::BLOCKED;
        }
        if (!IsEdgeBlocked(edge) && edge.state == Edge::EdgeState::BLOCKED) {
          edge.state = Edge::EdgeState::NORMAL;
        }
      }
    }

    std::function<void(int, bool)> dfs = [&](int v, bool was_blocked) {
      for (auto& e : graph[v]) {
        bool new_blocked = was_blocked || e.state == Edge::EdgeState::BLOCKED;
        if (new_blocked && e.state == Edge::EdgeState::NORMAL) {
          e.state = Edge::EdgeState::ORPHANED;
        }
        if (!new_blocked && e.state == Edge::EdgeState::ORPHANED) {
          e.state = Edge::EdgeState::NORMAL;
        }
        dfs(e.to, new_blocked);
      }
    };

    dfs(0, false);
  }

private:

  Point Steer(const Point& new_point, const Point& old_point) {
    double dist = Distance(new_point, old_point);
    if (dist <= radius) {
      return new_point;
    }
    return (new_point - old_point) / dist * radius + old_point;
  }

  bool IntersectsWithStaticObstacles(const Segment& s) {
    if (!static_obstacles_ptr) {
      return false;
    }
    for (const auto& obstacle : *static_obstacles_ptr) {
      if (Distance(obstacle.GetPolygon(), s) < min_distance_to_obstacles) {
        return true;
      }
    }
    return false;
  }

  bool IntersectsWithDynamicObstacles(const Segment& s) {
    if (!dynamic_obstacles_ptr) {
      return false;
    }
    for (const auto& obstacle : *dynamic_obstacles_ptr) {
      if (Distance(obstacle.GetObject(), s) < min_distance_to_obstacles) {
        return true;
      }
    }
    return false;
  }

  const double min_distance_to_obstacles = 10.0;

  double height;
  double width;
  double radius;

  const size_t num_closest = 7;

  std::mt19937_64 rng{1};

  std::vector<Vertex> vertices;
  std::vector<std::vector<Edge>> graph;

  const std::vector<StaticObstacle>* static_obstacles_ptr{nullptr};
  const std::vector<DynamicObstacle>* dynamic_obstacles_ptr{nullptr};
};
