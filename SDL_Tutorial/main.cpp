//
//  main.cpp
//  SDL_Tutorial
//
//  Created by Rhys Thomas on 2015-05-25.
//  Copyright (c) 2015 Rhys Thomas. All rights reserved.
//

/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
 and may not be redistributed without written permission.*/

//Would like to do up to Lesson#33 to get a full grasp
//Currently on Lesson#7

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "GameReferee.h"

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

SDL_Renderer* gRenderer = nullptr;

SDL_Surface* gScreenSurface = nullptr;

bool init()
{
    //Initialize SDL
    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        printf("SDL Could not be initialized!");
        return false;
    }
    else
    {
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if(gWindow == nullptr)
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            return false;
        }
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if(gRenderer == nullptr)
        {
            printf("Renderer could not be reated! SDL Error: %s\n", SDL_GetError());
            return false;
        }
        //Initialize renderer color
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        
        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !(IMG_Init( imgFlags) & imgFlags))
        {
            printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
            return false;
        }
        gScreenSurface = SDL_GetWindowSurface( gWindow );
    }
    return true;
}


void close()
{
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    if( !init() )
    {
        printf("failed to initialize!\n");
        return 1;
    }
    SDL_Rect outlineRect = { SCREEN_WIDTH / 3, SCREEN_HEIGHT / 15, 250, 500  };
    GameBoard * gameBoard = new GameBoard(&outlineRect, gRenderer);
    GameReferee * tetrisGame = new GameReferee(gWindow, gRenderer, gameBoard);
    tetrisGame->PlayGame();
   
    close();
    
    return 0;
}




