//
// Created by darkroom2 on 16/10/22.
//

#include <cmath>
#include "../include/Entity.h"
#include "../include/SpriteLoader.h"
#include "../libs/Framework/inc/Framework.h"


Entity::Entity(double x, double y) : xPos(x), yPos(y), defaultX(-1), defaultY(-1), xVel(0), yVel(0), width(0),
                                     height(0), defaultWidth(-1), defaultHeight(-1),
                                     currentState(EntityState::UNDEFINED), alive(true), speed(0) {}

bool Entity::isColliding(const Entity &entity) const {
    auto c1 = xPos < entity.xPos + entity.width;
    auto c2 = xPos + width > entity.xPos;
    auto c3 = yPos < entity.yPos + entity.height;
    auto c4 = height + yPos > entity.yPos;
    return c1 && c2 && c3 && c4;
}

void Entity::setDimensions(double w, double h) {
    // Width and height being 0 means that sprite wasn't yet loaded.
    if (width == 0 || height == 0 || (w < 0 && h < 0))
        return;

    auto oldWidth = width;
    auto oldHeight = height;

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

    xPos = xPos + (oldWidth - width) / 2;
    yPos = yPos + (oldHeight - height) / 2;

    if (defaultWidth == -1 && defaultHeight == -1) {
        defaultWidth = width;
        defaultHeight = height;
    }
}

void Entity::setPosition(double x, double y) {
    if (defaultX == -1 && defaultY == -1) {
        defaultX = x;
        defaultY = y;
    }

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
    setDimensions(defaultWidth, defaultHeight);
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

double Entity::getXVel() const {
    return xVel;
}

double Entity::getYVel() const {
    return yVel;
}

void Entity::setSpeed(double s) {
    speed = s;
}

double Entity::getSpeed() const {
    return speed;
}

Entity::Entity(const Entity &e) = default;


Ball::Ball(double x, double y, double speed) : Entity(x, y), dirX(0), dirY(0), released(false), paddle(nullptr) {
    std::vector<EntityState> states{EntityState::NORMAL};
    loadSprites("ball", states, EntityState::NORMAL);
    Entity::speed = speed;
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

void Ball::moveWithPaddle(bool pressed) {
    if (!isReleased()) {
        if (pressed) {
            setVelocity(paddle->getXVel(), paddle->getYVel());
        } else {
            setVelocity(0, 0);
        }
    }
}

void Ball::stickTo(Paddle *p) {
    paddle = p;
}

Ball::Ball(const Ball &b) = default;


Paddle::Paddle(double x, double y, double speed) : Entity(x, y) {
    std::vector<EntityState> states{EntityState::NORMAL};
    loadSprites("paddle", states, EntityState::NORMAL);
    Entity::speed = speed;
}

void Paddle::moveLeft(bool pressed) {
    setVelocity(pressed ? -speed : 0, 0);
}

void Paddle::moveRight(bool pressed) {
    setVelocity(pressed ? speed : 0, 0);
}

void Paddle::shrink() {
    setDimensions(width * 0.6f, height);
}

void Paddle::extend() {
    setDimensions(width * 1.4f, height);
}

void Paddle::addPerk(std::unique_ptr<Perk> perk) {
    // TODO: set lifetime to perk and in paddle.update() remove lifetime and in takeDamage undo effect
    //  (shrinked -> extend, extendended -> shrink)
    perks.push_back(std::move(perk));
}


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


Perk::Perk(double x, double y, EntityState type, double speed) : Entity(x, y) {
    std::vector<EntityState> types{EntityState::POSITIVE, EntityState::NEGATIVE};
    loadSprites("perk", types, type);
    Entity::speed = speed;
}

Perk::Perk(const Perk &p) = default;
