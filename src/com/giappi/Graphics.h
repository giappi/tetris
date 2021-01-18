
#pragma once
#include "Bitmap.h"
#include "Canvas.h"
class Canvas;
class Graphics
{
public:
	Graphics(Canvas* canvas);
	~Graphics();
private:
	Canvas* canvas = NULL;
public:
	void DrawImage(Bitmap* image, int x, int y);
    void DrawLine(int x0, int y0,   int x1, int y1, unsigned int color);
    void DrawText(const char* text, int x,  int y,  unsigned int color);
    void DrawRect(int x0, int y0,   int w,  int h,  unsigned int color);
    void FillRect(int x0, int y0,   int w,  int h,  unsigned int color);
};
