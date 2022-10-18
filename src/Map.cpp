//
// Created by darkroom2 on 16/10/22.
//

#include <cmath>
#include <filesystem>
#include "../include/Map.h"
#include "../libs/Framework/inc/Framework.h"


namespace {
    const int PADDING = 5;
}

Map::Map(int x, int y, int lines, int columns) : Entity(x, y) {
    getScreenSize(width, height);

    int brickWidth = (int) std::round((double) width / (double) columns);

    auto brick = std::make_unique<Brick>(0, 0, EntityColor::RED);
    brick->setDimensions(brickWidth, 0);

    for (int i = 0; i < columns; ++i) {
        auto brickCopy = std::make_unique<Brick>(*brick);
        brickCopy->setPosition(i * brickCopy->width, 0);
        bricks.push_back(std::move(brickCopy));
    }

    brick = std::make_unique<Brick>(0, 0, EntityColor::GREEN);
    brick->setDimensions(brickWidth, 0);

    auto perk = std::make_unique<Perk>(0, 0);
    perk->setDimensions(0, brick->height);

    for (int i = 0; i < (lines - 1) * columns; ++i) {
        auto line = i / columns + 1;
        auto column = i % columns;
        auto brickCopy = std::make_unique<Brick>(*brick);
        brickCopy->setPosition(column * brickCopy->width, line * brickCopy->height);
        auto perkCopy = std::make_unique<Perk>(*perk);
        perkCopy->setPosition((column * brickCopy->width) + brickCopy->width / 2 - perkCopy->width / 2, line * brickCopy->height);
        bricks.push_back(std::move(brickCopy));
        entities.push_back(std::move(perkCopy));
    }

    paddle = std::make_unique<Paddle>(0, 0);
    paddle->setDimensions(0, brick->height * 2);
    paddle->setPosition(width / 2 - paddle->width / 2, height - paddle->height - PADDING);

    ball = std::make_unique<Ball>(33, 333);
    ball->setDimensions(0, brick->height);
}

void Map::update(unsigned int i) {
    for (auto &b: bricks) {
        b->update(i);
    }
    for (auto &e: entities) {
        e->update(i);
    }
    paddle->update(i);
    ball->update(i);
}
