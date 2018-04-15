#include "stdafx.h"

void ShieldUserSystem::Update(float deltaTime, GameState & gameState)
{
	EntityManager& manager = gameState.GetEntityManager();
	EventManager& eventManager = gameState.GetEventManager();
	EntityFactory& entityFactory = gameState.GetEntityFactory();

	for (auto& entity : manager.GetEntities())
	{
		ShieldUserComponent* shieldUserComponent = entity->GetComponent<ShieldUserComponent>();
		if (shieldUserComponent == nullptr)
		{
			continue;
		}

		if (shieldUserComponent->IsShieldActivated())
		{
			if (shieldUserComponent->IsShieldExprired())
			{
				shieldUserComponent->DeactivateShield();
			}
		}

		if (!shieldUserComponent->IsShieldReady())
		{
			shieldUserComponent->IncreaseTimeElapsedSinceShieldActivation(deltaTime);

			PlayerComponent* player = entity->GetComponent<PlayerComponent>();
			if (player != nullptr && shieldUserComponent->IsShieldReady())
			{
				eventManager.AddEvent(std::make_unique<GameEvent>(GameEventType::PlayerShieldStatusChanged, entity->GetId()));
			}
	    }
	}

	HandleEvents(eventManager, manager, entityFactory);
}

void ShieldUserSystem::HandleEvents(EventManager& eventManager, EntityManager& entityManager, EntityFactory& entityFactory)
{
	for (auto& event : eventManager.GetEvents())
	{
		if (event->GetEventType() != EventType::GameEvent)
		{
			continue;
		}

		GameEvent* gameEvent = static_cast<GameEvent*>(event.get());
      	if (gameEvent->GetGameEventType() == GameEventType::CreateShield)
		{
			gameEvent->MarkAsRead();
			std::shared_ptr<Entity> entity = entityManager.FindEntityById(gameEvent->GetEntityId());
			if (entity == nullptr)
			{
				continue;
			}

			ShieldUserComponent* shieldUserComponent = entity->GetComponent<ShieldUserComponent>();
			if (!shieldUserComponent->IsShieldCreated())
		    {
		    	entityManager.AddEntity(entityFactory.CreateShield(entity.get()));
		    }
		    shieldUserComponent->ActivateShield();
		}
	}
}