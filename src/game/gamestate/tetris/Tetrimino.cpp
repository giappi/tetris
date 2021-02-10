/*
 * File:   Tetrimino.cpp
 * Author: Giappi
 *
 * Created on 2021-02-10, 18:21
 */

#include "Tetrimino.h"
#include "com/giappi/Debug.h"
#include <initializer_list>
#include <memory>

#define ArrayLiteral std::initializer_list

Tetrimino::Tetrimino(FixedArray<TetShape, 4>&& shapes, const char* name): shapes(std::move(shapes)), name(name)
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

const Boolean Tetrimino::dotAt(const UnsignedInteger x, const UnsignedInteger y) const
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

const void Tetrimino::reset()
{
    this->angle = Rotation::ANGLE_0;
}



const Tetrimino& Tetrimino::fixPositionAfterRotate(Integer angle0_x, Integer angle0_y, Integer angle90_x,Integer angle90_y, Integer angle180_x, Integer angle180_y, Integer angle270_x, Integer angle270_y)
{
    rotationPositions[0].x = angle0_x;
    rotationPositions[0].y = angle0_y;
    rotationPositions[1].x = angle90_x;
    rotationPositions[1].y = angle90_y;
    rotationPositions[2].x = angle180_x;
    rotationPositions[2].y = angle180_y;
    rotationPositions[3].x = angle270_x;
    rotationPositions[3].y = angle270_y;
    return *this;
}


const Tetrimino::Point Tetrimino::getRotationPosition() const
{
    return rotationPositions[(UnsignedInteger)angle];
}

const void Tetrimino::print() const
{
    __printf__("name: %s, width: %d, height: %d\n", &name, width(), height());
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

