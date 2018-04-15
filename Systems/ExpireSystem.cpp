#include "stdafx.h"

void ExpireSystem::Update(const float deltaTime, GameState & gameState)
{
	EntityManager& manager = gameState.GetEntityManager();
	
	for (auto& entity : manager.GetEntities())
	{
		ExpireComponent* expireComponent = entity->GetComponent<ExpireComponent>();
		if (expireComponent == nullptr)
		{
			continue;
		}

		expireComponent->IncreaseExistenceTime(deltaTime);
		if (expireComponent->IsExpired())
		{
			entity->MarkAsNeedsToBeRemoved();
		}
	}
}
