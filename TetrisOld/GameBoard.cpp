//
//  GameBoard.cpp
//  SDL_Tutorial
//
//  Created by Rhys Thomas on 2015-06-04.
//  Copyright (c) 2015 Rhys Thomas. All rights reserved.
//

#include "GameBoard.h"

GameBoard::GameBoard(SDL_Rect * gameRect, SDL_Renderer* gRenderer, int width, int height)
{
    m_width = width;
    m_height = height;
    m_gameRect = gameRect;
    m_renderer = gRenderer;
    m_curBlock = nullptr;
    
    m_root = new BlockList();
    m_root->block = nullptr;
    m_root->next = nullptr;
}

GameBoard::~GameBoard()
{
    
}

bool GameBoard::SetCurrentBlock(Block * block)
{
    m_curBlock = block;
    return true;
}

Block* GameBoard::GetCurrentBlock()
{
    return m_curBlock;
}

BlockList* GameBoard::GetRootNode()
{
    return m_root;
}

void GameBoard::DrawPlayArea()
{
    SDL_SetRenderDrawColor(m_renderer, 61, 61, 92, 128);
    SDL_RenderFillRect(m_renderer, m_gameRect);
}

void GameBoard::DrawGrid()
{
    SDL_SetRenderDrawColor( m_renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderDrawRect( m_renderer, m_gameRect );
    for(int i = m_gameRect->y; i < m_gameRect->y + m_gameRect->h; i+= 25)
    {
        for(int j = m_gameRect->x; j < m_gameRect->x + m_gameRect->w; j++)
        {
            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderDrawPoint(m_renderer, j, i);
        }
    }
    for(int i = m_gameRect->y; i < m_gameRect->y + m_gameRect->h; i++)
    {
        for(int j = m_gameRect->x; j < m_gameRect->x + m_gameRect->w; j+= 25)
        {
            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderDrawPoint(m_renderer, j, i);
        }
    }

    
}

void GameBoard::DrawBlock(Block* blockToDraw)
{
    SDL_SetRenderDrawColor(m_renderer, blockToDraw->GetRedColour(), blockToDraw->GetGreenColour(), blockToDraw->GetBlueColour(), 255);
    //SDL_SetRenderDrawColor(m_renderer, m_curBlock->m_redColour, m_curBlock->m_greenColour, m_curBlock->m_blueColour, 255);
    for(int i = 0; i < 4; i++)
    {
        for(int j=0; j < 4; j++)
        {
            if(blockToDraw->m_shape[i][j] == 1)
            {
                int startX = m_gameRect->x + (m_width * (blockToDraw->m_curCol + j));
                int startY = m_gameRect->y + (m_height * (blockToDraw->m_curRow + i));
                SDL_Rect square = {startX, startY, m_width, m_height };
                SDL_RenderFillRect(m_renderer, &square);
            }
            
        }
    }
}

void GameBoard::DrawRestBlocks()
{
    BlockList* currentBlock = m_root;
    while(currentBlock->next != nullptr)
    {
        currentBlock = currentBlock->next;
        DrawBlock(currentBlock->block);
    }
    
}

void GameBoard::DrawBoard()
{
    //Draw current block
    DrawPlayArea();
    DrawBlock(m_curBlock);
    DrawRestBlocks();
    DrawGrid();
    
}

void GameBoard::AddBlockToList()
{
    BlockList* finalNode = FindLastNode();
    finalNode->next = new BlockList();
    finalNode->next->next = nullptr;
    finalNode->next->block = m_curBlock;
    m_curBlock = nullptr;
}

BlockList* GameBoard::FindLastNode()
{
    BlockList* returnNode = m_root;
    while(returnNode->next != nullptr)
        returnNode = returnNode->next;
    return returnNode;
}