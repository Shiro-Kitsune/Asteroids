#include "stdafx.h"

void PlayerSystem::Update(const float deltaTime, GameState& gameState)
{
	EntityManager& entityManager = gameState.GetEntityManager();
	EventManager& eventManager = gameState.GetEventManager();
	
	for (auto& entity : entityManager.GetEntities())
	{
		PlayerComponent* playerComponent = entity->GetComponent<PlayerComponent>();
		if (playerComponent == nullptr)
		{
			continue;
		}

		if (playerComponent->IsActive())
		{
			HandleInput(*entity, *playerComponent, entityManager, eventManager, deltaTime);

			ShieldUserComponent* shieldUserComponent = entity->GetComponent<ShieldUserComponent>();
			if (!shieldUserComponent->IsShieldActivated())
			{
				HandleCollisions(*entity, *playerComponent, gameState.GetEventManager());
			}
		}
		else
		{
			playerComponent->IncreaseTimeElapsedSinceDeactivation(deltaTime);
			if (playerComponent->ReadyToBeActivated())
			{
				entity->GetComponent<RenderingComponent>()->SetVisibility(true);
				ResetPlayerPosition(*entity, eventManager);
				playerComponent->Activate();
			}
		}
		break;
	}
}

void PlayerSystem::HandleInput(Entity& entity, PlayerComponent& playerComponent, EntityManager& entityManager, EventManager& eventManager, const float deltaTime)
{
	PlayerInputComponent* inputComponent = entity.GetComponent<PlayerInputComponent>();

	ShooterComponent* shooterComponent = entity.GetComponent<ShooterComponent>();
	if (shooterComponent != nullptr)
	{
		//Shoot if it is time to shoot
		if (shooterComponent->IsReadyToShoot())
		{
			if (inputComponent->ShootAction())
			{
				eventManager.AddEvent(std::make_unique<GameEvent>(GameEventType::ShootActionRequested, entity.GetId()));
			}
		}

		//Handle power up in effect
		if (playerComponent.IsPowerUpInEffect())
		{
			playerComponent.IncreasePowerUpInEffectTime(deltaTime);
			if (!playerComponent.IsPowerUpInEffect())
			{
				shooterComponent->SetFireType(FireType::Common);
			}
		}
	}

	//Shield
	ShieldUserComponent* shieldUserComponent = entity.GetComponent<ShieldUserComponent>();
	if (shieldUserComponent->IsShieldReady())
	{
	    if (inputComponent->ActivateShieldAction())
	    {
			eventManager.AddEvent(std::make_unique<GameEvent>(GameEventType::PlayerShieldStatusChanged, entity.GetId()));
			eventManager.AddEvent(std::make_unique<GameEvent>(GameEventType::CreateShield, entity.GetId()));
	    }
    }

	//Acceleration
	if (inputComponent->AccelerateAction())
	{
		AcceleratePlayer(entity);
	}

	//Rotation
	if (inputComponent->RotateLeftAction())
	{
		RotatePlayer(entity, 1, playerComponent.GetRotationFactor());
	}
	else if (inputComponent->RotateRightAction())
	{
		RotatePlayer(entity, -1, playerComponent.GetRotationFactor());
	}

}

void PlayerSystem::HandleCollisions(Entity& entity, PlayerComponent& playerComponent, EventManager& eventManager)
{
	RenderingComponent* renderingComponent = entity.GetComponent<RenderingComponent>();
	HealthComponent* healthComponent = entity.GetComponent<HealthComponent>();

	for (auto collision : entity.GetCollisions())
	{
		Entity* collidedWith = collision.GetEntity();
		EnemyComponent* enemyComponent = collidedWith->GetComponent<EnemyComponent>();
		BulletComponent* bulletComponent = collidedWith->GetComponent<BulletComponent>();

		if (enemyComponent != nullptr)
		{
			healthComponent->DecreaseLives();
			playerComponent.Deactivate();
			renderingComponent->SetVisibility(false);
			eventManager.AddEvent(std::make_unique<GameEvent>(GameEventType::PlayerHealthChanged, entity.GetId()));
			break;
		}
		else if(bulletComponent != nullptr && !bulletComponent->IsPlayerOwner())
		{
			playerComponent.Deactivate();
			renderingComponent->SetVisibility(false);
			break;
		}
	}
}

void PlayerSystem::ResetPlayerPosition(Entity& entity, EventManager& eventManager)
{
    entity.SetPosition(Vector2D(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2));
    entity.SetAngle(0.0f);

    PhysicsComponent* physicsComponent = entity.GetComponent<PhysicsComponent>();
    physicsComponent->SetVelocity(Vector2D(0.0f, 0.0f));

	eventManager.AddEvent(std::make_unique<GameEvent>(GameEventType::CreateShield, entity.GetId()));
	eventManager.AddEvent(std::make_unique<GameEvent>(GameEventType::PlayerShieldStatusChanged, entity.GetId()));
}

void PlayerSystem::RotatePlayer(Entity& entity, const int direction, const float rotationFactor)
{
	float angle = entity.GetAngle();
	angle += direction * rotationFactor;
	entity.SetAngle(angle);
}

void PlayerSystem::AcceleratePlayer(Entity& entity)
{
	PhysicsComponent* physicsComponent = entity.GetComponent<PhysicsComponent>();
	float angle = entity.GetAngle() + 90;
	Vector2D force (cos(Utilities::ToRadians(angle)), sin(Utilities::ToRadians(angle)));
	force *= 90;
	physicsComponent->ApplyForce(force);
}
