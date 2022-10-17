cmake_minimum_required(VERSION 3.20)
project(arkanoid-like)

set(CMAKE_CXX_STANDARD 20)

set(LIBRARIES_DIR libs)
set(LIBRARIES Framework cxxopts)

add_executable(arkanoid-like src/arkanoidlike.cpp src/GameState.cpp include/GameState.h src/Game.cpp include/Game.h src/Entity.cpp include/Entity.h src/Map.cpp include/Map.h src/SpriteLoader.cpp include/SpriteLoader.h)

foreach (LIBRARY ${LIBRARIES})
    add_subdirectory("${LIBRARIES_DIR}/${LIBRARY}")
endforeach (LIBRARY)

# Could just use target_link_libraries(${PROJECT_NAME} ${LIBRARIES}), but
# I write library name by-hand to aviod making too much changes in Framework's CMakeFile.txt
target_link_libraries(${PROJECT_NAME} PRIVATE FrameworkRelease PUBLIC cxxopts)