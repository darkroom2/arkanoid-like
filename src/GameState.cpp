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
    paddle->setPosition(w / 2 - paddle->width / 2, h - paddle->height - borderPadding);

    ball = std::make_unique<Ball>(0, 0);
    ball->setDimensions(0, paddle->height / 2);
    ball->setPosition(w / 2 - ball->width / 2, paddle->y_pos - ball->height);
}

void GameplayGameState::update(unsigned int i) {
    map->update(i);
    paddle->update(i);
    ball->update(i);
}

void GameplayGameState::handleKey(FRKey key, bool pressed) {
    if (key == FRKey::UP) {
        paddle->setVelocity(pressed ? -1 : 0, 0);
    }
    if (key == FRKey::LEFT) {
        paddle->setVelocity(pressed ? -1 : 0, 0);
    }
    else if (key == FRKey::RIGHT) {
        paddle->setVelocity(pressed ? 1 : 0, 0);
    }
//    auto keyStr = (int) key == 1 ? std::string("lewo") : std::string("prawo");
//    std::cout << "key: " << keyStr << " pressed: " << pressed << '\n';
}

void GameplayGameState::handleMouseMove(int x, int y, int xrel, int yrel) {
    ball->setAngle(x, y);
//    std::cout << "mouse: " << x << ", " << y << " - " << xrel << ", " << yrel << '\n';
}

void GameplayGameState::handleMouseKey(FRMouseButton button, bool released) {
    if (button == FRMouseButton::LEFT) {
        ball->release();
    }
    auto keyStr = (int) button == 1 ? std::string("left") : std::string("right");
    std::cout << "button: " << keyStr << ", " << released << '\n';
}
