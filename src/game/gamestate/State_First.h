#pragma once
#include "GameState.h"
class State_First :
	public GameState
{
public:
	State_First();
	virtual ~State_First();

	virtual void Draw() override;
	virtual void Update() override;
	Bitmap* bitmap;
};

