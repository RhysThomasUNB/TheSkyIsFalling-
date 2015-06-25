//
//  GameBoard.h
//  SDL_Tutorial
//
//  Created by Rhys Thomas on 2015-06-04.
//  Copyright (c) 2015 Rhys Thomas. All rights reserved.
//

#ifndef __SDL_Tutorial__GameBoard__
#define __SDL_Tutorial__GameBoard__

#include <stdio.h>
#include "Block.h"
#include <SDL2/SDL.h>

struct BlockList
{
    Block * block;
    BlockList * next;
};

class GameBoard
{
public:
    GameBoard(SDL_Rect * gameRect, SDL_Renderer* gRenderer, int width = 25, int height = 25);
    ~GameBoard();
    void DrawPlayArea();
    
    void DrawBoard();
    bool SetCurrentBlock(Block * block);
    Block* GetCurrentBlock();
    BlockList* GetRootNode();
    
    void AddBlockToList();
    void UpdateBoard();
    void DrawGrid();
private:
    BlockList* FindLastNode();
    void DrawBlock(Block* blockToDraw);
    void DrawRestBlocks();
    
    int m_board[10][20];
    int m_width;
    int m_height;
    Block * m_curBlock;
    SDL_Rect * m_gameRect;
    SDL_Renderer* m_renderer;
    BlockList * m_root;
    //Linked list of Blocks that aren't current one..
    //After collision Add current block to end of list
    //We can then draw the current block, and then the rest of the blocks
};
#endif /* defined(__SDL_Tutorial__GameBoard__) */
