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

class Entity {
public:
    int x_pos;
    int y_pos;
    int width;
    int height;

    EntityState currentState;
    std::map<EntityState, Sprite *> sprites_by_type;

    explicit Entity(int x = 0, int y = 0);

    virtual ~Entity();

    virtual void update(unsigned int i) = 0;

    bool isColliding(const Entity &entity) const;

    int getX() const;

    int getY() const;

    void setX(int x);

    void setY(int y);

    void addSprite(const std::string &path);
};

class Ball : public Entity {
public:
    explicit Ball(int x, int y);

    void update(unsigned int i) override;
};

class Paddle : public Entity {
public:
    explicit Paddle(int x, int y);

    void update(unsigned int i) override;
};

class Brick : public Entity {
public:
    explicit Brick(int x, int y);

    void update(unsigned int i) override;
};

class Perk : public Entity {
public:
    explicit Perk(int x, int y);

    void update(unsigned int i) override;
};

#endif //ARKANOID_LIKE_ENTITY_H
