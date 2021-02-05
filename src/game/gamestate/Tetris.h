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

#define MAX_TET_WIDTH   4
#define MAX_TET_HEIGHT  4
#define ROTATIONS_NUM   4

struct TetShape : public FixedArray<FixedArray<Boolean, MAX_TET_WIDTH>, MAX_TET_HEIGHT>
{
    UnsignedInteger w = 0;
    UnsignedInteger h = 0;
};

struct Point { Interger x; Interger y; };

struct Tetrimino
{
    enum class Rotation {ANGLE_0 = 0, ANGLE_90 = 1, ANGLE_180 = 2, ANGLE_270 = 3};
private:
    /** rotation state */
    Rotation                angle   = Rotation::ANGLE_0;
    /** 4 shape of rotation state */
    FixedArray<TetShape, ROTATIONS_NUM>     shapes = {};
    FixedArray<Point,    ROTATIONS_NUM>     rotationPosition[4] = {};
public:
    Tetrimino(FixedArray<TetShape, 4>&& shapes);
    Tetrimino(){};
    const UnsignedInteger   width()     const;
    const UnsignedInteger   height()    const;
    const Rotation          rotation()  const;
    const Boolean           dot(const UnsignedInteger x, const UnsignedInteger y) const;
    const void              rotate();
    const void              rotateLeft();
    const void              print() const;
};


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

