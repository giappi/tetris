/*
* File:   MouseEventListener.h
* Author: giappi
*
* Created on 2017-03-30, 2017, 01:23
*/

#ifndef MouseEventListener_H
#define MouseEventListener_H

#include <SDL2/SDL.h>
#include <vector>
#include "Debug.h"

struct MouseEvent
{
	enum Type { MOUSEUP, MOUSEDOWN, MOUSEMOVE };
	int x;
	int y;
	Type type;
	int button = 0;
	MouseEvent(int x, int y, Type type) :x(x), y(y), type(type){}
};


class MouseEventListener
{
public:
	MouseEventListener();
	MouseEventListener(const MouseEventListener& orig);
	virtual ~MouseEventListener();

	static void OnEvent(MouseEvent e);


protected:
	virtual void OnMouseUp(int x, int y) = 0;
	virtual void OnMouseDown(int x, int y) = 0;
	virtual void OnMouseMove(int x, int y) = 0;

private:
	//static bool running;
	//static int Listen(void* ptr);
	static std::vector<MouseEventListener*> listeners;



};

#endif /* MouseEventListener_H */

