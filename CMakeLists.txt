cmake_minimum_required(VERSION 3.23)
project(arkanoid-like)

set(CMAKE_CXX_STANDARD 14)

set(LIBRARIES_DIR libs)
set(LIBRARIES Framework)

add_executable(arkanoid-like src/game.cpp)

foreach(LIBRARY ${LIBRARIES})
    add_subdirectory("${LIBRARIES_DIR}/${LIBRARY}")
endforeach(LIBRARY)

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})