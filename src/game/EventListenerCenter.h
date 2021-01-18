#pragma once
#include <SDL2/SDL.h>
#include "Singleton.h"

class EventListenerCenter
{
	/* Let Singleton access private constructor */
	friend class Singleton<EventListenerCenter>;
private:
	EventListenerCenter();
	virtual ~EventListenerCenter();

private:
	SDL_Event event;

public:
	void Update();
};

typedef Singleton<EventListenerCenter> EventListenerCenterS;

