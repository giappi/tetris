
#include "Canvas.h"
#include "../../utils/Memory.h"

Canvas::Canvas(int width, int height)
{
	bitmap = new Bitmap(width, height);
	graphics = new Graphics(this);
}

Canvas::~Canvas()
{
	Memory::Delete(bitmap);
	Memory::Delete(graphics);
}

Graphics* Canvas::GetGraphics()
{
	return this->graphics;
}

unsigned int Canvas::GetWidth()
{
	return bitmap->GetWidth();
}

unsigned int Canvas::GetHeight()
{
	return bitmap->GetHeight();
}

void Canvas::SetBitmap(Bitmap* bitmap, int x, int y)
{
    SDL_Rect rect = SDL_Rect();
    rect.x = x;
    rect.y = y;
	rect.w = bitmap->GetWidth();
    rect.h = bitmap->GetHeight();
    //Apply the image
    SDL_BlitSurface( bitmap->GetSDLSurface(), NULL, this->bitmap->GetSDLSurface(), &rect );
}

Bitmap* Canvas::GetBitmap()
{
	return bitmap;
}

Bitmap* Canvas::CopyBitmap()
{
	Bitmap* bmp = new Bitmap(bitmap->GetWidth(), bitmap->GetHeight());
	return bmp;
}

SDL_Surface* Canvas::GetSDLSurface()
{
	return bitmap->GetSDLSurface();
}

void Canvas::SetSDLSurface(SDL_Surface* sfc)
{
	bitmap->SetSDLSurface(sfc);
}
