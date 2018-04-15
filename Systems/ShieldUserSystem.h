#pragma once

class ShieldUserSystem : public System
{
public:
	void Init(GameState& gameState) {}
	void Update(float deltaTime, GameState& gameState);
private:
	void HandleEvents(EventManager& eventManager, EntityManager& entityManager, EntityFactory& entityFactory);
};
