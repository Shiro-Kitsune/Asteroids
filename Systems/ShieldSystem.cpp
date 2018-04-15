#include "stdafx.h"

void ShieldSystem::Update(const float deltaTime, GameState& gameState)
{
	EntityManager& manager = gameState.GetEntityManager();

	for (auto &entity : manager.GetEntities())
	{
		ShieldComponent* shieldComponent = entity->GetComponent<ShieldComponent>();
		ParentComponent* parentComponent = entity->GetComponent<ParentComponent>();

		if (shieldComponent == nullptr || parentComponent == nullptr)
		{
			continue;
		}

		ShieldUserComponent* shieldUser = parentComponent->GetParentEntity()->GetComponent<ShieldUserComponent>();
		//If there are no ShieldUser component in parent destroy the shield as it is not needed. Normally it shouldn't happen though
		if (shieldUser == nullptr)
		{
			entity->MarkAsNeedsToBeRemoved();
		}

		RenderingComponent* renderingComponent = entity->GetComponent<RenderingComponent>();
		if (shieldUser->IsShieldActivated())
		{	
			renderingComponent->SetVisibility(true);

		}
		else
		{
			renderingComponent->SetVisibility(false);
		}
	}
}
