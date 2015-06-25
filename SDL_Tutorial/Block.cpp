//
//  Block.cpp
//  SDL_Tutorial
//
//  Created by Rhys Thomas on 2015-06-04.
//  Copyright (c) 2015 Rhys Thomas. All rights reserved.
//

#include "Block.h"

Block::Block()
{
    //m_curRow = 0;
    //m_curCol = 0;
    m_redColour = 0;
    m_greenColour = 0;
    m_blueColour = 0;
    m_isActive = false;
}
Block::~Block()
{
    
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

void Block::SetRedColour(uint8_t rVal)
{
    m_redColour = rVal;
}
void Block::SetGreenColour(uint8_t gVal)
{
    m_greenColour = gVal;
}
void Block::SetBlueColour(uint8_t bVal)
{
    m_blueColour = bVal;
}