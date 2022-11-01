//
// Created by darkroom2 on 16/10/22.
//

#include "../include/Game.h"


Game::Game() : currentState(nullptr) {
    addState("StartGameState", std::move(std::make_unique<StartGameState>(this)));
    addState("GameplayGameState", std::move(std::make_unique<GameplayGameState>(this)));
    setCurrentState("StartGameState");
}

void Game::update(unsigned int i) const {
    currentState->update(i);
}

void Game::addState(const std::string &name, std::unique_ptr<GameState> state) {
    states.emplace(name, std::move(state));
}


void Game::setCurrentState(const std::string &name) {
    currentState = states.at(name).get();
}

Game::~Game() = default;
