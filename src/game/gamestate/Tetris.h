/*
 * File:   Tetris.h
 * Author: Giappi
 *
 * Created on 2021-01-17, 20:38
 */

#ifndef TETRIS_H
#define TETRIS_H

#include "GameState.h"
#include "com/giappi/Math.h"
#include "game/gamestate/tetris/Tetrimino.h"

class Tetris :
    public GameState
{
public:
    Tetris();
    virtual ~Tetris();

    virtual void Draw() override;
    virtual void Update() override;
    virtual void DrawCell(int i, int j);
    virtual void DrawBoard();
    virtual void DrawTetrimino(int i, int j, const Tetrimino& tet) const;
    virtual void RePaint();
    virtual void Rotate();
    virtual void OnKeyDown(int keycode) override;


private:
    int boardWidth      = 10;
    int boardHeight     = 21;
    int cellSize        = 16;
    int boardX          = 10;
    int boardY          = 10;
    int isDrawChange    = true;

    Tetrimino*  currentTetrimino    = 0;
    int         currentTetriminoX   = 0;
    int         currentTetriminoY   = 0;

};



#endif /* TETRIS_H */

