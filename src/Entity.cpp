//
// Created by darkroom2 on 16/10/22.
//

#include "../include/Entity.h"
#include "../libs/Framework/inc/Framework.h"


Entity::Entity(int x, int y) : x_pos(x), y_pos(y), width(0), height(0), currentState(EntityState::UNDEFINED) {}

Entity::~Entity() {
    if (!sprites_by_type.empty()) {
        for (auto &sprite_type: sprites_by_type) {
            destroySprite(sprite_type.second);
            sprite_type.second = nullptr;
        }
    }
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

void Entity::addSprite(const std::string &path) {
    auto s = createSprite(path.c_str());
    int bw{};
    int bh{};
    getSpriteSize(s, bw, bh);
    double hw_ratio = (double) bh / (double) bw;
    getScreenSize(width, height);
    int brick_width = (int) std::round((double) width / (double) columns);
    int brick_height = (int) std::round(hw_ratio * brick_width);
    setSpriteSize(s, brick_width, brick_height);
    sprites_by_type.emplace(state, sprite);
    currentState = state;
}


Ball::Ball(int x, int y) : Entity(x, y) {}

void Ball::update(unsigned int i) {}


Paddle::Paddle(int x, int y) : Entity(x, y) {}

void Paddle::update(unsigned int i) {}


Brick::Brick(int x, int y) : Entity(x, y) {}

void Brick::update(unsigned int i) {
    if (sprites_by_type.contains(currentState))
        drawSprite(sprites_by_type.at(currentState), getX(), getY());
}


Perk::Perk(int x, int y) : Entity(x, y) {}

void Perk::update(unsigned int i) {}
