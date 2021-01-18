/*
* File:   MouseEventListener.cpp
* Author: giappi
*
* Created on 2017-03-30, 2017, 01:23
*/
#include "MouseEventListener.h"

std::vector<MouseEventListener*> MouseEventListener::listeners = std::vector<MouseEventListener*>();


MouseEventListener::MouseEventListener()
{


	(MouseEventListener::listeners).push_back(this);
	printf("--> Add MouseEventListener: %d\n",(int) listeners.size());

}


MouseEventListener::~MouseEventListener()
{
}



void MouseEventListener::OnEvent(MouseEvent e)
{
	int x = e.x;
	int y = e.y;
	if (e.type == MouseEvent::MOUSEDOWN)
	{
		for (unsigned int i = 0; i < listeners.size(); i++)
		{
			MouseEventListener* k = listeners[i];
			__printf__(" --> called OnMouseDown(%d, %d) in %s", x, y, typeid(*k).name());
			k->OnMouseDown(x, y);
		}
	}
	if (e.type == MouseEvent::MOUSEUP)
	{
		for (unsigned int i = 0; i < listeners.size(); i++)
		{
			MouseEventListener* k = listeners[i];
			__printf__(" --> called OnMouseUp(%d, %d) in %s", x, y, typeid(*k).name());
			k->OnMouseUp(x, y);
		}
	}

	if (e.type == MouseEvent::MOUSEMOVE)
	{
		for (unsigned int i = 0; i < listeners.size(); i++)
		{
			MouseEventListener* k = listeners[i];
			//__printf__(" --> called OnMouseMove(%d, %d) in %s", x, y, typeid(*k).name());
			k->OnMouseMove(x, y);
		}
	}
}
