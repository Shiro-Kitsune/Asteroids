#include "stdafx.h"

void RamShipSystem::Init(GameState & gameState)
{
	m_player = gameState.GetEntityManager().FindEntityByName("player1");
}

void RamShipSystem::Update(float deltaTime, GameState & gameState)
{
	EntityManager& manager = gameState.GetEntityManager();

	for (auto& entity : manager.GetEntities())
	{
		RamShipComponent* ramShip = entity->GetComponent<RamShipComponent>();
		if (ramShip == nullptr)
		{
			continue;
		}

		PhysicsComponent* physicsComponent = entity->GetComponent<PhysicsComponent>();
		if(physicsComponent != nullptr)
		{
			Vector2D steeringForce = Seek(entity->GetPosition(), physicsComponent->GetVelocity(), ramShip->GetMaxSpeed(), ramShip->GetMaxForce());
			physicsComponent->ApplyForce(steeringForce);
			HandleCollisions(*entity);			
		}

		RenderingComponent* renderingComponent = entity->GetComponent<RenderingComponent>();
		if (renderingComponent != nullptr)
		{
			ChangeColor(*entity, *ramShip, *renderingComponent, deltaTime);
		}
	}
}

Vector2D RamShipSystem::Seek(const Vector2D & position, const Vector2D & velocity, const float maxSpeed, const float maxForce)
{
	if(m_player != nullptr)
	{
		Vector2D desiredVelocity = m_player->GetPosition() - position;
		desiredVelocity.Normalize();
		desiredVelocity *= maxSpeed;
		Vector2D steeringForce = desiredVelocity - velocity;
		steeringForce.Limit(maxForce);
		return steeringForce;
    }
    else
    {
    	return Vector2D();
    }
}

void RamShipSystem::HandleCollisions(Entity & entity)
{
	HealthComponent* healthComponent = entity.GetComponent<HealthComponent>();

	for (auto collision : entity.GetCollisions())
	{
		Entity* collidedWith = collision.GetEntity();
		PlayerComponent* player = collidedWith->GetComponent<PlayerComponent>();

		if (player != nullptr)
		{
			healthComponent->SetLives(0);
			break;
		}
	}
}

void RamShipSystem::ChangeColor(Entity & entity, RamShipComponent & ramShip, RenderingComponent & renderingComponent, const float deltaTime)
{
	if (ramShip.ReadyToChangeColor())
	{
		renderingComponent.SetColor(ramShip.GetNextColor());
	}
	else
	{
		ramShip.IncreaseTimeElapsedSinceColorChange(deltaTime);
	}
}
