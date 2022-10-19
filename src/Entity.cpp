//
// Created by darkroom2 on 16/10/22.
//

#include <cmath>
#include "../include/Entity.h"
#include "../include/SpriteLoader.h"
#include "../libs/Framework/inc/Framework.h"


Entity::Entity(double x, double y) : xPos(x), yPos(y), defaultX(0), defaultY(0), xVel(0), yVel(0), width(0), height(0),
                                     currentState(EntityState::UNDEFINED), alive(true) {}

Entity::~Entity() = default;

bool Entity::isColliding(const Entity &entity) const {
    return xPos > entity.xPos && xPos < entity.xPos + entity.width && yPos > entity.yPos &&
           yPos < entity.yPos + entity.height;
}

void Entity::setDimensions(double w, double h) {
    if (width == 0 || height == 0 || (w < 0 && h < 0))
        return;

    double ratio = (double) height / (double) width;

    if (w > 0)
        width = w;
    else
        width = std::round(1 / ratio * h);

    if (h > 0)
        height = h;
    else
        height = std::round(ratio * width);

    for (auto &sprite_type: spritesByType) {
        setSpriteSize(sprite_type.second, (int) width, (int) height);
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

void Entity::resetPos() {
    setVelocity(0, 0);
    setPosition(defaultX, defaultY);
}

void Entity::takeDamage() {
    alive = false;
}

void Entity::resetState() {
    currentState = EntityState::NORMAL;
    alive = true;
    resetPos();
}

Entity::Entity(const Entity &e) = default;


Ball::Ball(double x, double y) : Entity(x, y), dirX(0), dirY(0), speed(0.5), released(false) {
    std::vector<EntityState> v{EntityState::NORMAL};
    for (const auto &state: v) {
        spritesByType.emplace(state, SpriteLoader::getSprite("ball", state));
    }
    currentState = EntityState::NORMAL;
    getSpriteSize(spritesByType.at(currentState), (int &) width, (int &) height);
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

void Ball::bounceX() {
    xVel = -1 * xVel;
}

void Ball::bounceY() {
    yVel = -1 * yVel;
}

bool Ball::lossCondition() const {
    return !alive;
}

void Ball::resetState() {
    Entity::resetState();
    released = false;
}

Ball::Ball(const Ball &b) = default;


Paddle::Paddle(double x, double y) : Entity(x, y), speed(0.5) {
    currentPerk = EntityState::UNDEFINED;
    std::vector<EntityState> v{EntityState::NORMAL};
    for (const auto &state: v) {
        spritesByType.emplace(state, SpriteLoader::getSprite("paddle", state));
    }
    currentState = EntityState::NORMAL;
    getSpriteSize(spritesByType.at(currentState), (int &) width, (int &) height);
}

void Paddle::setDimensions(double w, double h) {
    Entity::setDimensions(w, h);

    defaultWidth = width;
    maxWidth = width * 2;
    minWidth = width * 0.5;
}

void Paddle::resetDimension() {
    setDimensions(defaultWidth, 0);
};

void Paddle::resetState() {
    Entity::resetState();
    resetDimension();
}

void Paddle::setWidth(int _width) {
    if (_width >= maxWidth) {
        width = maxWidth;
    } else if (_width <= minWidth) {
        width = minWidth;
    } else {
        width = _width;
    }
}

void Paddle::setDefaultWidth(int _width) {
    defaultWidth = _width;
}


void Paddle::increase() {
    setWidth(width * 1.4);
    Entity::setDimensions(width, 0);
}

void Paddle::decrease() {
    setWidth(width * 0.6);
    Entity::setDimensions(width, height);
}

void Paddle::resetPerk() {
    currentPerk = EntityState::UNDEFINED;
    resetDimension();
}

void Paddle::setPerk(EntityState perk) {
    if (currentPerk == EntityState::UNDEFINED) {
        currentPerk = perk;
        if (perk == EntityState::POSITIVE) {
            increase();
        } else if (perk == EntityState::NEGATIVE) {
            decrease();
        }
    } else if (currentPerk == EntityState::POSITIVE && perk == EntityState::POSITIVE) {
        increase();
    } else if (currentPerk == EntityState::NEGATIVE && perk == EntityState::NEGATIVE) {
        decrease();
    } else if (currentPerk == EntityState::POSITIVE && perk == EntityState::NEGATIVE ||
               currentPerk == EntityState::NEGATIVE && perk == EntityState::POSITIVE) {
        resetPerk();
    }
}

Paddle::Paddle(const Paddle &p) = default;


Brick::Brick(double x, double y, EntityColor color) : Entity(x, y), color(color) {
    std::vector<EntityState> v{EntityState::NORMAL, EntityState::DAMAGED};
    for (const auto &state: v) {
        spritesByType.emplace(state, SpriteLoader::getSprite("brick", state, color));
    }
    currentState = EntityState::DAMAGED;
    getSpriteSize(spritesByType.at(currentState), (int &) width, (int &) height);
}

void Brick::takeDamage() {
    // for bricks to be one-hit killable I set the state to be DAMAGED in Brick constructor
    if (currentState == EntityState::DAMAGED) {
        alive = false;
    } else {
        currentState = EntityState::DAMAGED;
    }
}

Brick::Brick(const Brick &b) = default;


Perk::Perk(double x, double y, EntityState type) : Entity(x, y) {
    std::vector<EntityState> v{EntityState::POSITIVE, EntityState::NEGATIVE};
    for (const auto &state: v) {
        spritesByType.emplace(state, SpriteLoader::getSprite("perk", state));
    }
    currentState = type;
    getSpriteSize(spritesByType.at(currentState), (int &) width, (int &) height);
}

Perk::Perk(const Perk &p) = default;
