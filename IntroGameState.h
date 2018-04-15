#pragma once

class IntroGameState : public GameState
{
public:
	void Init();
	void Cleanup();
	void HandleEvents(GameEngine& game);
	void Update(GameEngine& game, float deltaTime);

	static IntroGameState* Instance() { return &m_introGameState; }
protected:
	IntroGameState() { }
private:
	void CreateUI();
private:
	static IntroGameState m_introGameState;
};