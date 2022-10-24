//
// Created by darkroom2 on 16/10/22.
//

#ifndef ARKANOID_LIKE_ENTITY_H
#define ARKANOID_LIKE_ENTITY_H

#include <memory>
#include <map>
#include <vector>


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
    RED,
    UNDEFINED
};

class Entity {
public:
    explicit Entity(double x, double y);

    Entity(const Entity &e);

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
};

class Paddle : public Entity {
public:
    explicit Paddle(double x, double y, double speed = .001f);

    Paddle(const Paddle &p);

    void moveLeft(bool pressed);

    void moveRight(bool pressed);

private:
    EntityState currentPerk;
};

class Ball : public Entity {
public:
    explicit Ball(double x, double y, double speed = .0009f);

    Ball(const Ball &b);

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

class Perk : public Entity {
public:
    explicit Perk(double x, double y, EntityState type, double speed = .0007f);

    Perk(const Perk &p);
};

class Brick : public Entity {
public:
    EntityColor color;

    explicit Brick(double x, double y, EntityColor color);

    Brick(const Brick &b);

    void takeDamage() override;
};


#endif //ARKANOID_LIKE_ENTITY_H
