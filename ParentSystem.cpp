#include "stdafx.h"

void ParentSystem::Update(float deltaTime, GameState & gameState)
{
	EntityManager& manager = gameState.GetEntityManager();
	
	for (auto& entity : manager.GetEntities())
	{
		ParentComponent* parentComponent = entity->GetComponent<ParentComponent>();
		if (parentComponent == nullptr)
		{
			continue;
		}

		//Check if parent entity needs to be removed and mark child accordingly
		//Need to do it before EntityManager deletes parent otherwise child will have invalid pointer
		const Entity* parent = parentComponent->GetParentEntity();
		if ( (parent == nullptr) || (parent->NeedsToBeRemoved()) )
		{
			entity->MarkAsNeedsToBeRemoved();
		}
	}
}