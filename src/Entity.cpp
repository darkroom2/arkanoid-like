//
// Created by darkroom2 on 16/10/22.
//

#include <cmath>
#include "../include/Entity.h"
#include "../include/SpriteLoader.h"
#include "../libs/Framework/inc/Framework.h"


Entity::Entity(double x, double y) : xPos(x), yPos(y), defaultX(0), defaultY(0), xVel(0), yVel(0), width(0), height(0),
                                     currentState(EntityState::UNDEFINED), alive(true), speed(0) {}

bool Entity::isColliding(const Entity &entity) const {
    return xPos > entity.xPos && xPos < entity.xPos + entity.width && yPos > entity.yPos &&
           yPos < entity.yPos + entity.height;
}

void Entity::setDimensions(double w, double h) {
    if (width == 0 || height == 0 || (w < 0 && h < 0))
        return;

    double ratio = height / width;

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
    if (spritesByType.contains(currentState)) {
        drawSprite(spritesByType.at(currentState), (int) xPos, (int) yPos);
    }
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
    resetPos();
    currentState = EntityState::NORMAL;
    alive = true;
}

void Entity::loadSprites(const std::string &name, std::vector<EntityState> &states, const EntityState &default_state,
                         const EntityColor &color) {
    for (const auto &state: states) {
        spritesByType.emplace(state, SpriteLoader::getSprite(name, state, color));
    }
    currentState = default_state;
    int w, h;
    getSpriteSize(spritesByType.at(currentState), w, h);
    width = w;
    height = h;
}

void Entity::setSpeed(double value) {
    speed = value;
}

Entity::Entity(const Entity &e) = default;


Ball::Ball(double x, double y, double speed) : Entity(x, y), dirX(0), dirY(0), released(false) {
    std::vector<EntityState> states{EntityState::NORMAL};
    loadSprites("ball", states, EntityState::NORMAL);
    Entity::speed = width * speed;
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
    xVel = -xVel;
}

void Ball::bounceY() {
    yVel = -yVel;
}

bool Ball::lossCondition() const {
    return !alive;
}

void Ball::resetState() {
    Entity::resetState();
    released = false;
}

bool Ball::isReleased() const {
    return released;
}

Ball::Ball(const Ball &b) = default;


Paddle::Paddle(double x, double y, double speed) : Entity(x, y), currentPerk(EntityState::UNDEFINED) {
    std::vector<EntityState> states{EntityState::NORMAL};
    loadSprites("paddle", states, EntityState::NORMAL);
}

void Paddle::setPerk(EntityState perk) {
    currentPerk = perk;
}

Paddle::Paddle(const Paddle &p) = default;


Brick::Brick(double x, double y, EntityColor color) : Entity(x, y), color(color) {
    std::vector<EntityState> states{EntityState::NORMAL, EntityState::DAMAGED};
    loadSprites("brick", states, EntityState::DAMAGED, color);
}

void Brick::takeDamage() {
    // for bricks to be one-hit killable I set the state to be DAMAGED in Brick constructor
    if (currentState == EntityState::DAMAGED) {
        Entity::takeDamage();
    } else {
        currentState = EntityState::DAMAGED;
    }
}

Brick::Brick(const Brick &b) = default;


Perk::Perk(double x, double y, EntityState type) : Entity(x, y) {
    std::vector<EntityState> types{EntityState::POSITIVE, EntityState::NEGATIVE};
    loadSprites("perk", types, type);
}

Perk::Perk(const Perk &p) = default;
