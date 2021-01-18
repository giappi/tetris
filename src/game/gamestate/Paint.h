/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Paint.h
 * Author: giappi
 *
 * Created on April 8, 2017, 9:07 PM
 */

#ifndef PAINT_H
#define PAINT_H
#include "GameState.h"
class Paint:
            public GameState 
{
public:
    Paint();
    Paint(const Paint& orig);
    virtual ~Paint();
    
    void OnMouseDown(int x, int y);
    void OnMouseUp(int x, int y);
    void OnMouseMove(int x, int y);


private:
    bool  mouseHolding;
    int   lastMouseX = 0;
    int   lastMouseY = 0;
    Canvas* canvas = NULL;
    Graphics* graphics = NULL;
};

#endif /* PAINT_H */

