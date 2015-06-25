//
//  Shape.cpp
//  SDL_Tutorial
//
//  Created by Rhys Thomas on 2015-06-08.
//  Copyright (c) 2015 Rhys Thomas. All rights reserved.
//

#include "Shape.h"

Shape::Shape()
{
    /*for(int i = 0; i < 4; i++)
    {
        m_shape[i] = new Block();
    }*/
    for(int i =0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            m_tetroid[i][j] = new Block();
        }
    }
    m_shapeState = 0;
}

Shape::~Shape()
{
}

void Shape::CreateShape(int shapeId)
{
    switch(shapeId)
    {
        case TetrisShapes::LINE:
            m_shapeId = 0;
            for(int i = 0; i < 4; i++)
                m_tetroid[i][0]->m_isActive = true;
            break;
        case TetrisShapes::SQUARE:
            m_shapeId = 1;
            m_tetroid[0][0]->m_isActive = true;
            m_tetroid[0][1]->m_isActive = true;
            m_tetroid[1][0]->m_isActive = true;
            m_tetroid[1][1]->m_isActive = true;
            break;
        case TetrisShapes::L_PIECE:
            m_shapeId = 2;
            m_tetroid[0][0]->m_isActive = true;
            m_tetroid[1][0]->m_isActive = true;
            m_tetroid[2][0]->m_isActive = true;
            m_tetroid[2][1]->m_isActive = true;
            break;
        case TetrisShapes::BL_PIECE:
            m_shapeId = 3;
            m_tetroid[0][1]->m_isActive = true;
            m_tetroid[1][1]->m_isActive = true;
            m_tetroid[2][1]->m_isActive = true;
            m_tetroid[2][0]->m_isActive = true;
            break;
        case TetrisShapes::Z_PIECE:
            m_shapeId = 4;
            m_tetroid[0][0]->m_isActive = true;
            m_tetroid[0][1]->m_isActive = true;
            m_tetroid[1][1]->m_isActive = true;
            m_tetroid[1][2]->m_isActive = true;
            break;
        case TetrisShapes::BZ_PIECE:
            m_shapeId = 5;
            m_tetroid[0][1]->m_isActive = true;
            m_tetroid[0][2]->m_isActive = true;
            m_tetroid[1][1]->m_isActive = true;
            m_tetroid[1][0]->m_isActive = true;
            break;
        case TetrisShapes::CROSS:
            m_shapeId = 6;
            m_tetroid[0][1]->m_isActive = true;
            m_tetroid[1][0]->m_isActive = true;
            m_tetroid[1][1]->m_isActive = true;
            m_tetroid[1][2]->m_isActive = true;
            break;
        default:
            break;
            
    }
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            m_tetroid[i][j]->SetRedColour(Colours[shapeId][0]);
            m_tetroid[i][j]->SetGreenColour(Colours[shapeId][1]);
            m_tetroid[i][j]->SetBlueColour(Colours[shapeId][2]);
        }
    }
}
/*
 [ ][x][ ][ ]   0,1                1,0                [ ][ ][x]
 [ ][x][ ][ ]  1,1          =>    1,1              [x][x][x]
 [ ][x][x][ ]  2,1 & 2,2          1,2 & 2,2    [ ][ ][ ]
 [ ][ ][ ][ ]
 */
int** Shape::CompactArr(const int (&arr)[4][4])
{
    int** retArr = 0;
    bool foundRow = false, foundCol = false;
    int numEmptyRows = 0, rowCounter = 0;
    int numEmptyCols = 0, colCounter = 0;
    retArr = new int*[4];
    
    for (int h = 0; h < 4; h++)
    {
        retArr[h] = new int[4];
        
        if(rowCounter == 4)
            numEmptyRows++;
        rowCounter = 0;
        
        if(colCounter == 4)
            numEmptyCols++;
        colCounter = 0;
        
        for (int w = 0; w < 4; w++)
        {
            
            if(arr[h][w] == 0 && !foundRow)
                rowCounter++;
            else
                foundRow = true;
            
            
            if(arr[w][h] == 0 && !foundCol)
                colCounter++;
            else
                foundCol = true;
            // fill in some initial values
            // (filling in zeros would be more logic, but this is just for the example)
            retArr[h][w] = 0;
        }
    }

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(arr[i][j] == 1)
                retArr[i - numEmptyRows][j - numEmptyCols] = 1;
    
    return retArr;
}

int ** Shape::RotateShape()
{
    int refCounter[4][4];
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(m_tetroid[i][j]->m_isActive)
                refCounter[i][j] = 1;
            else
                refCounter[i][j] = 0;
        }
    }
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(m_tetroid[i][j]->m_isActive)
            {
                refCounter[i][j]--;
                if(i == 0 && j == 0)
                    refCounter[i + 3][j]++;
                else if(i == 0 && j == 1)
                    refCounter[i + 2][j - 1]++;
                else if(i == 0 && j == 2)
                    refCounter[i + 1][j - 2]++;
                else if(i == 0 && j == 3)
                    refCounter[i][j - 3]++;
                else if(i == 1 && j == 0)
                    refCounter[i + 2][j + 1]++;
                else if(i == 1 && j == 1)
                    refCounter[i + 1][j]++;
                else if(i == 1 && j == 2)
                    refCounter[i][j - 1]++;
                else if(i == 1 && j == 3)
                    refCounter[i - 1][j - 2]++;
                else if(i == 2 && j == 0)
                    refCounter[i + 1][j + 2]++;
                else if(i == 2 && j == 1)
                    refCounter[i][j + 1]++;
                else if(i == 2 && j == 2)
                    refCounter[i - 1][j]++;
                else if(i == 2 && j == 3)
                    refCounter[i - 2][j - 1]++;
                else if(i == 3 && j == 0)
                    refCounter[i][j + 3]++;
                else if(i == 3 && j == 1)
                    refCounter[i - 1][j + 2]++;
                else if(i == 3 && j == 2)
                    refCounter[i - 2][j + 1]++;
                else
                    refCounter[i - 3][j]++;
            }
        }
    }
    int ** newRefCounter = CompactArr(refCounter);
    /*if(!IsCollision(0, 0))
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(newRefCounter[i][j] == 1)
                {
                    m_tetroid[i][j]->m_isActive = true;
                }
                else
                    m_tetroid[i][j]->m_isActive = false;
            }
        }
    }*/
    
    //DELETE NEWREFCOUNTER
    return newRefCounter;
}


void Shape::SetTetroid(int ** newTetroid)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(newTetroid[i][j] == 1)
            {
                m_tetroid[i][j]->m_isActive = true;
            }
            else
                m_tetroid[i][j]->m_isActive = false;
        }
    }

}
