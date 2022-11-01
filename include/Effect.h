//
// Created by darkroom2 on 31/10/22.
//

#ifndef ARKANOID_LIKE_EFFECT_H
#define ARKANOID_LIKE_EFFECT_H

#include "Entity.h"

class Effect {
    double timeLeft;

public:
    explicit Effect(double duration);

    virtual void update(unsigned int i);

    bool isExpired() const;

    virtual ~Effect();
};


class ShrinkEffect : public Effect {
public:
    explicit ShrinkEffect(double duration, Paddle *paddle);

    virtual ~ShrinkEffect();

    Paddle *paddle;
};

class ExtendEffect : public Effect {
public:
    explicit ExtendEffect(double duration, Paddle *paddle);

    virtual ~ExtendEffect();

    Paddle *paddle;
};

#endif //ARKANOID_LIKE_EFFECT_H
