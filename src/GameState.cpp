//
// Created by darkroom2 on 16/10/22.
//

#include <filesystem>
#include "../include/GameState.h"
#include "../include/Game.h"


GameState::GameState(Game *game) : game(game) {}

GameState::~GameState() = default;


StartGameState::StartGameState(Game *game) : GameState(game) {
    setupSprites();
}

void StartGameState::setupSprites() {
    const std::filesystem::path sprite_dir{"/home/darkroom2/CLionProjects/arkanoid-like/data"};
    for (auto const &sprite_file: std::filesystem::recursive_directory_iterator{sprite_dir}) {
        Sprite *s = createSprite(sprite_file.path().c_str());
        game->sprites.push_back(s);
    }
}

void StartGameState::update(unsigned int i) {
    int x = 10;
    int y = 10;
    auto s = game->sprites[0];
    drawSprite(s, x, y);
}

GameplayGameState::GameplayGameState(Game *game) : GameState(game) {}

void GameplayGameState::update(unsigned int i) {
    int x = 10;
    int y = 10;
    for (auto &s: game->sprites) {
        drawSprite(s, x, y);
        ++x;
        ++y;
    }
}
