
#include "Bitmap.h"
#include "SDL2/SDL_image.h"



Bitmap::Bitmap(int width, int height)
{
	data = NULL;
	Uint32 rmask, gmask, bmask, amask;

	this->sdl_Surface =  SDL_CreateRGBSurface(0, width, height, 32, Color::MaskRed, Color::MaskGreen, Color::MaskBlue, Color::MaskAlpha);
	SDL_SetSurfaceBlendMode(sdl_Surface, SDL_BLENDMODE_BLEND);
	SDL_FillRect(sdl_Surface, NULL, Color(0, 0, 0, 255).toInteger());
}

Bitmap::Bitmap(SDL_Surface* surface)
{
	data = NULL;
	this->SetSDLSurface(surface);
}


Bitmap::~Bitmap()
{
	//Deallocate surface
	SDL_FreeSurface(this->sdl_Surface);
	this->sdl_Surface = NULL;
}

SDL_Surface* Bitmap::GetSDLSurface()
{
	return this->sdl_Surface;
}

void Bitmap::SetSDLSurface(SDL_Surface* surface)
{
	this->sdl_Surface = surface;
}

/* Get color of a pixel */
unsigned int Bitmap::GetColor(int x, int y)
{
	//Convert the pixels to 32 bit
	unsigned int *pixels = (unsigned int *)sdl_Surface->pixels;

	//Get the requested pixel
	return pixels[(y * sdl_Surface->w) + x];
}

/* Set color for a pixel */
void Bitmap::SetColor(int x, int y, unsigned int color)
{
	//Convert the pixels to 32 bit
	Uint32 * pixels = (Uint32 *)sdl_Surface->pixels;
	
	//Set the pixel
	pixels[(y * sdl_Surface->w) + x] = color;
}

unsigned int Bitmap::GetPixel(unsigned int index)
{
	return ((unsigned int*)sdl_Surface->pixels)[index];
}

void Bitmap::SetPixel(unsigned int index, unsigned int color)
{
	((unsigned int*)sdl_Surface->pixels)[index] = color;
}


unsigned int Bitmap::GetWidth()
{
	return sdl_Surface->w;
}

unsigned int Bitmap::GetHeight()
{
	return sdl_Surface->h;
}

unsigned int Bitmap::GetPixelCount()
{
	return GetWidth()*GetHeight();
}

unsigned int*& Bitmap::GetAllPixel()
{
	return (unsigned int*&)sdl_Surface->pixels;
}

unsigned char Bitmap::GetCellAt(unsigned int index)
{
	Color c((*this)[index/4]);
	return c[index % 4];
}

void Bitmap::SetCellAt(unsigned int index, unsigned char cell)
{
	Color c((*this)[index / 4]);
	c[index % 4] = cell;
	(*this)[index / 4] = c.toInteger();
}

/* incomplete function */
unsigned char* Bitmap::GetBitmapData()
{
	int n = GetWidth()*GetHeight();
	if (data == NULL)
	{
		data = new unsigned char[ n * 4 + 1];
	}
	unsigned int* p = GetAllPixel();
	int i = 0;
	while (i < n)
	{
		Color color(p[i]);
		data[4 * i + 0] = color.Red;
		data[4 * i + 1] = color.Green;
		data[4 * i + 2] = color.Blue;
		data[4 * i + 3] = color.Alpha;
		++i;
	}
	return data;
}

void Bitmap::SetBitmapData(unsigned char* d)
{
	int n = GetWidth()*GetHeight();
	unsigned int* p = GetAllPixel();
	int i = 0;
	while (i < n)
	{
		Color color(0);
		color.Red   = data[4 * i + 0];
		color.Green = data[4 * i + 1];
		color.Blue  = data[4 * i + 2];
		color.Alpha = data[4 * i + 3];
		p[i] = color.toInteger();
		++i;
	}
}


SDL_Surface* Bitmap::LoadFromImage(const char* path)
{
	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return NULL;
	}
	SDL_Surface* surface = IMG_Load(path);
	if (surface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	//Do not need return still run =))
	return surface;

}


Bitmap* Bitmap::CreateFromImage(const char* path)
{
	Bitmap* bitmap = NULL;
	SDL_Surface* surface = LoadFromImage(path);
	if (surface != NULL)
	{
		bitmap = new Bitmap(surface);
	}
	//assert(surface != NULL);
	return bitmap;
}