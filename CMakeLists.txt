cmake_minimum_required(VERSION 3.23)
project(arkanoid-like)

set(CMAKE_CXX_STANDARD 14)

set(LIBRARIES_DIR libs)
set(LIBRARIES Framework)

add_executable(arkanoid-like src/game.cpp)

foreach(LIBRARY ${LIBRARIES})
    add_subdirectory("${LIBRARIES_DIR}/${LIBRARY}")
endforeach(LIBRARY)

# Could just use target_link_libraries(${PROJECT_NAME} ${LIBRARIES}), but
# I write library name by-hand to aviod making too much changes in Framework's CMakeFile.txt
target_link_libraries(${PROJECT_NAME} PRIVATE FrameworkRelease)