/*
 * File:   Tetriminos.cpp
 * Author: Giappi
 *
 * Created on 2021-02-10, 18:48
 */

#include "Tetriminos.h"
#include "com/giappi/Debug.h"
#include <initializer_list>
#include <memory>

#define ArrayLiteral std::initializer_list

inline Tetrimino MakeTetrimino(const ArrayLiteral<ArrayLiteral<Boolean>>&& matrix, const char* name)
{
    int h = matrix.size(), w = 0;
    TetShape data  =  {};
    int _i = 0;
    for(auto& list : matrix)
    {
        w = list.size();
        data[_i] = {};
        int _j = 0;
        for(auto bit : list)
        {
            data[_i][_j] = bit;
            ++_j;
        }
        ++_i;
    }

    data.h = h;
    data.w = w;

    TetShape shape_0 = {};
    shape_0.h = data.h;
    shape_0.w = data.w;
    for(auto i = 0; i < h; i++)
    {
        shape_0[i] = {};
        for(auto j = 0; j < w; j++)
        {
            shape_0[i][j] = data[i][j];
        }
    }

    TetShape shape_1 = {};
    shape_1.h = data.w;
    shape_1.w = data.h;
    for(auto i = 0; i < shape_1.h; i++)
    {
        shape_1[i] = {};
        for(auto j = 0; j < shape_1.w; j++)
        {
            shape_1[i][j] = data[h-1-j][i];
        }
    }

    TetShape shape_2 = {};
    shape_2.h = data.h;
    shape_2.w = data.w;
    for(auto i = 0; i < shape_2.h; i++)
    {
        shape_2[i] = {};
        for(auto j = 0; j < shape_2.w; j++)
        {
            shape_2[i][j] = data[h-1-i][w-1-j];
        }
    }

    TetShape shape_3 = {};
    shape_3.h = data.w;
    shape_3.w = data.h;
    for(auto i = 0; i < shape_3.h; i++)
    {
        shape_3[i] = {};
        for(auto j = 0; j < shape_3.w; j++)
        {
            shape_3[i][j] = data[j][w-1-i];
        }
    }

    return Tetrimino({ shape_0, shape_1, shape_2, shape_3 }, name);
}



Tetrimino Tetriminos::O = MakeTetrimino({{1, 1}, {1, 1}},           "O");
Tetrimino Tetriminos::I = MakeTetrimino({{1, 1, 1, 1}},             "I");
Tetrimino Tetriminos::T = MakeTetrimino({{1, 1, 1}, {0, 1, 0}},     "T").fixPositionAfterRotate(-1, 1, 0, -1, 0, 0, 1, 0);
Tetrimino Tetriminos::J = MakeTetrimino({{0, 1}, {0, 1}, {1, 1}},   "J").fixPositionAfterRotate(0, -1, 0, 0, 1, 0, -1, 1);
Tetrimino Tetriminos::L = MakeTetrimino({{1, 0}, {1, 0}, {1, 1}},   "L").fixPositionAfterRotate(1, 0, -1, 1, 0, -1, 0, 0);
Tetrimino Tetriminos::S = MakeTetrimino({{0, 1, 1}, {1, 1, 0}},     "S");
Tetrimino Tetriminos::Z = MakeTetrimino({{1, 1, 0}, {0, 1, 1}},     "Z");
