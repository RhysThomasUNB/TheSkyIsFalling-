//
//  Block.cpp
//  SDL_Tutorial
//
//  Created by Rhys Thomas on 2015-06-04.
//  Copyright (c) 2015 Rhys Thomas. All rights reserved.
//

#include "Block.h"

Block::Block(int shapeId)
{
    m_curRow = 0;
    m_startCol = 4;
    m_curCol = 4;

    //Copy array for appropriate shape
    for(int i = 0; i < 4; i++)
    {
        for(int j= 0; j < 4; j++)
        {
            m_shape[i][j] = TetrisShapes[shapeId][i][j];
        }
    }
    m_redColour = Colours[shapeId][0];
    m_greenColour = Colours[shapeId][1];
    m_blueColour = Colours[shapeId][2];
    m_aplha = 255;
}

uint8_t Block::GetRedColour()
{
    return m_redColour;
}

uint8_t Block::GetGreenColour()
{
    return m_greenColour;
}

uint8_t Block::GetBlueColour()
{
    return m_blueColour;
}
