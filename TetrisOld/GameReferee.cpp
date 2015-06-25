//
//  GameReferee.cpp
//  SDL_Tutorial
//
//  Created by Rhys Thomas on 2015-06-02.
//  Copyright (c) 2015 Rhys Thomas. All rights reserved.
//

#include "GameReferee.h"

GameReferee::GameReferee(SDL_Window * window, SDL_Renderer * renderer, GameBoard * board)
{
    gWindow = window;
    gRenderer = renderer;
    m_board = board;
}

GameReferee::~GameReferee()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;
}


SDL_Texture * GameReferee::LoadTexture(std::string path)
{
    //the final texture
    SDL_Texture * newTexture = nullptr;
    
    //Load image at specified path
    SDL_Surface * loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr)
    {
        printf("Unable to load image %s! SDL_Image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == nullptr)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

bool GameReferee::CheckCollision(int row, int col, Block * curBlock)
{
    //Boundary Checking
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(curBlock->m_shape[i][j] == 1)
            {
                int curRow = row + i;
                int curCol = col + j;
                if(curRow < 0 || curRow >= 20 || curCol < 0 || curCol >= 10 )
                    return false;
            }
        }
    }
    
    //Now check for collision between other pieces!
    BlockList* curNode = m_board->GetRootNode();
    Block* blockNode = nullptr;
    while(curNode->next != nullptr)
    {
        curNode = curNode->next;
        blockNode = curNode->block;
        //For each Cell of Current Block...
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                //if it is a valid cell...
                if(curBlock->m_shape[i][j] == 1)
                {
                    int curRow = row + i;
                    int curCol = col + j;
                    //We must check each cell of block in question
                    for(int k = 0; k < 4; k++)
                    {
                        for(int l = 0; l < 4; l++)
                        {
                            if(blockNode->m_shape[k][l] == 1)
                            {
                                if(curRow == blockNode->m_curRow + k &&  curCol == blockNode->m_curCol + l )
                                    return false;
                            }
                        }
                    }
                    
                }
            }
        }
    }
    return true;
}

void GameReferee::DropBlockComplete(Block * curBlock)
{
    while(CheckCollision(curBlock->m_curRow + 1, curBlock->m_curCol, curBlock))
        curBlock->m_curRow++;
}

void GameReferee::PlayGame()
{
    //Event Handler
    SDL_Event e;
    printf("Dimensions: Width: %d, Height: %d\n", (SCREEN_WIDTH / 2) - (SCREEN_WIDTH / 4), (SCREEN_HEIGHT * 7 / 8) - (SCREEN_HEIGHT / 15));
    Block* currBlock = new Block(5);
    m_board->SetCurrentBlock(currBlock);
    
    m_idleTime = SDL_GetTicks();
    //Game Loop
    bool quit = false;
    while(!quit)
    {
        uint32_t curTime = SDL_GetTicks();
        if(curTime - m_idleTime > 1500)
        {
            srand(curTime);
            m_idleTime = SDL_GetTicks();
            if(CheckCollision(currBlock->m_curRow + 1, currBlock->m_curCol, currBlock))
                currBlock->m_curRow++;
            else
            {
                m_board->AddBlockToList();
                currBlock = new Block(rand() % 6);
                m_board->SetCurrentBlock(currBlock);
            }
            
        }
        //Event Handlers FOR KEY PRESSES
        while(SDL_PollEvent( &e ) != 0)
        {
            //User wants to quit
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                //    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT];
                switch(e.key.keysym.sym)
                 {
                 //Reference for keypresses
                 case SDLK_UP:
                         break;
                 case SDLK_DOWN:
                         if(CheckCollision(currBlock->m_curRow + 1, currBlock->m_curCol, currBlock))
                             currBlock->m_curRow++;
                         break;
                 case SDLK_LEFT:
                         if(CheckCollision(currBlock->m_curRow, currBlock->m_curCol - 1, currBlock))
                             currBlock->m_curCol--;
                         break;
                 case SDLK_RIGHT:
                         if(CheckCollision(currBlock->m_curRow, currBlock->m_curCol + 1, currBlock))
                             currBlock->m_curCol++;
                         break;
                     case SDLK_SPACE:
                         DropBlockComplete(currBlock);
                 default:
                         break;
                 }
            }
            
        }
        SDL_RenderClear( gRenderer );
        
        //Draw current state of game
        if(m_board->GetCurrentBlock())
            m_board->DrawBoard();
        
        //Fill rest of screen with white and re-draw
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderPresent( gRenderer );
        
    }

}









