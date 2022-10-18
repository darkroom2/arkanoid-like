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
    int x_pos;
    int y_pos;
    int width;
    int height;

    EntityState currentState;
    std::map<EntityState, Sprite *> sprites_by_type;

    explicit Entity(int x = 0, int y = 0);

    Entity(const Entity &e);

    virtual ~Entity();

    virtual void update(unsigned int i);

    bool isColliding(const Entity &entity) const;

    int getX() const;

    int getY() const;

    void setX(int x);

    void setY(int y);

    void setDimensions(int w = -1, int h = -1);

    void setPosition(int x, int y);


};

class Ball : public Entity {
public:
    explicit Ball(int x, int y);

    Ball(const Ball &b);
};

class Paddle : public Entity {
public:
    explicit Paddle(int x, int y);

    Paddle(const Paddle &p);
};

class Brick : public Entity {
public:
    explicit Brick(int x, int y, EntityColor color);

    Brick(const Brick &b);
};

class Perk : public Entity {
public:
    explicit Perk(int x, int y);

    Perk(const Perk &p);
};

#endif //ARKANOID_LIKE_ENTITY_H
