//
// Created by darkroom2 on 16/10/22.
//

#ifndef ARKANOID_LIKE_GAMESTATE_H
#define ARKANOID_LIKE_GAMESTATE_H


#include "../libs/Framework/inc/Framework.h"
#include "Map.h"

class Game;

class GameState {
public:
    GameState(Game *game, std::string &execPath);
    virtual ~GameState();

    std::string &execPath;
    Game *game;

    virtual void update(unsigned int i) = 0;
    virtual void handleKey(FRKey key, bool pressed) = 0;
    virtual void handleMouseMove(int x, int y, int xrel, int yrel) = 0;
    virtual void handleMouseKey(FRMouseButton button, bool released) = 0;
};

class StartGameState : public GameState {
public:
    StartGameState(Game *game, std::string &execPath);

    void update(unsigned int i) override;

    void handleKey(FRKey key, bool pressed) override;

    void handleMouseMove(int x, int y, int xrel, int yrel) override;

    void handleMouseKey(FRMouseButton button, bool released) override;
};

class GameplayGameState : public GameState {
public:
    GameplayGameState(Game *game, std::string &execPath);

    std::unique_ptr<Map> map;

    void update(unsigned int i) override;

    void handleKey(FRKey key, bool pressed) override;

    void handleMouseMove(int x, int y, int xrel, int yrel) override;

    void handleMouseKey(FRMouseButton button, bool released) override;
};


#endif //ARKANOID_LIKE_GAMESTATE_H
