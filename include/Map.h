//
// Created by darkroom2 on 16/10/22.
//

#ifndef ARKANOID_LIKE_MAP_H
#define ARKANOID_LIKE_MAP_H


#include <vector>
#include <memory>
#include "Entity.h"

class Map : public Entity {
public:
    explicit Map(int x, int y, int width, int height, int lines, int columns);

    void update(unsigned int i) override;

private:
    std::vector<std::unique_ptr<Brick>> bricks;
    std::vector<std::unique_ptr<Entity>> entities;
};


#endif //ARKANOID_LIKE_MAP_H
