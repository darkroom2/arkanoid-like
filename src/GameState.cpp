//
// Created by darkroom2 on 16/10/22.
//

#include "../include/GameState.h"
#include "../include/Game.h"


GameState::GameState(Game *game, std::string &execPath) : game(game), execPath(execPath) {}

GameState::~GameState() = default;


StartGameState::StartGameState(Game *game, std::string &execPath) : GameState(game, execPath) {}

void StartGameState::update(unsigned int i) {}

void StartGameState::handleMouseMove(int x, int y, int xrel, int yrel) {}

void StartGameState::handleKey(FRKey key, bool pressed) {}

void StartGameState::handleMouseKey(FRMouseButton button, bool released) {
    if (button == FRMouseButton::LEFT && released) {
        if (game->currentState == game->states.at("StartGameState").get())
            game->setCurrentState("GameplayGameState");
    }
}


GameplayGameState::GameplayGameState(Game *game, std::string &execPath) : GameState(game, execPath), map(std::make_unique<Map>()) {}

void GameplayGameState::update(unsigned int i) {
    map->update(i);
}

void GameplayGameState::handleKey(FRKey key, bool pressed) {}

void GameplayGameState::handleMouseMove(int x, int y, int xrel, int yrel) {}

void GameplayGameState::handleMouseKey(FRMouseButton button, bool released) {}
