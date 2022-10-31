//
// Created by darkroom2 on 31/10/22.
//

#include "../include/Effect.h"

bool Effect::isExpired() const {
    return timeLeft <= 0;
}

void Effect::update(unsigned int i) {
    timeLeft -= i;
}


Effect::Effect(double duration) : timeLeft(duration) {}


ShrinkEffect::ShrinkEffect(double duration, Paddle *paddle) : Effect(duration), paddle(paddle) {
    paddle->shrink();
}

ShrinkEffect::~ShrinkEffect() {
    paddle->extend();
}


ExtendEffect::ExtendEffect(double duration, Paddle *paddle) : Effect(duration), paddle(paddle) {
    paddle->extend();
}

ExtendEffect::~ExtendEffect() {
    paddle->shrink();
}
