/*
 * File:   KeyEventListener.cpp
 * Author: giappi
 *
 * Created on 2017-03-27, 20:40 PM
 */

#include "KeyEventListener.h"
#include <algorithm>

std::vector<KeyEventListener*> KeyEventListener::listeners = std::vector<KeyEventListener*>();


KeyEventListener::KeyEventListener()
{


    (KeyEventListener::listeners).push_back(this);
    __printf__("--> Add KeyEventListener: %d\n", (int)listeners.size());

    /*
    SDL_Thread *thread;
    int         threadReturnValue;

    //KeyEventListener::running = true;

    printf("\nSimple SDL_CreateThread test:");

    // Simply create a thread
    thread = SDL_CreateThread(Listen, "Listen", (void *)NULL);

    if (NULL == thread)
    {
        printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
    }
    else
    {
        //SDL_WaitThread(thread, &threadReturnValue);
        printf("\nThread returned value: %d", threadReturnValue);
    }
    */
}

KeyEventListener::KeyEventListener(const KeyEventListener& orig)
{
}

KeyEventListener::~KeyEventListener()
{
    //remove listener
    listeners.erase(std::remove(listeners.begin(), listeners.end(), this), listeners.end());
}

/*
int KeyEventListener::Listen(void* ptr)
{
    //Event handler
    SDL_Event e;
    bool running = true;

    while(running)
    {
        //printf("Hello\n");

        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                running = false;
            }
            //User presses a key
            if( e.type == SDL_KEYDOWN )
            {
                //Select surfaces based on key press
                switch( e.key.keysym.sym )
                {
                    case SDLK_UP:
                        printf("Navigation Up\n");
                    break;

                    case SDLK_DOWN:
                        printf("Navigation Down\n");
                    break;

                    case SDLK_LEFT:
                        printf("Navigation Left\n");
                    break;

                    case SDLK_RIGHT:
                        printf("Navigation Right\n");
                    break;

                    default:
                    printf("Pressed %d\n", e.key.keysym.sym);
                    break;
                }
            }
        }

        SDL_Delay(20);
    }
    return 0;
}
*/

void KeyEventListener::OnEvent(KeyEvent e)
{
    int keycode = e.keyCode;
    if (e.type == KeyEvent::KEYDOWN)
    {
        for (unsigned int i = 0; i < listeners.size(); i++)
        {
            KeyEventListener* k = listeners[i];
            __printf__(" --> called OnKeyDown(%d) in %s", keycode, typeid(*k).name());
            k->OnKeyDown(keycode);
        }
    }
    if (e.type == KeyEvent::KEYUP)
    {
        for (unsigned int i = 0; i < listeners.size(); i++)
        {
            KeyEventListener* k = listeners[i];
            __printf__(" --> called OnKeyUp(%d) in %s", keycode, typeid(*k).name());
            k->OnKeyUp(keycode);
        }
    }
}
