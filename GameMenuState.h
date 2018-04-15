#pragma once

#include "Renderer.h"

class GameMenuState : public GameState
{
public:
	void Init();
	void Cleanup();

	void HandleEvents(GameEngine& game);
	void Update(GameEngine& game, float deltaTime);

	static GameMenuState* Instance() { return &m_gameMenuState; }
protected:
	GameMenuState() { }
private:
	void CreateSystems();
	void CreateUI();
private:
	static GameMenuState m_gameMenuState;
	std::vector<std::unique_ptr<System>> m_systems;
};