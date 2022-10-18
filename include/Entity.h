//
// Created by darkroom2 on 16/10/22.
//

#ifndef ARKANOID_LIKE_ENTITY_H
#define ARKANOID_LIKE_ENTITY_H

#include <memory>
#include <map>


class Sprite;

enum class EntityState {
    NORMAL,
    DAMAGED,
    POSITIVE,
    NEGATIVE,
    UNDEFINED
};

enum class EntityColor {
    GREEN,
    RED
};

class Entity {
public:
    double xPos;
    double yPos;
    double xVel;
    double yVel;
    double defaultX;
    double defaultY;
    int width;
    int height;

    EntityState currentState;
    std::map<EntityState, Sprite *> spritesByType;

    explicit Entity(double x, double y);

    Entity(const Entity &e);

    virtual ~Entity();

    virtual void update(unsigned int i);

    virtual bool isColliding(const Entity &entity) const;

    virtual void setDimensions(int w, int h);

    virtual void setPosition(double x, double y);

    virtual void setVelocity(double vx, double vy);

    virtual void reset();
};

class Ball : public Entity {
public:
    explicit Ball(double x, double y);

    Ball(const Ball &b);

    void setDirection(int mouseX, int mouseY);

    void release();

    double dirX;
    double dirY;
    double speed;
    bool released;

    void reset() override;
};

class Paddle : public Entity {
public:
    explicit Paddle(double x, double y);

    Paddle(const Paddle &p);
};

class Brick : public Entity {
public:
    explicit Brick(double x, double y, EntityColor color);

    Brick(const Brick &b);
};

class Perk : public Entity {
public:
    explicit Perk(double x, double y);

    Perk(const Perk &p);
};

#endif //ARKANOID_LIKE_ENTITY_H
