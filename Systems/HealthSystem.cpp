#include "stdafx.h"

void HealthSystem::Update(const float deltaTime, GameState & gameState)
{
	EntityManager& entityManager = gameState.GetEntityManager();
	EventManager& eventManager = gameState.GetEventManager();
	EntityFactory& entityFactory = gameState.GetEntityFactory();

	for (int i = 0; i < entityManager.GetNumberOfEntities(); ++i)
	{
		Entity* entity = entityManager.GetEntityAt(i);

		HealthComponent* healthComponent = entity->GetComponent<HealthComponent>();
		if (healthComponent == nullptr || !healthComponent->IsDead())
		{
			continue;
		}
			
		entity->MarkAsNeedsToBeRemoved();

		PlayerComponent* player = entity->GetComponent<PlayerComponent>();
		if(player != nullptr)
		{
			eventManager.AddEvent(std::make_unique<GameEvent>(GameEventType::PlayerDied, entity->GetId()));
		}
		else
		{
			EnemyComponent* enemy = entity->GetComponent<EnemyComponent>();
			if(enemy != nullptr)
			{
				eventManager.AddEvent(std::make_unique<GameEvent>(GameEventType::EnemyDestroyed, entity->GetId()));
				//Spawn Loot
				if (enemy->GetLootType() != ItemType::None)
				{
					entityManager.AddEntity(entityFactory.CreateItem(entity->GetPosition(), enemy->GetLootType()));
				}
			}

			EnemyShipComponent* ship = entity->GetComponent<EnemyShipComponent>();
			if (ship != nullptr)
			{
				eventManager.AddEvent(std::make_unique<GameEvent>(GameEventType::ShipDestroyed, entity->GetId()));
			}
		}

        //Spawn explosion
		ExplodableComponent* explodable = entity->GetComponent<ExplodableComponent>();
		if(explodable != nullptr)
		{
			entityManager.AddEntity(entityFactory.CreateExplosion(entity->GetPosition()));
		}
	}
}
