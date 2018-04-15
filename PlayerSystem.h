#pragma once

class PlayerSystem : public System
{
public:
	void Init(GameState& gameState) {}
	void Update(float deltaTime, GameState& gameState);
private:
	void HandleInput(Entity& entity, PlayerComponent& playerComponent, EntityManager& manager, EventManager& eventManager, float deltaTime);
	void HandleCollisions(Entity& entity, PlayerComponent& playerComponent, EventManager& eventManager);
	void ResetPlayerPosition(Entity& entity, EventManager& eventManager);
	void RotatePlayer(Entity& entity, int direction, float rotationFactor);
	void AcceleratePlayer(Entity& entity);
};