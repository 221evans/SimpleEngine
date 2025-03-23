//
// Created by Jason Evans on 21/03/2025.
//

#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "TextureHandler.hpp"
#include "raylib.h"


class Enemy {

public:
    Enemy();
    ~Enemy();
    Vector2 position;
    TextureHandler textureHandler;
    bool isAttacking;
    bool attackTriggered;
    bool actionCompletedThisTurn;
    Rectangle collisionRec;
    void Init();
    void EnemyAttack();
    bool IsAttackComplete();
    void StartTurn();
    void Draw();
    void Update(float deltaTime);
    void ResetAttackState();

private:
    Texture2D currentEnemyTexture;
    bool isFacingLeft;
    Rectangle destRec;
    Rectangle sourceRec;
    Vector2 destPos;
    Vector2 origin;
    int enemyHealth;
    int posX;
    int posY;
    int height;
    int width;
    int speed;
    int frameWidth;
    int frameCount;
    bool isRunning;
    float rotation;
    int currentFrame;
    float attackTimer;
    float attackDuration;

};





#endif //ENEMY_HPP
