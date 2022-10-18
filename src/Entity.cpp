//
// Created by darkroom2 on 16/10/22.
//

#include <cmath>
#include "../include/Entity.h"
#include "../include/SpriteLoader.h"
#include "../libs/Framework/inc/Framework.h"


Entity::Entity(double x, double y) : xPos(x), yPos(y), defaultX(0), defaultY(0), xVel(0), yVel(0), width(0), height(0),
                                     currentState(EntityState::UNDEFINED) {}

Entity::~Entity() = default;

bool Entity::isColliding(const Entity &entity) const {
    return xPos < entity.xPos + entity.width && xPos + width > entity.xPos &&
           yPos > entity.yPos + entity.height && yPos + height < entity.yPos;
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

    for (auto &sprite_type: spritesByType) {
        setSpriteSize(sprite_type.second, width, height);
    }
}

void Entity::setPosition(double x, double y) {
    defaultX = x;
    defaultY = y;

    xPos = x;
    yPos = y;
}

void Entity::setVelocity(double vx, double vy) {
    xVel = vx;
    yVel = vy;
}

void Entity::update(unsigned int i) {
    if (spritesByType.contains(currentState))
        drawSprite(spritesByType.at(currentState), (int) xPos, (int) yPos);
    xPos += xVel;
    yPos += yVel;
}

void Entity::reset() {
    setVelocity(0, 0);
    setPosition(defaultX, defaultY);
}

Entity::Entity(const Entity &e) = default;


Ball::Ball(double x, double y) : Entity(x, y), dirX(0), dirY(0), speed(5), released(false) {
    std::vector<EntityState> v{EntityState::NORMAL};
    for (const auto &state: v) {
        spritesByType.emplace(state, SpriteLoader::getSprite("ball", state));
    }
    currentState = EntityState::NORMAL;
    getSpriteSize(spritesByType.at(currentState), width, height);
}

void Ball::setDirection(int mouseX, int mouseY) {
    dirX = mouseX;
    dirY = mouseY;
}

void Ball::release() {
    double angle = atan2(dirY - yPos, dirX - xPos);
    double vy = speed * std::sin(angle);
    double vx = speed * std::cos(angle);
    setVelocity(vx, vy);
    released = true;
}

void Ball::reset() {
    Entity::reset();
    released = false;
}

Ball::Ball(const Ball &b) = default;


Paddle::Paddle(double x, double y) : Entity(x, y) {
    std::vector<EntityState> v{EntityState::NORMAL};
    for (const auto &state: v) {
        spritesByType.emplace(state, SpriteLoader::getSprite("paddle", state));
    }
    currentState = EntityState::NORMAL;
    getSpriteSize(spritesByType.at(currentState), width, height);
}

Paddle::Paddle(const Paddle &p) = default;


Brick::Brick(double x, double y, EntityColor color) : Entity(x, y) {
    std::vector<EntityState> v{EntityState::NORMAL, EntityState::DAMAGED};
    for (const auto &state: v) {
        spritesByType.emplace(state, SpriteLoader::getSprite("brick", state, color));
    }
    currentState = EntityState::NORMAL;
    getSpriteSize(spritesByType.at(currentState), width, height);
}

Brick::Brick(const Brick &b) = default;


Perk::Perk(double x, double y) : Entity(x, y) {
    std::vector<EntityState> v{EntityState::POSITIVE, EntityState::NEGATIVE};
    for (const auto &state: v) {
        spritesByType.emplace(state, SpriteLoader::getSprite("perk", state));
    }
    currentState = EntityState::POSITIVE;
    getSpriteSize(spritesByType.at(currentState), width, height);
}

Perk::Perk(const Perk &p) = default;
