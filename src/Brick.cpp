//
// Created by darkroom2 on 16/10/22.
//

#include "../include/Brick.h"
#include "../libs/Framework/inc/Framework.h"

Brick::Brick(Sprite *sprite, int x, int y) : Entity(sprite, x, y) {

}

void Brick::update(unsigned int i) {
    drawSprite(sprite, getX(), getY());
}
