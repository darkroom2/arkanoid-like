//
// Created by darkroom2 on 16/10/22.
//

#include <cmath>
#include <filesystem>
#include "../include/Map.h"
#include "../libs/Framework/inc/Framework.h"


Map::Map(int x, int y, int lines, int columns) : Entity(x, y) {
    getScreenSize(width, height);

    int brick_width = (int) std::round((double) width / (double) columns);

    Brick brick = Brick(0, 0, EntityColor::RED);
    brick.setDimensions(brick_width, 0);
    for (int i = 0; i < columns; ++i) {
        bricks.push_back(brick);
    }

    brick = Brick(0, 0, EntityColor::GREEN);
    brick.setDimensions(brick_width, 0);
    for (int i = 0; i < (lines - 1) * columns; ++i) {
        bricks.push_back(brick);
    }

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            bricks[i * columns + j].setPosition(brick.width * j, brick.height * i);
        }
    }

    int perkWidth = (int) std::round((double) width / (double) columns);
    Perk *perk = new Perk(22, 22);
    perk->setDimensions(perkWidth, 0);
    entities.push_back(perk);
}

void Map::update(unsigned int i) {
    for (auto &b: bricks) {
        b.update(i);
    }
    for (auto &e: entities) {
        e->update(i);
    }
}
