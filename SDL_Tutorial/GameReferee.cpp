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

//MAKE THIS A SHAPE FUNCTION CALL
bool GameReferee::IsCollision(int rowOffset, int colOffset, Shape * curShape)
{
    int newRow;
    int newCol;
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(curShape->m_tetroid[i][j]->m_isActive)
            {
                newRow = curShape->m_startRow + i + rowOffset;
                newCol = curShape->m_startCol + j + colOffset;
                if(newRow < 0 || newCol < 0 || newRow >= 20 || newCol >= 10)
                    return true;
                for(int k = 0; k < 20; k++)
                {
                    for(int l = 0; l < 10; l++)
                    {
                        if(m_board->m_board[k][l] != nullptr)
                            if(k == newRow
                               && l == newCol)
                                return true;
                    }
                }

            }
            
        }
    }
    return false;
}

bool GameReferee::IsRotateCollision(int ** newTetroid, int startRow, int startCol)
{
    int newRow;
    int newCol;
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(newTetroid[i][j] == 1)
            {
                newRow = startRow + i;
                newCol = startCol + j;
                if(newRow < 0 || newCol < 0 || newRow >= 20 || newCol >= 10)
                    return true;
                for(int k = 0; k < 20; k++)
                {
                    for(int l = 0; l < 10; l++)
                    {
                        if(m_board->m_board[k][l] != nullptr)
                            if(k == newRow
                               && l == newCol)
                                return true;
                    }
                }
                
            }
            
        }
    }
    return false;
}

int GameReferee::IsLineComplete()
{
    int blockCounter;
    for(int i = 0; i < 20; i++)
    {
        blockCounter = 0;
        for(int j = 0; j < 10; j++)
        {
            if(m_board->m_board[i][j] != nullptr)
                blockCounter++;
            else
                break;
        }
        if(blockCounter == 10)
        {
            return i;
        }
    }
    return -1;
}


void GameReferee::MoveShapeDown(Shape* shape)
{
    shape->m_startRow++;
}

void GameReferee::MoveShapeLeft(Shape* shape)
{
    shape->m_startCol--;
}

void GameReferee::MoveShapeRight(Shape* shape)
{
    shape->m_startCol++;
}
void GameReferee::DropShapeComplete(Shape * curShape)
{
    while(!IsCollision(1, 0, curShape))
        MoveShapeDown(curShape);
}

void GameReferee::PlayGame()
{
    //Event Handler
    SDL_Event e;
    Shape* curShape = new Shape();
    srand(time(0));
    curShape->CreateShape(rand() % 7);
    m_board->SetCurrentShape(curShape);
    
    //If idle time is about 1 second auto drop block
    m_idleTime = SDL_GetTicks();
    
    //Game Loop
    bool quit = false;
    while(!quit)
    {
        uint32_t curTime = SDL_GetTicks();
        if(curTime - m_idleTime > 1200)
        {
            m_idleTime = SDL_GetTicks();
            if(!IsCollision(1, 0, curShape))
                MoveShapeDown(curShape);
            else
            {
                //Block done dropping
                m_board->AddShapeToBoard();
                int rowFinished = IsLineComplete();
                while(rowFinished != -1)
                {
                    //remove line and push down
                    m_board->RemoveAndDropRow(rowFinished);
                    rowFinished = IsLineComplete();
                    Draw();
                    sleep(1);
                }
                curShape = new Shape();
                curShape->CreateShape(rand() % 7);
                m_board->SetCurrentShape(curShape);
                if(IsCollision(1, 0, curShape))
                {
                    printf("Game is Over!");
                    return;
                }
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
                int ** rotatedTetroid;
                switch(e.key.keysym.sym)
                 {
                         
                 //Reference for keypresses
                 case SDLK_UP:
                         rotatedTetroid = curShape->RotateShape();
                         if(!IsRotateCollision(rotatedTetroid, curShape->m_startRow, curShape->m_startCol))
                         {
                             curShape->SetTetroid(rotatedTetroid);
                         }
                         break;
                 case SDLK_DOWN:
                         if(!IsCollision(1, 0, curShape))
                             MoveShapeDown(curShape);
                         break;
                 case SDLK_LEFT:
                         if(!IsCollision(0, -1, curShape))
                             MoveShapeLeft(curShape);
                         break;
                 case SDLK_RIGHT:
                         if(!IsCollision(0, 1, curShape))
                             MoveShapeRight(curShape);
                         break;
                case SDLK_SPACE:
                         DropShapeComplete(curShape);
                         break;
                 default:
                         break;
                 }
            }
            
        }
        Draw();
    }
}

void GameReferee::Draw()
{
    SDL_RenderClear( gRenderer );
    
    //Draw current state of game
    //if(m_board->GetCurrentShape())
    m_board->DrawBoard();
    
    //Fill rest of screen with white and re-draw
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderPresent( gRenderer );
}







