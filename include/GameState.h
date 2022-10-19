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
    explicit GameState(Game *game);

    virtual ~GameState();

    Game *game;

    virtual void update(unsigned int i) = 0;

    virtual void handleKey(FRKey key, bool pressed) = 0;

    virtual void handleMouseMove(int x, int y, int xrel, int yrel) = 0;

    virtual void handleMouseKey(FRMouseButton button, bool released) = 0;
};

class StartGameState : public GameState {
public:
    explicit StartGameState(Game *game);

    void update(unsigned int i) override;

    void handleKey(FRKey key, bool pressed) override;

    void handleMouseMove(int x, int y, int xrel, int yrel) override;

    void handleMouseKey(FRMouseButton button, bool released) override;
};

class GameplayGameState : public GameState {
public:
    explicit GameplayGameState(Game *game);

    int brickLines;
    int brickColumns;
    int maxPerkTime;
    int currentPerkTime;
    unsigned int currentTime{0};
    unsigned int lastTime{0};


    std::unique_ptr<Map> map;
    std::unique_ptr<Paddle> paddle;
    std::unique_ptr<Ball> ball;


    void update(unsigned int i) override;

    void handleKey(FRKey key, bool pressed) override;

    void handleMouseMove(int x, int y, int xrel, int yrel) override;

    void handleMouseKey(FRMouseButton button, bool released) override;

    void resetState();

    void changeState(const std::string &name);
};


#endif //ARKANOID_LIKE_GAMESTATE_H
