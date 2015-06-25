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
    m_curShape = nullptr;

    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            m_board[i][j] = nullptr;
        }
    }
}

GameBoard::~GameBoard()
{
    
}

bool GameBoard::SetCurrentShape(Shape * shape)
{
    m_curShape = shape;
    return true;
}

Shape * GameBoard::GetCurrentShape()
{
    return m_curShape;
}

void GameBoard::AddShapeToBoard()
{
    //for(int i = 0; i < 4; i++)
      //  m_board[m_curShape->m_shape[i]->m_curRow][m_curShape->m_shape[i]->m_curCol] = m_curShape->m_shape[i];
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(m_curShape->m_tetroid[i][j]->m_isActive)
                m_board[ m_curShape->m_startRow + i ][m_curShape->m_startCol + j] = m_curShape->m_tetroid[i][j];
        }
    }
    m_curShape = nullptr;
}

void GameBoard::RemoveAndDropRow(int rowDone)
{
    for(int i = 0; i < 10; i++)
    {
        delete m_board[rowDone][i];
        m_board[rowDone][i] = nullptr;
    }
        
    for(int i = rowDone - 1; i >= 0; i--)
    {
        for(int j = 0; j < 10; j++)
        {
            if(m_board[i][j] != nullptr)
            {
                m_board[i + 1][j] = m_board[i][j];
                m_board[i][j] = nullptr;
            }
        }
            
    }
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

void GameBoard::DrawCurrentShape()
{
    //Start shading with shape color not block color
    SDL_SetRenderDrawColor(m_renderer, m_curShape->m_tetroid[0][0]->GetRedColour(), m_curShape->m_tetroid[0][0]->GetGreenColour(),
                           m_curShape->m_tetroid[0][0]->GetBlueColour(), 255);
    //SDL_SetRenderDrawColor(m_renderer, m_curBlock->m_redColour, m_curBlock->m_greenColour, m_curBlock->m_blueColour, 255);
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(m_curShape->m_tetroid[i][j]->m_isActive)
            {
                int startX = m_gameRect->x + (m_width * (j + m_curShape->m_startCol));
                int startY = m_gameRect->y + (m_height * (i + m_curShape->m_startRow));
                SDL_Rect square = {startX, startY, m_width, m_height };
                SDL_RenderFillRect(m_renderer, &square);
            }
            
        }
        
    }
}
void GameBoard::DrawBlock(Block * block, int row, int col)
{
    SDL_SetRenderDrawColor(m_renderer, block->GetRedColour(), block->GetGreenColour(), block->GetBlueColour(), 255);
    int startX = m_gameRect->x + (m_width * col);
    int startY = m_gameRect->y + (m_height * row);
    SDL_Rect square = {startX, startY, m_width, m_height };
    SDL_RenderFillRect(m_renderer, &square);
}

void GameBoard::DrawBoard()
{
    //Draw current block
    DrawPlayArea();
    if(m_curShape != nullptr)
        DrawCurrentShape();
    
    //Draw board!
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(m_board[i][j] != nullptr)
                DrawBlock(m_board[i][j], i, j);
        }
    }
    DrawGrid();
    
}

