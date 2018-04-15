#pragma once

class CollisionDetectionSystem : public System
{
public:
	void Init(GameState& gameState) {}
	void Update(float deltaTime, GameState& gameState);
private:
	void ResolveCollision(Entity& entity1, float radius1, Entity& entity2, float radius2);
};