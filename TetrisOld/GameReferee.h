//
//  GameReferee.h
//  SDL_Tutorial
//
//  Created by Rhys Thomas on 2015-06-02.
//  Copyright (c) 2015 Rhys Thomas. All rights reserved.
//

#ifndef __SDL_Tutorial__GameReferee__
#define __SDL_Tutorial__GameReferee__

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "GameBoard.h"

//Screen dimension constants
static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 600;

//Each block is 24x24
class GameReferee
{
public:
    //Constructor/Destructor
    GameReferee(SDL_Window * window, SDL_Renderer * renderer, GameBoard * board);
    ~GameReferee();
    
    //Helper functions to load Textures NOTE: might not need this
    bool LoadMedia();
    SDL_Texture * LoadTexture(std::string path);
    
    //Rules & Game playing functions
    void PlayGame();
    bool CheckCollision(int row, int col, Block * curBlock);
    void DropBlockComplete(Block* curBlock);
    
private:
    //The window we'll be rendering to
    SDL_Window* gWindow;
    //Our Graphics Renderer
    SDL_Renderer* gRenderer;
    
    //Game Timer
    uint32_t m_idleTime;
    
    GameBoard * m_board;
};

#endif /* defined(__SDL_Tutorial__GameReferee__) */
