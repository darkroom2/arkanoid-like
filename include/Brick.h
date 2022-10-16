//
// Created by darkroom2 on 16/10/22.
//

#ifndef ARKANOID_LIKE_BRICK_H
#define ARKANOID_LIKE_BRICK_H


#include "Entity.h"

class Brick : public Entity {
public:
    explicit Brick(Sprite *sprite, int x, int y);
    void update(unsigned int i) override;
};


#endif //ARKANOID_LIKE_BRICK_H
