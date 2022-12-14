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

    void update(unsigned int i);

    virtual ~Game();

    GameState *currentState;

    std::map<std::string, std::unique_ptr<GameState>> states;

    void setCurrentState(const std::string &name);

private:
    void addState(const std::string &name, std::unique_ptr<GameState> state);

};


#endif //ARKANOID_LIKE_GAME_H
