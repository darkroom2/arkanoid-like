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

    brickLines = 3;
    brickColumns = 5;
    maxPerkTime = 20;
    currentPerkTime = 0;

    map = std::make_unique<Map>(0, 0, w, h, brickLines, brickColumns);

    int borderPadding = 5;
    int paddleProportion = 5;
    int paddleWidth = (int) std::round((double) w / (double) paddleProportion);
    paddle = std::make_unique<Paddle>(0, 0);
    paddle->setDefaultWidth(paddleWidth);
    paddle->setDimensions(paddleWidth, 0);
    paddle->setPosition((double) w / 2 - (double) paddle->defaultWidth / 2, h - paddle->height - borderPadding);

    ball = std::make_unique<Ball>(0, 0);
    ball->setDimensions(0, paddle->height / 2);
    ball->setPosition(paddle->xPos + (double) paddle->defaultWidth / 2 - (double) ball->width / 2,
                      paddle->yPos - ball->height);
}

void GameplayGameState::update(unsigned int i) {
    if (ball->lossCondition()) {
        // this could be "loser" screen state
        std::cout << "You lost!\n";
        changeState("GameplayGameState");
        return;
    }
    if (ball->isColliding(*paddle)) {
        if (map->winCondition()) {
            // this could be next level state of something
            std::cout << "You won!\n";
            changeState("GameplayGameState");
            return;
        }
        ball->bounceY();
    }

    map->update(i);
    ball->update(i);
    paddle->update(i);

    if (ball->yPos > map->height) {
        ball->takeDamage();
    }

    if (paddle->xPos < 0) {
        paddle->xPos = 0;
        if (!ball->released) {
            ball->xPos = paddle->xPos + (double) paddle->width / 2 - (double) ball->width / 2;
        }
    }
    if (paddle->xPos > map->width - paddle->width) {
        paddle->xPos = map->width - paddle->width;
        if (!ball->released) {
            ball->xPos = paddle->xPos + (double) paddle->width / 2 - (double) ball->width / 2;
        }
    } else if (ball->xPos < 0) {
        ball->xPos = 0;
        ball->bounceX();
    } else if (ball->xPos > map->width - ball->width) {
        ball->xPos = map->width - ball->width;
        ball->bounceX();
    } else if (ball->yPos < 0) {
        ball->yPos = 0;
        ball->bounceY();
    }

    // kolizje piłki z brickami
    if (map->isColliding(*ball)) {
        ball->bounceY();
    }
    // kolizje paletki z perkami
    if (map->isColliding(*paddle)) {
        std::cout << "width:" << paddle->width << " defaultWidth:" << paddle->defaultWidth << "\n";
        currentPerkTime = maxPerkTime;
    }
    currentTime = getTickCount();
    if (currentTime > lastTime + 1000) {
        currentPerkTime--;
        if (currentPerkTime == 0) {
            paddle->resetPerk();
        }
        lastTime = currentTime;
    }


}

void GameplayGameState::changeState(const std::string &name) {
    resetState();
    game->setCurrentState(name);
}

void GameplayGameState::handleKey(FRKey key, bool pressed) {
    if (key == FRKey::LEFT) {
        paddle->setVelocity(pressed ? -paddle->speed : 0, 0);
        if (!ball->released) {
            ball->setVelocity(pressed ? -paddle->speed : 0, 0);
        }
    } else if (key == FRKey::RIGHT) {
        paddle->setVelocity(pressed ? paddle->speed : 0, 0);
        if (!ball->released) {
            ball->setVelocity(pressed ? paddle->speed : 0, 0);
        }
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
        ball->resetState();
        paddle->resetState();
    }
}

void GameplayGameState::resetState() {
    map = std::make_unique<Map>(0, 0, map->width, map->height, brickLines, brickColumns);
    paddle->resetState();
    ball->resetState();
}
