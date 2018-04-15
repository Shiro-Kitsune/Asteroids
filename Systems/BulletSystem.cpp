#include "stdafx.h"

void BulletSystem::Update(const float deltaTime, GameState & gameState)
{
	EntityManager& entityManager = gameState.GetEntityManager();
	
	for (auto& entity : entityManager.GetEntities())
	{
		BulletComponent* bulletComponent = entity->GetComponent<BulletComponent>();
		if (bulletComponent == nullptr)
		{
			continue;
		}
		
		for (auto collision : entity->GetCollisions())
		{
			Entity* collidedWith = collision.GetEntity();
			HealthComponent* healthComponent = collidedWith->GetComponent<HealthComponent>();
			if (healthComponent == nullptr)
			{
				continue;
			}

			//Bullet belonging to player can affect only enemies
			if (bulletComponent->IsPlayerOwner())
			{
				EnemyComponent* enemyComponent = collidedWith->GetComponent<EnemyComponent>();
				if (enemyComponent != nullptr)
				{
					entity->MarkAsNeedsToBeRemoved();
					ShieldUserComponent* shieldUser = collidedWith->GetComponent<ShieldUserComponent>();
					if (shieldUser == nullptr || !shieldUser->IsShieldActivated())
					{
						healthComponent->DecreaseLives();
					}
					break;
				}
			}
			//Bullet belonging to enemy ship can affect only player
			else
			{
				PlayerComponent* playerComponent = collidedWith->GetComponent<PlayerComponent>();
				if (playerComponent != nullptr)
				{
					entity->MarkAsNeedsToBeRemoved();
					ShieldUserComponent* shieldUser = collidedWith->GetComponent<ShieldUserComponent>();
					if (playerComponent->IsActive() && (shieldUser == nullptr || !shieldUser->IsShieldActivated()))
					{
						healthComponent->DecreaseLives();
						gameState.GetEventManager().AddEvent(std::make_unique<GameEvent>(GameEventType::PlayerHealthChanged, collidedWith->GetId()));
					}
					break;
				}
			}
		}
	}
}
