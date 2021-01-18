#include "State_First.h"
#include "../../game/GameStateCenter.h"
#include "../../utils/Memory.h"
State_First::State_First()
{
	canvas = Singleton<GameStateCenter>::GetInstance()->GetCanvas();
	graphics = canvas->GetGraphics();
	bitmap = Bitmap::CreateFromImage("res/sheet.png");
}


State_First::~State_First()
{
	Memory::Delete(graphics);
}


void State_First::Draw()
{
	//Apply the image
	graphics->DrawImage(bitmap, 100, 100);
    graphics->FillRect(10, 10, 100, 100, 0xFF00FFFF);
}

void State_First::Update()
{

}