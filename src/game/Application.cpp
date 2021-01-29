#include "Application.h"
#include "../game/gamestate/Tetris.h"
#include "../utils/Memory.h"
#include "gamestate/Paint.h"
#include "com/giappi/Timer.h"
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
    TIMER.Update();
    //Handle events on queue
	EventListenerCenterS::GetInstance()->Update();
}


void Application::Run()
{

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	GameStateCenterS::GetInstance()->PushState(new Tetris());
    
    // Game Interval
    auto gameInterval = TIMER.setInterval([]()
    {
        GameStateCenterS::GetInstance()->Update();
        GameStateCenterS::GetInstance()->Draw();
    }, 20*MILISECOND);

    __printf__("[I] Begin Main Loop");
	//Main loop flag

#ifdef __EMSCRIPTEN__
    // void emscripten_set_main_loop(em_callback_func func, int fps, int simulate_infinite_loop);
    emscripten_set_main_loop(__main_loop__, 60/*fps*/, 1);
#else
    m_running = true;
	//While application is running
	while (m_running)
	{
		__main_loop__();
		//Wait 100 miliseconds
		SDL_Delay(10);
	}
#endif
    __printf__("[D] Exit main loop");
    TIMER.clearInterval(gameInterval);
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
	m_running = false;
}

