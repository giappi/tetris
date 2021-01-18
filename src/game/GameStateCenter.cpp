/* 
 * File:   GameStateCenter.cpp
 * Author: giappi
 * 
 * Created on 2017-03-28, 20:05
 */

#include "GameStateCenter.h"
#include "../utils/Memory.h"

GameStateCenter::GameStateCenter()
{
	gamestates = std::vector<GameState*>();


	//Create window, TODO: Make it better
	this->sdl_Window = SDL_CreateWindow("Người đan chữ xếp hình", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 440, SDL_WINDOW_SHOWN);
	if (this->sdl_Window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		SDL_Surface* surface = SDL_GetWindowSurface(sdl_Window);
		int a = surface->format->BytesPerPixel;
		canvas = new Canvas(surface->w, surface->h);
		canvas->bitmap->SetSDLSurface(surface);
	}

}

GameStateCenter::~GameStateCenter()
{
	Memory::Delete(canvas);;
	SDL_DestroyWindow(this->sdl_Window);
	this->sdl_Window = NULL;
}


void GameStateCenter::PushState(GameState* state)
{
	gamestates.push_back(state);
}

void GameStateCenter::PopState()
{
	gamestates.pop_back();
}

void GameStateCenter::RequestRePaint()
{
    isNeedRePaint = true;
}


void GameStateCenter::OnKeyUp(int keycode)
{
	if (gamestates.size() > 0)
	{
		gamestates.back()->OnKeyUp(keycode);
	}
}

void GameStateCenter::OnKeyDown(int keycode)
{
	if (gamestates.size() > 0)
	{
		gamestates.back()->OnKeyDown(keycode);
	}

}

void GameStateCenter::OnMouseDown(int x, int y)
{
	if (gamestates.size() > 0)
	{
		gamestates.back()->OnMouseDown(x, y);
	}
}

void GameStateCenter::OnMouseMove(int x, int y)
{
    //printf("-- GameStateCenter From (%d, %d) -> (%d, %d); \n", x, y, x, y);
	if (gamestates.size() > 0)
	{
		gamestates.back()->OnMouseMove(x, y);
	}
}
void GameStateCenter::OnMouseUp(int x, int y)
{
	if (gamestates.size() > 0)
	{
		gamestates.back()->OnMouseUp(x, y);
	}
}

void GameStateCenter::Draw()
{
    if(isNeedRePaint)
    {
        if (gamestates.size() > 0)
        {
            gamestates.back()->Draw();
        }
        //Update the surface
        SDL_UpdateWindowSurface(this->sdl_Window);
        isNeedRePaint = false;
    }
}

void GameStateCenter::Update()
{
	if (gamestates.size() > 0)
	{
		gamestates.back()->Update();
	}

}


Canvas* GameStateCenter::GetCanvas()
{
	return canvas;
}


unsigned int GameStateCenter::GetScreenWidth()
{
	return canvas->GetWidth();
}

unsigned int GameStateCenter::GetScreenHeight()
{
	return canvas->GetHeight();
}