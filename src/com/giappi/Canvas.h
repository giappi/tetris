#ifndef _CANVAS_H
#define _CANVAS_H

#pragma once
#include "Debug.h"
#include <SDL2/SDL.h>
#include "Bitmap.h"
#include "Display.h"
#include "Graphics.h"

class Graphics;

class Canvas:
	  /* extends */ Display
{
public:
	Canvas(int width, int height);
	~Canvas();

public:
	Graphics* GetGraphics();
	void SetBitmap(Bitmap* bitmap, int x, int y);
	void PutPixel(int x, int y, int color);
	int GetPixel(int x, int y);

	unsigned int GetWidth();
	unsigned int GetHeight();

	Bitmap* GetBitmap();
	Bitmap* CopyBitmap();

	void SetSDLSurface(SDL_Surface* sfc);
	SDL_Surface* GetSDLSurface();

public:
	Bitmap* bitmap = NULL;

protected:
	void Paint();

private:
	Graphics* graphics = NULL;
};

#endif