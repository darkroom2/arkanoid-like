//
// Created by darkroom2 on 16/10/22.
//

#ifndef ARKANOID_LIKE_MAP_H
#define ARKANOID_LIKE_MAP_H


#include <vector>
#include <memory>
#include "Brick.h"

class Map : public Entity {
public:
    explicit Map(Sprite *sprite = nullptr, int x = 0, int y = 0, int lines = 6, int columns = 11);
    void update(unsigned int i) override;

private:
    std::vector<std::unique_ptr<Brick>> bricks;
};


#endif //ARKANOID_LIKE_MAP_H
