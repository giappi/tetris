/* 
 * File:   GameState.cpp
 * Author: giappi
 * 
 * Created on 2017-03-28, 20:04
 */

#include "GameState.h"
#include "../../game/GameStateCenter.h"

GameState::GameState()
{
	canvas = Singleton<GameStateCenter>::GetInstance()->GetCanvas();
	graphics = canvas->GetGraphics();
}

GameState::~GameState()
{
}

void GameState::OnKeyUp(int keycode)
{

}

void GameState::OnKeyDown(int keycode)
{

}

void GameState::OnMouseDown(int x, int y)
{

}

void GameState::OnMouseMove(int x, int y)
{

}

void GameState::OnMouseUp(int x, int y)
{

}

void GameState::Draw()
{

}

void GameState::Update()
{

}