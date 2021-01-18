/* 
 * File:   GameState.h
 * Author: giappi
 *
 * Created on 2017-03-28, 20:04
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "../../com/giappi/Canvas.h"
#include "../../com/giappi/Graphics.h"

class GameState
{
public:
    GameState();
    virtual ~GameState();
public:
	virtual void OnKeyUp(int keycode);
	virtual void OnKeyDown(int keycode);
	virtual void OnMouseDown(int x, int y);
	virtual void OnMouseMove(int x, int y);
	virtual void OnMouseUp(int x, int y);
	virtual void Draw();
	virtual void Update();

protected:
	Canvas* canvas;
	Graphics* graphics;
};

#endif /* GAMESTATE_H */

