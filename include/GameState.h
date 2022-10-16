//
// Created by darkroom2 on 16/10/22.
//

#ifndef ARKANOID_LIKE_GAMESTATE_H
#define ARKANOID_LIKE_GAMESTATE_H


class Game;

class GameState {
public:
    explicit GameState(Game *game);

    virtual void update(unsigned int i) = 0;

    virtual ~GameState();

    Game *game;
};

class StartGameState : public GameState {
public:
    void setupSprites();

    explicit StartGameState(Game *game);

    void update(unsigned int i) override;
};

class GameplayGameState : public GameState {
public:
    explicit GameplayGameState(Game *game);

    void update(unsigned int i) override;
};


#endif //ARKANOID_LIKE_GAMESTATE_H
