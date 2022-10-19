//
// Created by darkroom2 on 16/10/22.
//

#include <cmath>
#include <filesystem>
#include <iostream>
#include "../include/Map.h"


Map::Map(int x, int y, int w, int h, int lines, int columns) : Entity(x, y) {
    width = w;
    height = h;

    int brickWidth = (int) std::round((double) width / (double) columns);

    auto brick = std::make_unique<Brick>(0, 0, EntityColor::RED);
    brick->setDimensions(brickWidth, 0);

    for (int i = 0; i < columns; ++i) {
        auto brickCopy = std::make_unique<Brick>(*brick);
        brickCopy->setPosition(i * brickCopy->width, 0);
        bricks.push_back(std::move(brickCopy));
    }

    auto brick2 = std::make_unique<Brick>(0, 0, EntityColor::GREEN);
    brick2->setDimensions(brickWidth, 0);

    for (int i = 0; i < (lines - 1) * columns; ++i) {
        auto line = i / columns + 1;
        auto column = i % columns;
        auto brickCopy = std::make_unique<Brick>(*brick2);
        brickCopy->setPosition(column * brickCopy->width, line * brickCopy->height);
        bricks.push_back(std::move(brickCopy));
    }
}

void Map::update(unsigned int i) {
    removeBricks();
    for (auto &b: bricks) {
        b->update(i);
    }
    for (auto &e: entities) {
        e->update(i);
    }
}

bool Map::winCondition() const {
    return bricks.empty();
}

bool Map::isColliding(const Entity &entity) const {
    for (const auto &brick: bricks) {
        if (entity.isColliding(*brick)) {
            brick->takeDamage();
            return true;
        }
    }
    return false;
}

void Map::removeBricks() {
    std::erase_if(bricks, [](auto &x) { return !x->alive; });
}
