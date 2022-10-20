cmake_minimum_required(VERSION 3.20)
project(arkanoid-like)

set(CMAKE_CXX_STANDARD 20)

set(LIBRARIES_DIR libs)
set(LIBRARIES Framework cxxopts)

add_executable(arkanoid-like src/arkanoidlike.cpp src/GameState.cpp include/GameState.h src/Game.cpp include/Game.h src/Entity.cpp include/Entity.h src/Map.cpp include/Map.h src/SpriteLoader.cpp include/SpriteLoader.h)

foreach (LIBRARY ${LIBRARIES})
    add_subdirectory("${LIBRARIES_DIR}/${LIBRARY}")
endforeach (LIBRARY)

target_link_libraries(arkanoid-like PRIVATE FrameworkRelease PUBLIC cxxopts)

add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data)
add_dependencies(arkanoid-like copy_assets)
