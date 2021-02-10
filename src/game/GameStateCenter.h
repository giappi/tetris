/* 
 * File:   GameStateCenter.h
 * Author: giappi
 *
 * Created on 2017-03-28, 20:05
 */

#ifndef GAMESTATECENTER_H
#define GAMESTATECENTER_H
#include "../com/giappi/KeyEventListener.h"
#include "../com/giappi/MouseEventListener.h"
#include "../game/gamestate/GameState.h"
#include "Singleton.h"
#include <vector>

class GameStateCenter:
    /* implements */ public KeyEventListener, public MouseEventListener
{
	/* Let Singleton access private constructor */
	friend class Singleton<GameStateCenter>;
protected:
	GameStateCenter();
	virtual ~GameStateCenter();

public:
	void Draw();
	void Update();

	unsigned int GetScreenWidth();
	unsigned int GetScreenHeight();

	void PushState(GameState* state);
	void PopState();
    void RequestRePaint();

private:
    std::vector<GameState*> gamestates = {};
protected:
    void OnKeyUp(int keycode);
    void OnKeyDown(int keycode);
	void OnMouseUp(int x, int y);
	void OnMouseMove(int x, int y);
	void OnMouseDown(int x, int y);

public:
	Canvas* GetCanvas();

private:
	SDL_Window*     sdl_Window      = 0;
	Canvas*         canvas          = 0;
    bool            isNeedRePaint   = false;

};

typedef Singleton<GameStateCenter> GameStateCenterS;
#define GAMESTATECENTER (*(Singleton<GameStateCenter>::GetInstance()))

#endif /* GAMESTATECENTER_H */

