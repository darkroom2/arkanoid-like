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

    virtual void onKeyPressed(FRKey k, bool pressed) = 0;

    virtual void onMouseMove(int x, int y, int xRelative, int yRelative) = 0;

    virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) = 0;
};

class StartGameState : public GameState {
public:
    explicit StartGameState(Game *game);

    void update(unsigned int i) override;

    void onKeyPressed(FRKey key, bool pressed) override;

    void onMouseMove(int x, int y, int xRelative, int yRelative) override;

    void onMouseButtonClick(FRMouseButton button, bool isReleased) override;
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

    void onKeyPressed(FRKey key, bool pressed) override;

    void onMouseMove(int x, int y, int xrelative, int yrelative) override;

    void onMouseButtonClick(FRMouseButton button, bool isReleased) override;

    void resetState();

    void changeState(const std::string &name);
};


#endif //ARKANOID_LIKE_GAMESTATE_H
