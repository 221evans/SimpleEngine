// src/SpriteComponent.cpp
#include "SpriteComponent.hpp"
#include "Entity.hpp"
#include <iostream>

SpriteComponent::SpriteComponent() :
    currentFrame(0),
    frameTime(0.0f),
    frameDuration(0.15f),
    animationComplete(false),
    width(64),
    height(64),
    rotation(0.0f),
    flipHorizontal(false) {

    componentType = "Sprite";
    origin = {0.0f, 0.0f};
}

SpriteComponent::~SpriteComponent() {
    // Don't unload textures here as they are managed by TextureHandler
}

void SpriteComponent::Init(Entity* owner) {
    // Nothing specific to initialize for now
}

void SpriteComponent::Update(Entity* owner, float deltaTime) {
    if (currentAnimation.empty() || animations.find(currentAnimation) == animations.end()) {
        return;
    }

    const auto& anim = animations[currentAnimation];

    frameTime += deltaTime;

    // Update animation frame
    if (frameTime >= frameDuration) {
        frameTime = 0;
        currentFrame++;

        if (currentFrame >= anim.frameCount) {
            currentFrame = 0;
            animationComplete = true;
        }
    }

    // Set up the source rectangle for drawing
    sourceRec.x = currentFrame * anim.frameWidth;
    sourceRec.y = 0;
    sourceRec.width = flipHorizontal ? -anim.frameWidth : anim.frameWidth;
    sourceRec.height = height;

    // Set up the destination rectangle
    destRec.x = owner->GetPosition().x;
    destRec.y = owner->GetPosition().y;
    destRec.width = width;
    destRec.height = height;
}

void SpriteComponent::Draw(Entity* owner) {
    if (currentAnimation.empty() || animations.find(currentAnimation) == animations.end()) {
        return;
    }

    const auto& anim = animations[currentAnimation];

    // Draw the sprite
    DrawTexturePro(
        anim.texture,
        sourceRec,
        destRec,
        origin,
        rotation,
        WHITE
    );

    // Debug: Draw collision rectangle
    Rectangle collisionRec = owner->GetCollisionRect();
    DrawRectangleLines(
        collisionRec.x,
        collisionRec.y,
        collisionRec.width,
        collisionRec.height,
        RED
    );
}

void SpriteComponent::SetTexture(const std::string& animationName, Texture2D texture, int frameCount, int frameWidth, int frameHeight) {
    AnimationInfo info;
    info.texture = texture;
    info.frameCount = frameCount;
    info.frameWidth = frameWidth;
    info.frameHeight = texture.height;
    animations[animationName] = info;

    // If this is our first animation, set it as current
    if (currentAnimation.empty()) {
        SetAnimation(animationName);
        width = frameWidth;
        height = frameHeight;
    }
}

void SpriteComponent::SetAnimation(const std::string& animationName) {
    if (animations.find(animationName) == animations.end()) {
        std::cout << "Animation not found: " << animationName << std::endl;
        return;
    }

    if (currentAnimation != animationName) {
        currentAnimation = animationName;
        currentFrame = 0;
        frameTime = 0.0f;
        animationComplete = false;
    }
}

void SpriteComponent::FlipHorizontal(bool flip) {
    flipHorizontal = flip;
}