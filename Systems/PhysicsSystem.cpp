#include "stdafx.h"

void PhysicsSystem::Update(const float deltaTime, GameState & gameState)
{
	EntityManager& manager = gameState.GetEntityManager();
	
	for (auto& entity : manager.GetEntities())
	{
		PhysicsComponent* physicsComponent = entity->GetComponent<PhysicsComponent>();
		if (physicsComponent != nullptr)
		{
			UpdateEntity(deltaTime, *entity, *physicsComponent, true);
			//manager.PutEntityToGrid(entity.get());
		}
		else
		{
			ParticleEmmiter* particleEmmiter = entity->GetComponent<ParticleEmmiter>();
			if (particleEmmiter != nullptr)
			{
				UpdateParticles(deltaTime, *particleEmmiter);
			}
		}
	}
}

void PhysicsSystem::UpdateEntity(float deltaTime, Entity& entity, PhysicsComponent& physicsComponent, bool wrapAroundScreen)
{
	Vector2D position = entity.GetPosition();
	float angle = entity.GetAngle();
	Vector2D velocity = physicsComponent.GetVelocity();
	Vector2D acceleration = physicsComponent.GetAcceleration();
	float damping = physicsComponent.GetDamping();
	float rotationalSpeed = physicsComponent.GetRotationalSpeed();
	float deltaTimeInSeconds = deltaTime * 0.001f;

	velocity += acceleration * deltaTimeInSeconds;
	velocity *= damping;
	position += velocity * deltaTimeInSeconds;
	angle += rotationalSpeed * deltaTimeInSeconds;

	// Keep object in game world (wrap-around borders)
	if (wrapAroundScreen)
	{
		if (position.x < 0)
		{
			position.x += APP_VIRTUAL_WIDTH;
		}
		if (position.x >= APP_VIRTUAL_WIDTH)
		{
			position.x -= APP_VIRTUAL_WIDTH;
		}
		if (position.y < 0)
		{
			position.y += APP_VIRTUAL_HEIGHT;
		}
		if (position.y >= APP_VIRTUAL_HEIGHT)
		{
			position.y -= APP_VIRTUAL_HEIGHT;
		}
	}

    //Reset acceleration because the force is applied every frame and we do not acceleration to go to infinity
	physicsComponent.SetAcceleration(Vector2D(0.0f, 0.0f));
    physicsComponent.SetVelocity(velocity);
	entity.SetPosition(position);
	entity.SetAngle(angle);
	//entity.SetAngle(velocity.Heading());
}

void PhysicsSystem::UpdateParticles(float deltaTime, const ParticleEmmiter & particleEmmiter)
{
	for (auto& particle : particleEmmiter.GetParticles())
	{
		PhysicsComponent* physicsComponent = particle->GetComponent<PhysicsComponent>();
		UpdateEntity(deltaTime, *particle, *physicsComponent, false);
	}
}
