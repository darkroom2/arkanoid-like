//
// Created by darkroom2 on 16/10/22.
//

#include <cmath>
#include "../include/Entity.h"
#include "../include/SpriteLoader.h"
#include "../libs/Framework/inc/Framework.h"


Entity::Entity(int x, int y) : x_pos(x), y_pos(y), width(0), height(0), currentState(EntityState::UNDEFINED) {}

Entity::~Entity() = default;

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

void Entity::setDimensions(int w, int h) {
    if (width == 0 || height == 0 || (w < 0 && h < 0))
        return;

    double ratio = (double) height / (double) width;

    if (w > 0)
        width = w;
    else
        width = (int) std::round(1 / ratio * h);

    if (h > 0)
        height = h;
    else
        height = (int) std::round(ratio * width);

    for (auto &sprite_type: sprites_by_type) {
        setSpriteSize(sprite_type.second, width, height);
    }
}

void Entity::setPosition(int x, int y) {
    x_pos = x;
    y_pos = y;
}

void Entity::update(unsigned int i) {
    if (sprites_by_type.contains(currentState))
        drawSprite(sprites_by_type.at(currentState), getX(), getY());
}

Entity::Entity(const Entity &e) = default;


Ball::Ball(int x, int y) : Entity(x, y) {
    std::vector<EntityState> v{EntityState::NORMAL};
    for (const auto &state: v) {
        sprites_by_type.emplace(state, SpriteLoader::getSprite("ball", state));
    }
    currentState = EntityState::NORMAL;
    getSpriteSize(sprites_by_type.at(currentState), width, height);
}

Ball::Ball(const Ball &b) = default;


Paddle::Paddle(int x, int y) : Entity(x, y) {
    std::vector<EntityState> v{EntityState::NORMAL};
    for (const auto &state: v) {
        sprites_by_type.emplace(state, SpriteLoader::getSprite("paddle", state));
    }
    currentState = EntityState::NORMAL;
    getSpriteSize(sprites_by_type.at(currentState), width, height);
}

Paddle::Paddle(const Paddle &p) = default;


Brick::Brick(int x, int y, EntityColor color) : Entity(x, y) {
    std::vector<EntityState> v{EntityState::NORMAL, EntityState::DAMAGED};
    for (const auto &state: v) {
        sprites_by_type.emplace(state, SpriteLoader::getSprite("brick", state, color));
    }
    currentState = EntityState::NORMAL;
    getSpriteSize(sprites_by_type.at(currentState), width, height);
}

Brick::Brick(const Brick &b) = default;


Perk::Perk(int x, int y) : Entity(x, y) {
    std::vector<EntityState> v{EntityState::POSITIVE, EntityState::NEGATIVE};
    for (const auto &state: v) {
        sprites_by_type.emplace(state, SpriteLoader::getSprite("perk", state));
    }
    currentState = EntityState::POSITIVE;
    getSpriteSize(sprites_by_type.at(currentState), width, height);
}

Perk::Perk(const Perk &p) = default;
