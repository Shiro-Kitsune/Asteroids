#pragma once

#include "Renderer.h"

class LoseState : public GameState
{
public:
	void Init();
	void Cleanup();
	void HandleEvents(GameEngine& game);
	void Update(GameEngine& game, float deltaTime);

	static LoseState* Instance() { return &m_loseState; }
protected:
	LoseState() { }
private:
	void CreateUI();
private:
	static LoseState m_loseState;
};