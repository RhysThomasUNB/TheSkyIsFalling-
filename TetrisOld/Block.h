//
//  Block.h
//  SDL_Tutorial
//
//  Created by Rhys Thomas on 2015-06-04.
//  Copyright (c) 2015 Rhys Thomas. All rights reserved.
//

#ifndef __SDL_Tutorial__Block__
#define __SDL_Tutorial__Block__

#include <stdio.h>
#include <stdint.h>

static int TetrisShapes[6][4][4] =
{
    //LINE PIECE
    {
        { 1, 0, 0, 0},
        { 1, 0, 0, 0},
        { 1, 0, 0, 0},
        { 1, 0, 0, 0},
    },
    
    //SQUARE PIECE
    {
        { 1, 1, 0, 0},
        { 1, 1, 0, 0},
        { 0, 0, 0, 0},
        { 0, 0, 0, 0},
    },
    
    //L PIECE
    {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
    },
    
    //BL PIECE
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
    },
    
    //Z PIECE
    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
    //BZ PIECE
    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    }
};

static int Colours[6][3] =
{
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255},
    {0, 255, 255},
    {255, 255, 0},
    {255, 0, 255},
};

class Block
{
    
public:
    Block(int shapeId);
    ~Block();
    int m_curRow;
    int m_curCol;
    int m_shape[4][4];
    
    
    uint8_t GetRedColour();
    uint8_t GetGreenColour();
    uint8_t GetBlueColour();
    //void DrawBlock();
private:
    int m_startRow;
    int m_startCol;
    uint8_t m_redColour;
    uint8_t m_greenColour;
    uint8_t m_blueColour;
    uint8_t m_aplha;
    
};
#endif /* defined(__SDL_Tutorial__Block__) */
