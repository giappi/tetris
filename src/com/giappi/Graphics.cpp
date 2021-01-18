
#include "Graphics.h"


Graphics::Graphics(Canvas* canvas)
{
	this->canvas = canvas;
}

Graphics::~Graphics()
{
	
}

void Graphics::DrawImage(Bitmap* bitmap, int x, int y)
{
	this->canvas->SetBitmap(bitmap, x, y);
}

void Graphics::DrawLine(int x0, int y0, int x1, int y1, unsigned int color)
{
    
    
	int _loc_6 = 0;
	int _loc_7 = 0;
	int _loc_8 = 0;
	int _loc_9 = 0;
	int _loc_10 = 0;
	int _loc_11 = 0;
	int _loc_12 = 0;
	int _loc_13 = 0;
    
    Bitmap* bitmap = this->canvas->bitmap;

	if (x0 == x1 && y0 == y1)
	{
		bitmap->SetColor(x0, y0, color);
		return;
	}
	if (x1 >= x0)
	{
		_loc_8 = x1 - x0;
		_loc_10 = 1;
	}
	else
	{
		_loc_8 = x0 - x1;
		_loc_10 = -1;
	}
	if (y1 >= y0)
	{
		_loc_9 = y1 - y0;
		_loc_11 = 1;
	}
	else
	{
		_loc_9 = y0 - y1;
		_loc_11 = -1;
	}
	_loc_6 = x0;
	_loc_7 = y0;
	if (_loc_8 >= _loc_9)
	{
		_loc_9 = _loc_9 << 1;
		_loc_13 = _loc_9 - _loc_8;
		_loc_8 = _loc_8 << 1;
		while (_loc_6 != x1)
		{

			bitmap->SetColor(_loc_6, _loc_7, color);
			if (_loc_13 >= 0)
			{
				_loc_7 = _loc_7 + _loc_11;
				_loc_13 = _loc_13 - _loc_8;
			}
			_loc_13 = _loc_13 + _loc_9;
			_loc_6 = _loc_6 + _loc_10;
		}
		bitmap->SetColor(_loc_6, _loc_7, color);
	}
	else
	{
		_loc_8 = _loc_8 << 1;
		_loc_13 = _loc_8 - _loc_9;
		_loc_9 = _loc_9 << 1;
		while (_loc_7 != y1)
		{

			bitmap->SetColor(_loc_6, _loc_7, color);
			if (_loc_13 >= 0)
			{
				_loc_6 = _loc_6 + _loc_10;
				_loc_13 = _loc_13 - _loc_9;
			}
			_loc_13 = _loc_13 + _loc_8;
			_loc_7 = _loc_7 + _loc_11;
		}
		bitmap->SetColor(_loc_6, _loc_7, color);
	}
	return;
}



void Graphics::DrawText(const char* text,int x, int y, unsigned int color)
{
	
}

void Graphics::DrawRect(int x0, int y0, int w, int h, unsigned int color)
{
    Bitmap* bitmap = this->canvas->bitmap;
    for(int x = x0; x <= x0 + w; x++)
    {
        bitmap->SetColor(x, y0      , color);
        bitmap->SetColor(x, y0 + h  , color);
    }
    for(int y = y0; y <= y0 + h; y++)
    {
        bitmap->SetColor(x0    , y , color);
        bitmap->SetColor(x0 + w, y , color);
    }
}


void Graphics::FillRect(int x0, int y0, int w, int h, unsigned int color)
{
    Bitmap* bitmap = this->canvas->bitmap;
    for(int y = y0; y <= y0 + h; y++)
    {
        for(int x = x0; x <= x0 + w; x++)
        {
            bitmap->SetColor(x, y, color);
        }
    }
}
