//
// Created by darkroom2 on 16/10/22.
//

#include <cmath>
#include <iostream>
#include "../include/GameState.h"
#include "../include/Game.h"


GameState::GameState(Game *game) : game(game) {}


StartGameState::StartGameState(Game *game) : GameState(game) {
    int w, h;
    getScreenSize(w, h);

    welcomeScreen = std::make_unique<Entity>(0, 0);
    std::vector<EntityState> states{EntityState::NORMAL};
    welcomeScreen->loadSprites("start-screen", states, EntityState::NORMAL);
    welcomeScreen->setDimensions((double) w / 3, 0);
    welcomeScreen->setPosition((double) w / 2 - welcomeScreen->width / 2,
                               (double) h / 2 - (double) welcomeScreen->height / 2);
}

void StartGameState::update(unsigned int i) {
    welcomeScreen->update(i);
}

void StartGameState::onMouseMove(int x, int y, int xRelative, int yRelative) {}

void StartGameState::onKeyPressed(FRKey key, bool pressed) {}

void StartGameState::onMouseButtonClick(FRMouseButton button, bool isReleased) {
    if (button == FRMouseButton::LEFT && isReleased) {
        game->setCurrentState("GameplayGameState");
    }
}


GameplayGameState::GameplayGameState(Game *game) : GameState(game) {
    int w, h;
    getScreenSize(w, h);

    brickLines = 11;
    brickColumns = 5;

    map = std::make_unique<Map>(0, 0, w, h, brickLines, brickColumns);

    int borderPadding = h / 20;
    int paddleProportion = 5.f;
    double paddleWidth = std::round(w / paddleProportion);
    paddle = std::make_unique<Paddle>(0, 0);
    paddle->setDimensions(paddleWidth, 0);
    paddle->setPosition((double) w / 2 - paddle->width / 2, h - paddle->height - borderPadding);
    paddle->setSpeed(map->width * paddle->getSpeed());

    ball = std::make_unique<Ball>(0, 0);
    ball->setDimensions(0, paddle->height / 2);
    ball->setPosition(paddle->xPos + paddle->width / 2 - ball->width / 2, paddle->yPos - ball->height);
    ball->stickTo(paddle.get());
    ball->setSpeed(map->width * ball->getSpeed());
}

void GameplayGameState::update(unsigned int i) {
    if (ball->lossCondition()) {
        std::cout << "You lost!" << std::endl;
        changeState("StartGameState");
        return;
    } else if (ball->isColliding(*paddle)) {
        if (map->winCondition()) {
            std::cout << "You won!" << std::endl;
            changeState("StartGameState");
            return;
        }
        ball->bounceY();
    }

    if (paddle->xPos < 0) {
        paddle->xPos = 0;
        if (!ball->isReleased()) {
            ball->xPos = paddle->xPos + (double) paddle->width / 2 - (double) ball->width / 2;
        }
    } else if (paddle->xPos > map->width - paddle->width) {
        paddle->xPos = map->width - paddle->width;
        if (!ball->isReleased()) {
            ball->xPos = paddle->xPos + (double) paddle->width / 2 - (double) ball->width / 2;
        }
    }

    if (ball->xPos < 0) {
        ball->xPos = 0;
        ball->bounceX();
    } else if (ball->xPos > map->width - ball->width) {
        ball->xPos = map->width - ball->width;
        ball->bounceX();
    }

    if (ball->yPos < 0) {
        ball->yPos = 0;
        ball->bounceY();
    } else if (ball->yPos > map->height) {
        ball->takeDamage();
    }

    map->isColliding(*ball);
    map->isColliding(*paddle);

    map->update(i);
    ball->update(i);
    paddle->update(i);
}

void GameplayGameState::changeState(const std::string &name) {
    resetState();
    game->setCurrentState(name);
}

void GameplayGameState::onKeyPressed(FRKey key, bool pressed) {
    if (key == FRKey::LEFT) {
        paddle->moveLeft(pressed);
        if (!ball->isReleased()) {
            ball->moveWithPaddle(pressed);
        }
    } else if (key == FRKey::RIGHT) {
        paddle->moveRight(pressed);
        if (!ball->isReleased()) {
            ball->moveWithPaddle(pressed);
        }
    } else if (key == FRKey::UP && pressed) {
        paddle->extend();
    } else if (key == FRKey::DOWN && pressed) {
        paddle->shrink();
    }
}

void GameplayGameState::onMouseMove(int x, int y, int xRelative, int yRelative) {
    ball->setDirection(x, y);
}

void GameplayGameState::onMouseButtonClick(FRMouseButton button, bool isReleased) {
    if (button == FRMouseButton::LEFT && isReleased) {
        if (!ball->isReleased())
            ball->release();
    }
    if (button == FRMouseButton::RIGHT && isReleased) {
        paddle->resetState();
        ball->resetState();
    }
}

void GameplayGameState::resetState() {
    map = std::make_unique<Map>(0, 0, map->width, map->height, brickLines, brickColumns);
    paddle->resetState();
    ball->resetState();
}
