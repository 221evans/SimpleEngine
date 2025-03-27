
#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include "Component.hpp"
#include "../TextureHandler.hpp"
#include "raylib.h"
#include <unordered_map>
#include <string>

class SpriteComponent : public Component {
public:
    SpriteComponent();
    ~SpriteComponent() override;

    void Init(Entity* owner) override;
    void Update(Entity* owner, float deltaTime) override;
    void Draw(Entity* owner) override;

    // Animation controls
    void SetTexture(const std::string& animationName, Texture2D texture, int frameCount, int frameWidth, int frameHeight);
    void SetAnimation(const std::string& animationName);
    void FlipHorizontal(bool flip);

    // Getters
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    bool IsAnimationComplete() const { return animationComplete; }
    bool enemyIsFacingLeft = true;
    bool playerIsFacingLeft = false;

    // Setters
    void SetSize(int w, int h) { width = w; height = h; }
    void SetFrameDuration(float duration) { frameDuration = duration; }
    void SetRotation(float rot) { rotation = rot; }

private:
    struct AnimationInfo {
        Texture2D texture;
        int frameCount;
        int frameWidth;
        int frameHeight;
    };

    std::unordered_map<std::string, AnimationInfo> animations;
    std::string currentAnimation;

    int currentFrame;
    float frameTime;
    float frameDuration;
    bool animationComplete;

    int width;
    int height;
    float rotation;
    bool flipHorizontal;

    Rectangle sourceRec;
    Rectangle destRec;
    Vector2 origin;
};

#endif // SPRITE_COMPONENT_HPP