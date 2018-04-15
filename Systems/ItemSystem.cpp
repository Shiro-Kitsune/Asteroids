#include "stdafx.h"

void ItemSystem::Update(const float deltaTime, GameState & gameState)
{
	EntityManager& manager = gameState.GetEntityManager();

	for (auto& entity : manager.GetEntities())
	{
		ItemComponent* itemComponent = entity->GetComponent<ItemComponent>();
		if (itemComponent == nullptr)
		{
			continue;
		}

		for (auto collision : entity->GetCollisions())
		{
			Entity* player = collision.GetEntity();
			PlayerComponent* playerComponent = player->GetComponent<PlayerComponent>();
			if (playerComponent == nullptr)
			{
				continue;
			}

			entity->MarkAsNeedsToBeRemoved();

			switch (itemComponent->GetType())
			{
				case ItemType::Mineral :
				{
					playerComponent->AddToScore(5);
					gameState.GetEventManager().AddEvent(std::make_unique<GameEvent>(GameEventType::MineralCollected, player->GetId()));
					break;
				}
				case ItemType::Heart:
				{
					HealthComponent* healthComponent = player->GetComponent<HealthComponent>();
					healthComponent->Heal();
					gameState.GetEventManager().AddEvent(std::make_unique<GameEvent>(GameEventType::PlayerHealthChanged, player->GetId()));
				    break;
				}
				case ItemType::PowerUp:
				{
					ShooterComponent* shooterComponent = player->GetComponent<ShooterComponent>();
					playerComponent->PowerUp();
					shooterComponent->SetFireType(FireType::Boss);
					break;
				}
			}
			break;
		}
	}
}
