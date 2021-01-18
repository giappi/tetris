/* 
 * File:   Paint.cpp
 * Author: giappi
 * 
 * Created on April 8, 2017, 9:07 PM
 */

#include "Paint.h"
#include "../../game/GameStateCenter.h"

Paint::Paint()
{
    canvas = GameStateCenterS::GetInstance()->GetCanvas();
    graphics = canvas->GetGraphics();
}

Paint::Paint(const Paint& orig)
{
}

Paint::~Paint()
{
}

void Paint::OnMouseDown(int x, int y)
{
    lastMouseX = x;
    lastMouseY = y;
    mouseHolding = true;
}

void Paint::OnMouseMove(int x, int y)
{
    int dx = x - lastMouseX;
    int dy = y - lastMouseY;
    if(mouseHolding)
    {
        //printf("-- From (%d, %d) -> (%d, %d); \n", lastMouseX, lastMouseY, x, y);
        canvas->bitmap->SetColor(x, y, Color(255, 255, 0, 255).toInteger());
    }
    
    lastMouseX = x;
    lastMouseY = y;
}

void Paint::OnMouseUp(int x, int y)
{
    lastMouseX = x;
    lastMouseY = y;
    mouseHolding = false;
}

