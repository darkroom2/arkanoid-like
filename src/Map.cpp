//
// Created by darkroom2 on 16/10/22.
//

#include <cmath>
#include <filesystem>
#include <iostream>
#include "../include/Map.h"


Map::Map(int x, int y, int w, int h, int lines, int columns) : Entity(x, y), e1(r()), uniform_dist(1, 100) {
    redBricks = columns;
    greenBricks = (lines - 1) * columns;
    perkChance = 70;

    width = w;
    height = h;

    int brickWidth = (int) std::round((double) width / (double) columns);

    auto redBrick = std::make_unique<Brick>(0, 0, EntityColor::RED);
    redBrick->setDimensions(brickWidth, 0);

    for (int i = 0; i < redBricks; ++i) {
        auto brickCopy = std::make_unique<Brick>(*redBrick);
        brickCopy->setPosition(i * brickCopy->width, 0);
        bricks.push_back(std::move(brickCopy));
    }


    auto greenBrick = std::make_unique<Brick>(0, 0, EntityColor::GREEN);
    greenBrick->setDimensions(brickWidth, 0);

    for (int i = 0; i < greenBricks; ++i) {
        auto line = i / columns + 1;
        auto column = i % columns;
        auto brickCopy = std::make_unique<Brick>(*greenBrick);
        brickCopy->setPosition(column * brickCopy->width, line * brickCopy->height);
        bricks.push_back(std::move(brickCopy));
    }
}

void Map::update(unsigned int i) {
    removeBricks();
    for (auto &b: bricks) {
        b->update(i);
    }
    for (auto &p: perks) {
        if (p->yPos > height) {
            p->takeDamage();
            continue;
        }
        p->update(i);
    }
}

bool Map::winCondition() const {
    return bricks.empty();
}

bool Map::isColliding(const Entity &entity) {
    for (const auto &brick: bricks) {
        if (entity.isColliding(*brick)) {
            if (brick->color == EntityColor::GREEN) {
                brick->takeDamage();
                --greenBricks;
                trySpawnPerk(brick->xPos + (double) brick->width / 2 - (double) brick->height / 2, brick->yPos,
                             brick->height);
                return true;
            } else if (brick->color == EntityColor::RED && greenBricks == 0) {
                brick->takeDamage();
                trySpawnPerk(brick->xPos + (double) brick->width / 2 - (double) brick->height / 2, brick->yPos,
                             brick->height);
                return true;
            } else {
                return true;
            }
        }
    }
    return false;
}

void Map::removeBricks() {
    std::erase_if(bricks, [](auto &x) { return !x->alive; });
    std::erase_if(perks, [](auto &x) { return !x->alive; });
}

void Map::trySpawnPerk(double x, double y, int size) {
    EntityState perkType;

    int perkTicket = uniform_dist(e1);

    if (perkTicket < perkChance) {
        auto typeTicket = uniform_dist(e1);
        if (typeTicket < 50) {
            perkType = EntityState::POSITIVE;
        } else {
            perkType = EntityState::NEGATIVE;
        }
        auto perk = std::make_unique<Perk>(x, y, perkType);
        perk->setDimensions(size, 0);
        perk->setVelocity(0, 0.5);
        perks.push_back(std::move(perk));
    }
}

bool Map::isColliding(Paddle &entity) {
    for (const auto &perk: perks) {
        if (perk->isColliding(entity)) {
            entity.setPerk(perk->currentState);
            perk->takeDamage();
            return true;
        }
    }
    return false;
}
