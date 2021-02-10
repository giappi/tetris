/*
 * File:   Tetris.cpp
 * Author: Giappi
 *
 * Created on 2021-01-17, 20:38
 */

#include "Tetris.h"
#include "tetris/Tetriminos.h"
#include "game/GameStateCenter.h"
#include "utils/Memory.h"
#include "com/giappi/Timer.h"
#include <chrono>


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
            currentTetrimino->reset();
        }
        RePaint();
    }, 1000000000);

    RePaint();

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
            if(tet.dotAt(j, i) == true)
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
            RePaint();
            break;
        }
        // ^
        case 1073741906:
        {
            Rotate();
            RePaint();
            break;
        }
        // -->
        case 1073741903:
        {
            currentTetriminoX + currentTetrimino->width() < boardWidth ? currentTetriminoX++ : 0;
            RePaint();
            break;
        }
        // _
        case 1073741905:
        {
            FixedArray<Tetrimino*, 7> collection = { &Tetriminos::T, &Tetriminos::I, &Tetriminos::J, &Tetriminos::L, &Tetriminos::O, &Tetriminos::S, &Tetriminos::Z };
            currentTetrimino = collection[rand()%7];
            currentTetrimino->reset();
            RePaint();
            break;
        }
        // p : print infomation
        case 112:
        {
            currentTetrimino->print();
        }
    }
}

void Tetris::Rotate()
{
    currentTetrimino->rotate();
    Tetrimino::Point p = currentTetrimino->getRotationPosition();
    currentTetriminoX += p.x;
    currentTetriminoY += p.y;
    RePaint();
}


void Tetris::RePaint()
{
    GAMESTATECENTER.RequestRePaint();
}

