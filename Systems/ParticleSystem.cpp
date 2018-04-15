#include "stdafx.h"

void ParticleSystem::Update(float deltaTime, GameState & gameState)
{
	EntityManager& manager = gameState.GetEntityManager();

	for (auto& entity : manager.GetEntities())
	{
		ParticleEmmiter* emmiter = entity->GetComponent<ParticleEmmiter>();
		if (emmiter == nullptr)
		{
			continue;
		}

		emmiter->RemoveExpiredParticles();
	}
}
