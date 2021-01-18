/* 
 * File:   KeyEventListener.h
 * Author: giappi
 *
 * Created on 2017-03-27, 20:40 PM
 */

#ifndef KEYEVENTLISTENER_H
#define KEYEVENTLISTENER_H

#include <SDL2/SDL.h>
#include <vector>
#include "Debug.h"

struct KeyEvent
{
	enum Type { KEYUP, KEYDOWN };
	int type;
	int keyCode = 0;
	KeyEvent(int type, int keyCode) :type(type), keyCode(keyCode){}
};


class KeyEventListener
{
public:
    KeyEventListener();
    KeyEventListener(const KeyEventListener& orig);
    virtual ~KeyEventListener();
    
	static void OnEvent(KeyEvent e);
 
    
protected:
    virtual void OnKeyUp(int keycode) = 0;
    virtual void OnKeyDown(int keyCode) = 0;
    
private:
    //static bool running;
    //static int Listen(void* ptr);
    static std::vector<KeyEventListener*> listeners;
    


};

#endif /* KEYEVENTLISTENER_H */

