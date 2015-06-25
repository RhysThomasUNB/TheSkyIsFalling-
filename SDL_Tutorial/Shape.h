//
//  Shape.h
//  SDL_Tutorial
//
//  Created by Rhys Thomas on 2015-06-08.
//  Copyright (c) 2015 Rhys Thomas. All rights reserved.
//

#ifndef __SDL_Tutorial__Shape__
#define __SDL_Tutorial__Shape__

#include <stdio.h>
#include "Block.h"

#endif /* defined(__SDL_Tutorial__Shape__) */

enum TetrisShapes
{
    LINE,
    SQUARE,
    L_PIECE,
    BL_PIECE,
    Z_PIECE,
    BZ_PIECE,
    CROSS,
};

static int Colours[7][3] =
{
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255},
    {0, 255, 255},
    {255, 255, 0},
    {255, 0, 255},
    {100, 100, 100},
};

enum ShapeState
{
    DEFAULT,
    ONCEROTATED,
    TWICEROTATED,
    THRICEROTATED,
};

class Shape
{
public:
    Shape();
    ~Shape();
    //TODO: REMOVE
    //Block * m_shape[4];
    Block * m_tetroid[4][4];
    //Uses ShapeType[] and Colour[] to create a shape using blocks!
    //Don't forget to initialize each blocks colour, using a for loop
    void CreateShape(int shapeId);
    int ** RotateShape();
    void SetTetroid(int** newTetroid);
    int m_startRow = 0;
    int m_startCol = 4;
    int m_shapeId;
    int m_shapeState;
private:
    int** CompactArr(const int (&arr)[4][4]);
    
};