/* 
 * File:   Tetris.h
 * Author: Giappi
 *
 * Created on 2021-01-17, 20:38
 */

#ifndef TETRIS_H
#define TETRIS_H

#include "GameState.h"
#include <initializer_list>
#include <functional>

struct Tetrimino
{
    int     w       = 0;
    int     h       = 0;
    int*  shape     = 0;
    Tetrimino(int w, int h, int* shape);
    Tetrimino(){};
};
 
//template <const unsigned int W, const unsigned int H>
//struct TetriminoSpecific : public Tetrimino
//{
//    int     w       = W;
//    int     h       = H;
//    bool    shape[H][W];
//    TetriminoSpecific(bool shape[W][H]);
//};
//
//typedef TetriminoSpecific<2, 2> Tetrimino_O;
//typedef TetriminoSpecific<1, 4> Tetrimino_I;
//typedef TetriminoSpecific<3, 2> Tetrimino_T;
//typedef TetriminoSpecific<2, 4> Tetrimino_J;
//typedef TetriminoSpecific<2, 4> Tetrimino_L;
//typedef TetriminoSpecific<3, 2> Tetrimino_S;
//typedef TetriminoSpecific<3, 2> Tetrimino_Z;

struct Tetriminos
{
    static Tetrimino O;
    static Tetrimino I;
    static Tetrimino T;
    static Tetrimino J;
    static Tetrimino L;
    static Tetrimino S;
    static Tetrimino Z;
};



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
    virtual void PostDrawChanged();
    
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

