//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"

GameEngine game;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	game.Init();
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	game.HandleEvents();
	game.Update(deltaTime);
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine or Print) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	game.Render();
}


//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	game.Cleanup();
}