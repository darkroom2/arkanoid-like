//
// Created by darkroom2 on 16/10/22.
//

#include <cmath>
#include <filesystem>
#include "../include/Map.h"
#include "../libs/Framework/inc/Framework.h"


Map::Map(int x, int y, int lines, int columns) : Entity(x, y) {
    auto s = createSprite("brick-green-normal.png");
    int bw{};
    int bh{};
    getSpriteSize(s, bw, bh);
    double hw_ratio = (double) bh / (double) bw;
    getScreenSize(width, height);
    int brick_width = (int) std::round((double) width / (double) columns);
    int brick_height = (int) std::round(hw_ratio * brick_width);
    setSpriteSize(s, brick_width, brick_height);
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            auto brick = std::make_unique<Brick>(j * brick_width, i * brick_height);
            bricks.push_back(std::move(brick));
        }
    }
}

void Map::update(unsigned int i) {
    for (const auto &b: bricks) {
        b->update(i);
    }
}
