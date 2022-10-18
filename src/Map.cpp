//
// Created by darkroom2 on 16/10/22.
//

#include <cmath>
#include "../include/Map.h"
#include "../libs/Framework/inc/Framework.h"


Map::Map(Sprite *sprite, int x, int y, int lines, int columns) : Entity(sprite, x, y) {
    getScreenSize(width, height);
    int brick_width = (int) std::round((double) width / (double) columns);
    auto s = createSprite("/home/darkroom2/CLionProjects/arkanoid-like/data/brick-green-normal.png");
    int bw{};
    int bh{};
    getSpriteSize(s, bw, bh);
    double hw_ratio = (double) bh / (double) bw;
    int brick_height = (int) std::round(hw_ratio * brick_width);
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            setSpriteSize(s, brick_width, brick_height);
            bricks.push_back(std::make_unique<Brick>(s, j * brick_width, i * brick_height));
        }
    }
}

void Map::update(unsigned int i) {
    for (const auto &b: bricks) {
        b->update(i);
    }
}
