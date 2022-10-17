//
// Created by darkroom2 on 16/10/22.
//

#include "../include/Game.h"


Game::Game(std::string &execPath) {
    addState("StartGameState", std::move(std::make_unique<StartGameState>(this, execPath)));
    addState("GameplayGameState", std::move(std::make_unique<GameplayGameState>(this, execPath)));
    setCurrentState("StartGameState");
}

void Game::update(unsigned int i) {
    currentState->update(i);
}

void Game::addState(const std::string &name, std::unique_ptr<GameState> state) {
    states.emplace(name, std::move(state));
}

Game::~Game() {
    for (auto s: sprites) {
        destroySprite(s);
    }
}

void Game::setCurrentState(const std::string &name) {
    currentState = states.at(name).get();
}
