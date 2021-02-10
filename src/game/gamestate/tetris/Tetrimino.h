/*
 * File:   Tetrimino.h
 * Author: Giappi
 *
 * Created on 2021-02-10, 18:21
 */

#ifndef TETRIMINO_H
#define TETRIMINO_H

#include "_typedef.h"
#include "com/giappi/Math.h"

#define MAX_TET_WIDTH   4
#define MAX_TET_HEIGHT  4
#define ROTATIONS_NUM   4

struct TetShape : public FixedArray<FixedArray<Boolean, MAX_TET_WIDTH>, MAX_TET_HEIGHT>
{
    UnsignedInteger w = 0;
    UnsignedInteger h = 0;
};


struct Tetrimino
{
    enum class Rotation {ANGLE_0 = 0, ANGLE_90 = 1, ANGLE_180 = 2, ANGLE_270 = 3};
    struct Point { Integer x; Integer y; };
private:
    /** rotation state */
    Rotation                angle   = Rotation::ANGLE_0;
    /** 4 shape of rotation state */
    FixedArray<TetShape, ROTATIONS_NUM>     shapes = {};
    FixedArray<Point,    ROTATIONS_NUM>     rotationPositions = {};
    FixedString<64>                         name = "";
public:
    Tetrimino(FixedArray<TetShape, 4>&& shapes, const char* name = "");
    Tetrimino(){};
    const UnsignedInteger   width()     const;
    const UnsignedInteger   height()    const;
    const Rotation          rotation()  const;
    const Boolean           dotAt(const UnsignedInteger x, const UnsignedInteger y) const;
    const void              rotate();
    const void              rotateLeft();
    const Point             getRotationPosition() const;
    const Tetrimino&        fixPositionAfterRotate(Integer x_angle0_x, Integer y_angle0, Integer x_angle90, Integer y_angle90, Integer x_angle180, Integer y_angle180, Integer x_angle270, Integer y_angle270);
    const void              reset();
    const void              print() const;
};

#endif /* TETRIMINO_H */

