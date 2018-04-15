#include "stdafx.h"

void CollisionRemoverSystem::Update(const float deltaTime, GameState & gameState)
{
	EntityManager& manager = gameState.GetEntityManager();
	
	for (auto& entity : manager.GetEntities())
	{
		entity->RemoveAllCollisions();
	}
}
