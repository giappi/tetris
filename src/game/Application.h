#pragma once
#include "Singleton.h"
//Using SDL and standard IO
#include <SDL2/SDL.h>
#include "../com/giappi/Debug.h"
#include "../com/giappi/Program.h"
#include "../game/GameStateCenter.h"

#include "../game/EventListenerCenter.h"
class Application:
	public Program
{
public:
	Application();
	virtual ~Application();
	void Run();

	void OnStart();
	void OnPause();
	void OnClose();
private:
	bool m_running = false;

	void Update();

};

typedef Singleton<Application> GameS;

