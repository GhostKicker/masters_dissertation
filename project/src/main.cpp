#include "rrt.h"
#include "visualize.h"
#include "geom.h"
#include "static_obstacle.h"
#include "params.h"

using namespace std;

void Initialize(State& state) {
  state.static_obstacles = {
    StaticObstacle(Polygon({Point(500, 150), 
                            Point(500, 200),
                            Point(450, 200),
                            Point(450, 300),
                            Point(350, 300),
                            Point(350, 250),
                            Point(400, 250),
                            Point(400, 150)})),

    StaticObstacle(Polygon({Point(450, 350), 
                            Point(450, 500),
                            Point(400, 500),
                            Point(400, 350)})),
  };
  state.dynamic_obstacles = {
    DynamicObstacle({
        Point(350, 600),
        Point(350, 340),
        Point(200, 270),
        Point(200, 470),
        Point(350, 600)},
        30),
    DynamicObstacle({
        Point(525, 400),
        Point(650, 400),
        Point(650, 250),
        Point(525, 250),
        Point(650, 250),
        Point(650, 400),
        Point(525, 400)},
        30)
  };

  state.rrt.SetStaticObstacles(&state.static_obstacles);
  state.rrt.SetDynamicObstacles(&state.dynamic_obstacles);

  for (int i = 0; i < 3500; ++i) {
    state.rrt.AddRandomPoint();
  }
}

int main() {
  Parameters params;
  State state(params);
  Initialize(state);
  while (true) {
    Visualizator viz(params);
    state.Update();
    viz.DrawState(state);
    viz.Show();
  }
}
