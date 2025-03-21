//
// Created by Jason Evans on 21/03/2025.
//

#ifndef TEXTUREHANDLER_HPP
#define TEXTUREHANDLER_HPP
#include <raylib.h>


class TextureHandler {
public:
    // Player
    Texture2D playerIdle;
    Texture2D playerRun;
    Texture2D playerJump;
    Texture2D playerAttack;
    Texture2D playerDead;
    // Black Boar
    Texture2D blackBoarIdle;
    Texture2D blackBoarRun;
    Texture2D blackBoarAttack;
    Texture2D blackBoarDead;
    // White Boar
    Texture2D whiteBoarIdle;
    Texture2D whiteBoarRun;
    Texture2D whiteBoarAttack;
    Texture2D whiteBoarDead;

    void LoadPlayerTextures();
    void LoadBlackBoarTextures();
    void UnloadTextures() const;


};



#endif //TEXTUREHANDLER_HPP
