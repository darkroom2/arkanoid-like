//
// Created by darkroom2 on 16/10/22.
//

#ifndef ARKANOID_LIKE_ENTITY_H
#define ARKANOID_LIKE_ENTITY_H

#include <memory>
#include <map>
#include <vector>
#include "EntityConstants.h"
#include "Effect.h"

class Sprite;

class Entity {
public:
    explicit Entity(double x, double y);

    double height;
    double width;
    double xPos;
    double yPos;
    EntityState currentState;
    bool alive;

    virtual void update(unsigned int i);

    virtual void takeDamage();

    virtual bool isColliding(const Entity &entity) const;

    virtual void setDimensions(double w, double h);

    virtual void setPosition(double x, double y);

    void loadSprites(const std::string &name, std::vector<EntityState> &states, const EntityState &default_state,
                     const EntityColor &color = EntityColor::UNDEFINED);

    void setSpeed(double speed);

    double getSpeed() const;

    virtual void resetState();

    virtual void setVelocity(double vx, double vy);

    double getXVel() const;

    double getYVel() const;

private:
    double defaultX;
    double defaultY;

    virtual void resetPos();

protected:
    std::map<EntityState, Sprite *> spritesByType;
    double xVel;
    double yVel;
    double speed;
    double defaultWidth;
    double defaultHeight;
};

class Perk : public Entity {
public:
    explicit Perk(double x, double y, EntityState type, double speed = .0007f);
};

class Paddle : public Entity {
public:
    double maxWidth;
    double minWidth;

    explicit Paddle(double x, double y, double speed = .001f);

    void moveLeft(bool pressed);

    void moveRight(bool pressed);

    void shrink();

    void extend();

    void addEffect(EntityState perkType);

    void setDimensions(double w, double h) override;

    void update(unsigned int i) override;

private:
    std::vector<std::unique_ptr<Effect>> effects;
};

class Ball : public Entity {
public:
    explicit Ball(double x, double y, double speed = .0009f);

    bool lossCondition() const;

    void bounceY();

    void bounceX();

    void setDirection(int mouseX, int mouseY);

    void release();

    void resetState() override;

    void moveWithPaddle(bool pressed);

    void stickTo(Paddle *paddle);

    bool isReleased() const;

private:
    int dirX;
    int dirY;
    bool released;
    const Paddle *paddle;
};

class Brick : public Entity {
public:
    EntityColor color;

    explicit Brick(double x, double y, EntityColor color);

    void takeDamage() override;
};

#endif //ARKANOID_LIKE_ENTITY_H
