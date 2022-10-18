//
// Created by darkroom2 on 16/10/22.
//

#include "../include/Entity.h"
#include "../libs/Framework/inc/Framework.h"

Entity::Entity(Sprite *sprite, int x, int y) : x_pos(x), y_pos(y), width(0), height(0) {
    setSprite(sprite);
}

Entity::~Entity() {
    if (sprite)
        destroySprite(sprite);
}

bool Entity::isColliding(const Entity &entity) const {
    return getX() < entity.getX() + entity.width && getX() + width > entity.getX() &&
           getY() > entity.getY() + entity.height && getY() + height < entity.getY();
}

int Entity::getX() const {
    return x_pos;
}

int Entity::getY() const {
    return y_pos;
}

void Entity::setX(int x) {
    x_pos = x;
}

void Entity::setY(int y) {
    y_pos = y;
}

void Entity::setSprite(Sprite *pSprite) {
    sprite = pSprite;
    if (sprite)
        getSpriteSize(sprite, width, height);
}

Ball::Ball(Sprite *sprite, int x, int y) : Entity(sprite, x, y) {}
void Ball::update(unsigned int i) {}

Paddle::Paddle(Sprite *sprite, int x, int y) : Entity(sprite, x, y) {}
void Paddle::update(unsigned int i) {}
