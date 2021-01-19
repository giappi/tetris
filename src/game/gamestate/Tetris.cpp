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


std::function<void()> drop;
UnsignedInteger timerDrop = 0;

Tetris::Tetris()
{
    
    printf("[D] Start Timer\n");
    auto t0 = std::chrono::system_clock::now().time_since_epoch();
    TIMER.setTimeOut_thread([t0]()
    {
        auto t1 = std::chrono::system_clock::now().time_since_epoch();
        printf("[D] Time out: %f\n", std::chrono::duration<double>(t1 - t0).count());
    }, 5000000000);
    
    //Tetrimino collection[] = {Tetriminos::O, Tetriminos::I, Tetriminos::T, Tetriminos::J, Tetriminos::L, Tetriminos::S, Tetriminos::Z};
    
    currentTetrimino = &Tetriminos::O;
    
    timerDrop = TIMER.setInterval_thread([this]()
    {
        currentTetriminoY += 1;
        if(currentTetriminoY > 20)
        {
            currentTetriminoY = 0;
        }
        GameStateCenterS::GetInstance()->RequestRePaint();
    }, 1000000000);
 
}

Tetris::~Tetris()
{
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
    for(int j = 0; j < tet.h; j++)
    {
        for(int i = 0; i < tet.w; i++)
        {
            if(tet.shape[j*tet.w + i] == 1)
            {
                graphics->FillRect(boardX + x*cellSize + i*cellSize, boardY + y*cellSize + j*cellSize, cellSize, cellSize, 0xFFFF00FF);
                
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
            break;
        }
        // -->
        case 1073741903:
        {
            currentTetriminoX + currentTetrimino->w < boardWidth ? currentTetriminoX++ : 0;
            PostDrawChanged();
            break;
        }
        // _
        case 1073741905:
        {
            break;
        }
    }
}



Tetrimino::Tetrimino(int w, int h, int* shape) : w(w), h(h), shape(shape)
{
}

void Tetris::PostDrawChanged()
{
    GameStateCenterS::GetInstance()->RequestRePaint();
}



Tetrimino Tetriminos::O = Tetrimino(2, 2,  new int[4] {1, 1, 1, 1});
Tetrimino Tetriminos::I = Tetrimino(1, 4,  new int[4] {1, 1, 1, 1});
Tetrimino Tetriminos::T = Tetrimino(3, 2,  new int[6] {1, 1, 1, 0, 1, 0});
Tetrimino Tetriminos::J = Tetrimino(2, 4,  new int[8] {0, 1, 0, 1, 0, 1, 1, 1});
Tetrimino Tetriminos::L = Tetrimino(2, 4,  new int[8] {1, 0, 1, 0, 1, 0, 1, 1});
Tetrimino Tetriminos::S = Tetrimino(3, 2,  new int[6] {0, 1, 1, 1, 1, 0});
Tetrimino Tetriminos::Z = Tetrimino(3, 2,  new int[6] {1, 1, 0, 0, 1, 0});