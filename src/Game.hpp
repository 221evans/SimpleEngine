//
// Created by Jason Evans on 21/03/2025.
//

#ifndef GAME_HPP
#define GAME_HPP
#include "Enemy.hpp"
#include "Player.hpp"


class Game {
public:
    Game();
    ~Game();
    Enemy enemy;
    Player player;
    void Init();
    void Update(float deltaTime);
private:
    bool isPlayerTurn;
    bool isEnemyTurn;
    bool playerTurnInitialized;
    bool enemyTurnInitialized;
    void HandlePlayerTurn();
    void HandleEnemyTurn();
    void SwitchToPlayerTurn();
    void SwitchToEnemyTurn();
    void DrawUI();

};



#endif //GAME_HPP
