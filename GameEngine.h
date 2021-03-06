#pragma once

class GameState;

class GameEngine
{
public:

	void Init();
	void Cleanup();

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	void HandleEvents();
	void Update(float deltaTime);
	void Render();

private:
	// the stack of states
	std::vector<GameState*> m_states;
};