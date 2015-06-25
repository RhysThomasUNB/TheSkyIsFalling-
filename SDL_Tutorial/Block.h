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



class Block
{
    
public:
    Block();
    ~Block();
    //int m_curRow;
    //int m_curCol;
    
    uint8_t GetRedColour();
    uint8_t GetGreenColour();
    uint8_t GetBlueColour();
    void SetRedColour(uint8_t rVal);
    void SetGreenColour(uint8_t gVal);
    void SetBlueColour(uint8_t bVal);
    bool m_isActive;
    //void DrawBlock();
private:
    //int m_startRow;
    //int m_startCol;
    uint8_t m_redColour;
    uint8_t m_greenColour;
    uint8_t m_blueColour;
    uint8_t m_aplha;
    
};
#endif /* defined(__SDL_Tutorial__Block__) */
