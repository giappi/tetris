#include "Application.h"
#include "../game/gamestate/Tetris.h"
#include "../utils/Memory.h"
#include "gamestate/Paint.h"
#include "../com/giappi/Timer.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

Application::Application()
{

}


Application::~Application()
{
}

void __main_loop__()
{
	//Handle events on queue
    TIMER.Update();
	EventListenerCenterS::GetInstance()->Update();
	GameStateCenterS::GetInstance()->Update();
	GameStateCenterS::GetInstance()->Draw();

}


void Application::Run()
{

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return;
	}

    GameState* tetris = new Tetris();
	//GameState* logo = new LogoDisovle();
	GameStateCenterS::GetInstance()->PushState(tetris);

	//Main loop flag
	running = true;

#ifdef __EMSCRIPTEN__
    // void emscripten_set_main_loop(em_callback_func func, int fps, int simulate_infinite_loop);
    emscripten_set_main_loop(__main_loop__, 30, 1);
#else
	//While application is running
	while (running)
	{
		__main_loop__();
		//Wait 100 miliseconds
		SDL_Delay(20);
	}

#endif
    Memory::Delete(tetris);
	EventListenerCenterS::DestroyInstance();
	GameStateCenterS::DestroyInstance();
	GameS::DestroyInstance();
	//Quit SDL subsystems
	SDL_Quit();
}


void Application::OnStart()
{

}
void Application::OnPause()
{

}

void Application::OnClose()
{
	running = false;
}

