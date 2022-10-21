//
// Created by darkroom2 on 16/10/22.
//

#ifndef ARKANOID_LIKE_GAME_H
#define ARKANOID_LIKE_GAME_H

#include <vector>
#include <string>
#include <map>
#include <memory>
#include "GameState.h"
#include "../libs/Framework/inc/Framework.h"


class Game {
public:
    Game();

    virtual ~Game();

    void setCurrentState(const std::string &name);

    void update(unsigned int i) const;

    GameState *currentState;

private:
    std::map<std::string, std::unique_ptr<GameState>> states;

    void addState(const std::string &name, std::unique_ptr<GameState> state);
};


#endif //ARKANOID_LIKE_GAME_H
