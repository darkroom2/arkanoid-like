//
// Created by darkroom2 on 16/10/22.
//

#include <cmath>
#include <iostream>
#include "../include/GameState.h"
#include "../include/Game.h"


GameState::GameState(Game *game) : game(game) {}

GameState::~GameState() = default;


StartGameState::StartGameState(Game *game) : GameState(game) {}

void StartGameState::update(unsigned int i) {}

void StartGameState::handleMouseMove(int x, int y, int xrel, int yrel) {}

void StartGameState::handleKey(FRKey key, bool pressed) {}

void StartGameState::handleMouseKey(FRMouseButton button, bool released) {
    if (button == FRMouseButton::LEFT && released) {
        game->setCurrentState("GameplayGameState");
    }
}


GameplayGameState::GameplayGameState(Game *game) : GameState(game) {
    int w{}, h{};
    getScreenSize(w, h);

    int brickLines = 6;
    int brickColumns = 11;
    map = std::make_unique<Map>(0, 0, w, h, brickLines, brickColumns);

    int borderPadding = 5;
    int paddleProportion = 5;
    int paddleWidth = (int) std::round((double) w / (double) paddleProportion);
    paddle = std::make_unique<Paddle>(0, 0);
    paddle->setDimensions(paddleWidth, 0);
    paddle->setPosition((double) w / 2 - (double) paddle->width / 2, h - paddle->height - borderPadding);

    ball = std::make_unique<Ball>(0, 0);
    ball->setDimensions(0, paddle->height / 2);
    ball->setPosition(paddle->xPos + (double) paddle->width / 2 - (double) ball->width / 2, paddle->yPos - ball->height);
}

void GameplayGameState::update(unsigned int i) {
    map->update(i);
    paddle->update(i);
    ball->update(i);
}

void GameplayGameState::handleKey(FRKey key, bool pressed) {
    if (key == FRKey::LEFT) {
        paddle->setVelocity(pressed ? -5 : 0, 0);
        if (!ball->released)
            ball->setVelocity(pressed ? -5 : 0, 0);
    } else if (key == FRKey::RIGHT) {
        paddle->setVelocity(pressed ? 5 : 0, 0);
        if (!ball->released)
            ball->setVelocity(pressed ? 5 : 0, 0);
    }
}

void GameplayGameState::handleMouseMove(int x, int y, int xrel, int yrel) {
    ball->setDirection(x, y);
}

void GameplayGameState::handleMouseKey(FRMouseButton button, bool released) {
    if (button == FRMouseButton::LEFT && released) {
        if (!ball->released)
            ball->release();
    }
    if (button == FRMouseButton::RIGHT && released) {
        ball->reset();
        paddle->reset();
    }
}
