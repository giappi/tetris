#include "EventListenerCenter.h"
#include "../com/giappi/KeyEventListener.h"
#include "../com/giappi/MouseEventListener.h"
#include "Application.h"


EventListenerCenter::EventListenerCenter()
{
}


EventListenerCenter::~EventListenerCenter()
{
}

void EventListenerCenter::Update()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			GameS::GetInstance()->OnClose();
		}
		if (event.type == SDL_KEYUP)
		{
			KeyEventListener::OnEvent(KeyEvent(KeyEvent::KEYUP, event.key.keysym.sym));
		}
		if (event.type == SDL_KEYDOWN)
		{
			KeyEventListener::OnEvent(KeyEvent(KeyEvent::KEYDOWN, event.key.keysym.sym));
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			MouseEventListener::OnEvent(MouseEvent(x, y, MouseEvent::Type::MOUSEDOWN));
		}
		if (event.type == SDL_MOUSEBUTTONUP)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			MouseEventListener::OnEvent(MouseEvent(x, y, MouseEvent::Type::MOUSEUP));
		}
		if (event.type == SDL_MOUSEMOTION)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			MouseEventListener::OnEvent(MouseEvent(x, y, MouseEvent::Type::MOUSEMOVE));
		}
	}

}