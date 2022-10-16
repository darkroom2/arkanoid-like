//
// Created by darkroom2 on 16/10/22.
//

#ifndef ARKANOID_LIKE_ENTITY_H
#define ARKANOID_LIKE_ENTITY_H

#include <memory>


class Sprite;

class Entity {
public:
    Sprite *sprite;
    int x_pos;
    int y_pos;
    int width;
    int height;

    explicit Entity(Sprite *sprite = nullptr, int x = 0, int y = 0);
    virtual ~Entity();

    virtual void update(unsigned int i) = 0;
    bool isColliding(const Entity &entity) const;

    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);

    void setSprite(Sprite *pSprite);
};

class Ball : public Entity {
public:
    explicit Ball(Sprite *sprite, int x, int y);
    void update(unsigned int i) override;
};

class Paddle : public Entity {
public:
    explicit Paddle(Sprite *sprite, int x, int y);
    void update(unsigned int i) override;
};


#endif //ARKANOID_LIKE_ENTITY_H
