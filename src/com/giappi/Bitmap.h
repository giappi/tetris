#pragma once
#include "Debug.h"
#include <SDL2/SDL.h>


#ifndef Color
struct Color
{
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) :Red(r), Green(g), Blue(b), Alpha(a){};
	Color(unsigned int color)
	{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Red = (color >> 24) & 0xFF; // Red channel
		Green = (color >> 16) & 0xFF; // Green channel
		Blue = (color >> 8) & 0xFF; // Blue channel
		Alpha = color & 0xFF; // Alphas channel
#else
		Alpha = (color >> 24) & 0xFF; // Red channel
		Blue = (color >> 16) & 0xFF; // Green channel
		Green = (color >> 8) & 0xFF; // Blue channel
		Red = color & 0xFF; // Alphas channel
#endif
	};

	unsigned int operator[](unsigned int index) const
	{
		unsigned char channel[4] = { Red, Green, Blue, Alpha };
		return channel[index];
	};

	unsigned char& operator[](unsigned int index)
	{
		unsigned char* channel[4] = { &Red, &Green, &Blue, &Alpha };
		return *(channel[index]);
	};

	unsigned int toInteger()
	{
		unsigned int color = 0;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN

		color = Red;
		color <<= 8;
		color += Green;
		color <<= 8;
		color += Blue;
		color <<= 8;
		color += Alpha;
#else
		color = Alpha;
		color <<= 8;
		color += Blue;
		color <<= 8;
		color += Green;
		color <<= 8;
		color += Red;

#endif
		return color;
	}

	unsigned char Red;
	unsigned char Green;
	unsigned char Blue;
	unsigned char Alpha;

	const static bool is_big_endian = SDL_BYTEORDER == SDL_BIG_ENDIAN;
	const static unsigned int MaskRed = is_big_endian ? 0xff000000 : 0x000000ff;
	const static unsigned int MaskGreen = is_big_endian ? 0x00ff0000 : 0x0000ff00;
	const static unsigned int MaskBlue = is_big_endian ? 0x0000ff00 : 0x00ff0000;
	const static unsigned int MaskAlpha = is_big_endian ? 0x000000ff : 0xff000000;


};

#endif




class Bitmap
{
public:
	Bitmap(int width, int height);
	~Bitmap();

private:
	SDL_Surface* sdl_Surface;
	unsigned char* data = NULL;

	static SDL_Surface* LoadFromImage(const char* path);

	Bitmap(SDL_Surface* surface);

public:

	unsigned int &operator[](unsigned int index) const
	{
		return ((Uint32 *)sdl_Surface->pixels)[index];
	};
	unsigned int &operator[](unsigned int index)
	{
		return ((Uint32 *)sdl_Surface->pixels)[index];
	};

	unsigned int  GetColor(int x, int y);
	unsigned int  GetPixel(unsigned int index);
	void SetPixel(unsigned int index, unsigned int color);
	void SetColor(int x, int y, unsigned int color);
	unsigned int GetWidth();
	unsigned int GetHeight();
	unsigned int GetPixelCount();

	unsigned char* GetBitmapData();
	void SetBitmapData(unsigned char* data);

	unsigned int*& GetAllPixel();

	unsigned char GetCellAt(unsigned int index);
	void SetCellAt(unsigned int index, unsigned char cell);

	static Bitmap* CreateFromImage(const char* path);

public:

	SDL_Surface* GetSDLSurface();
	void SetSDLSurface(SDL_Surface*);

};