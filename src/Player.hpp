//
// Created by Jason Evans on 11/03/2025.
//


#include "raylib.h"
#include "TextureHandler.hpp"
#include "vector"

#ifndef PLAYER_HPP
#define PLAYER_HPP



class Player {
public:
    Player();
    ~Player();
    void Draw();
    void PlayerAttack();
    void Update(float deltaTime);
    void ResetAttackState();
    void StartTurn();
    void TriggerAttack();
    TextureHandler textureHandler{};
    Texture2D currentPlayerTexture{};
    Vector2 position{};
    bool actionCompletedThisTurn{};
    bool attackWasTriggered;
    int playerHealth;
    void Init();
    static bool CheckCollision(Rectangle rec1, Rectangle rec2);
    bool isAttackComplete();

private:
    int posX;
    int posY;
    int width;
    int height;
    int speed;
    int currentFrame;
    float velocity{};
    bool isDead{};
    bool isJumping{};
    bool isAttacking{};
    bool isRunning{};
    bool isFacingLeft{};
    bool isGrounded{};
    int frameWidth{};
    int frameCount{};
    bool attackTriggered{};
    bool attackAnimationComplete;
    int attackAnimationFrame{};
    float rotation;
    float frameTime{};
    float frameDuration{};
    Rectangle destRect{};
    Rectangle sourceRec{};
    Rectangle collisionRec{};
    Vector2 origin{};
    void Jump(float deltaTime);

};



#endif //PLAYER_HPP
