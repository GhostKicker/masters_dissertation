cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 17)

project( Disser )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_definitions(-pthread -D_MY -Wall -Wextra -Wshadow -Wno-unused-result -Wno-unused-const-variable -O2)

add_executable(main
  src/main.cpp
  src/rrt.h
  src/visualize.h
  src/geom.h
  src/state.h
  src/static_obstacle.h
  src/dynamic_obstacle.h
)

target_link_libraries( main PRIVATE ${OpenCV_LIBS} )
target_link_libraries( main PRIVATE Threads::Threads )

