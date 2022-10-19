//
// Created by darkroom2 on 16/10/22.
//

#ifndef ARKANOID_LIKE_MAP_H
#define ARKANOID_LIKE_MAP_H


#include <vector>
#include <memory>
#include <random>
#include "Entity.h"

class Map : public Entity {
public:
    int redBricks;
    int greenBricks;

    double perkChance;

    explicit Map(int x, int y, int width, int height, int lines, int columns);

    void update(unsigned int i) override;

    bool isColliding(const Entity &entity);

    bool isColliding(Paddle &paddle);

    bool winCondition() const;

private:
    std::random_device r;
    std::default_random_engine e1;
    std::uniform_int_distribution<int> uniform_dist;

    std::vector<std::unique_ptr<Brick>> bricks;
    std::vector<std::unique_ptr<Perk>> perks;

    void removeBricks();

    void trySpawnPerk(double x, double y, int size);
};


#endif //ARKANOID_LIKE_MAP_H
