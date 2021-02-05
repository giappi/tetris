/*
 * File:   Tetris.cpp
 * Author: Giappi
 *
 * Created on 2021-01-17, 20:38
 */

#include "Tetris.h"
#include "../../game/GameStateCenter.h"
#include "../../utils/Memory.h"
#include "com/giappi/Timer.h"
#include <chrono>
#include <initializer_list>
#include "cpp/lang/String.h"
#include <cstdlib>

#define ListLiteral std::initializer_list


std::function<void()> drop;
UnsignedInteger timerDrop = 0;

Tetris::Tetris()
{

    __printf__("[D] Start Timer\n");
    auto t0 = std::chrono::system_clock::now();
    TIMER.setTimeOut([t0]()
    {
        auto t1 = std::chrono::system_clock::now();
        __printf__("[D] Time out: %f\n", std::chrono::duration<double>(t1 - t0).count());
    }, 5000000000);

    currentTetrimino = &Tetriminos::T;

    timerDrop = TIMER.setInterval([this]()
    {
        currentTetriminoY += 1;
        if(currentTetriminoY > 20)
        {
            currentTetriminoY = 0;
            FixedArray<Tetrimino*, 7> collection = { &Tetriminos::T, &Tetriminos::I, &Tetriminos::J, &Tetriminos::L, &Tetriminos::O, &Tetriminos::S, &Tetriminos::Z };
            currentTetrimino = collection[rand()%7];
        }
        GameStateCenterS::GetInstance()->RequestRePaint();
    }, 1000000000);

}

Tetris::~Tetris()
{
    __printf__("[D] Tetris::~Tetris");
    TIMER.clearTimeOut(timerDrop);
}

void Tetris::Draw()
{
    // clear
    graphics->FillRect(10, 10, boardWidth*cellSize, boardHeight*cellSize, 0xFF000000);

    if(currentTetrimino)
    {
        DrawTetrimino(currentTetriminoX, currentTetriminoY, *currentTetrimino);
    }

    // draw cells
    for(int j = 0; j < boardHeight; j++)
    {
        for(int i = 0; i < boardWidth; i++)
        {
            graphics->DrawRect(boardX + i*cellSize, boardY + j*cellSize, cellSize, cellSize, 0xFF444444);
        }
    }

    //draw board boders
    graphics->DrawRect(10, 10, boardWidth*cellSize, boardHeight*cellSize, 0xFF00FFFF);

}

void Tetris::DrawTetrimino(int x, int y, const Tetrimino& tet) const
{
    for(int i = 0; i < tet.height(); i++)
    {
        for(int j = 0; j < tet.width(); j++)
        {
            if(tet.dot(j, i) == true)
            {
                graphics->FillRect(boardX + x*cellSize + j*cellSize, boardY + y*cellSize + i*cellSize, cellSize, cellSize, 0xFFFF00FF);
            }
        }
    }
}

void Tetris::DrawBoard()
{

}

void Tetris::DrawCell(int i, int j)
{

}

void Tetris::Update()
{

}

void Tetris::OnKeyDown(int keycode)
{
    switch(keycode)
    {
        // <--
        case 1073741904:
        {
            currentTetriminoX > 0 ? currentTetriminoX-- : 0;
            PostDrawChanged();
            break;
        }
        // ^
        case 1073741906:
        {
            currentTetrimino->rotate();
            PostDrawChanged();
            break;
        }
        // -->
        case 1073741903:
        {
            currentTetriminoX + currentTetrimino->width() < boardWidth ? currentTetriminoX++ : 0;
            PostDrawChanged();
            break;
        }
        // _
        case 1073741905:
        {
            FixedArray<Tetrimino*, 7> collection = { &Tetriminos::T, &Tetriminos::I, &Tetriminos::J, &Tetriminos::L, &Tetriminos::O, &Tetriminos::S, &Tetriminos::Z };
            currentTetrimino = collection[rand()%7];
            PostDrawChanged();
            break;
        }
        // p : print infomation
        case 112:
        {
            currentTetrimino->print();
        }
    }
}

void Tetris::PostDrawChanged()
{
    GameStateCenterS::GetInstance()->RequestRePaint();
}


Tetrimino::Tetrimino(FixedArray<TetShape, 4>&& shapes) : shapes(std::move(shapes))
{

}

const UnsignedInteger Tetrimino::width() const
{
    return shapes[(UnsignedInteger)angle].w;
}

const UnsignedInteger Tetrimino::height() const
{
    return shapes[(UnsignedInteger)angle].h;
}

const Tetrimino::Rotation Tetrimino::rotation() const
{
    return angle;
}

const Boolean Tetrimino::dot(const UnsignedInteger x, const UnsignedInteger y) const
{
    return shapes[(UnsignedInteger)angle][y][x];
}

const void Tetrimino::rotate()
{
    angle = (Rotation) ((((UnsignedInteger) angle) + 1) % 4);
}

const void Tetrimino::rotateLeft()
{
    angle = (Rotation) ((((UnsignedInteger) angle) + 3) % 4);
}

const void Tetrimino::print() const
{
    __printf__("width: %d, height: %d\n", width(), height());
    auto shape = shapes[(UnsignedInteger)angle];
    for(int i = 0; i < shape.h; i++)
    {
        char s[shape.w+1];
        for(int j = 0; j < shape.w; j++)
        {
            s[j] = shape[i][j] ? '#' : '-';
        }
        s[shape.w] = '\0';
        __printf__("%s", s);
    }
    __printf__("\n");
}



inline Tetrimino MakeTetrimino(const ListLiteral<ListLiteral<Boolean>>&& matrix)
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

    FixedArray<TetShape, 4> shape_all = { std::move(shape_0), std::move(shape_1), std::move(shape_2), std::move(shape_3) };

    return Tetrimino(std::move(shape_all));
}



Tetrimino Tetriminos::O = MakeTetrimino({{1, 1}, {1, 1}});
Tetrimino Tetriminos::I = MakeTetrimino({{1, 1, 1, 1}});
Tetrimino Tetriminos::T = MakeTetrimino({{1, 1, 1}, {0, 1, 0}});
Tetrimino Tetriminos::J = MakeTetrimino({{0, 1}, {0, 1}, {0, 1}, {1, 1}});
Tetrimino Tetriminos::L = MakeTetrimino({{1, 0}, {1, 0}, {1, 0}, {1, 1}});
Tetrimino Tetriminos::S = MakeTetrimino({{0, 1, 1}, {1, 1, 0}});
Tetrimino Tetriminos::Z = MakeTetrimino({{1, 1, 0}, {0, 1, 0}});