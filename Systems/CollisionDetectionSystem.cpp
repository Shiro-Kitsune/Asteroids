#include "stdafx.h"

void CollisionDetectionSystem::Update(const float deltaTime, GameState & gameState)
{
	EntityManager& manager = gameState.GetEntityManager();
	
	for (int i = 0; i < manager.GetNumberOfEntities() - 1; ++i)
	{
		Entity* entity1 = manager.GetEntityAt(i);
		BoundingCircle2D* collider1 = entity1->GetComponent<BoundingCircle2D>();

		if (collider1 != nullptr)
		{
			for (int j = i + 1; j < manager.GetNumberOfEntities(); ++j)
			{
				Entity* entity2 = manager.GetEntityAt(j);
				BoundingCircle2D* collider2 = entity2->GetComponent<BoundingCircle2D>();
				if ((i == j) || (collider2 == nullptr))
				{
					continue;
				}

				bool collisionHappened = Utilities::CircleOverlap(entity1->GetPosition(), collider1->GetRadius(), entity2->GetPosition(), collider2->GetRadius());
				if (collisionHappened)
				{
					entity1->AddCollision(Collision(entity2));
					entity2->AddCollision(Collision(entity1));
					if (!collider1->IsTrigger() && !collider2->IsTrigger())
					{
						ResolveCollision(*entity1, collider1->GetRadius(), *entity2, collider2->GetRadius());
					}
				}
			}
		}
	}
}

void CollisionDetectionSystem::ResolveCollision(Entity& entity1, float radius1, Entity& entity2, float radius2)
{
	PhysicsComponent* physicsComponent1 = entity1.GetComponent<PhysicsComponent>();
	PhysicsComponent* physicsComponent2 = entity2.GetComponent<PhysicsComponent>();
	Vector2D velocity1 = physicsComponent1->GetVelocity();
	Vector2D velocity2 = physicsComponent2->GetVelocity();

	Vector2D difference = entity1.GetPosition() - entity2.GetPosition();
	Vector2D normal = difference.GetNormalized();

	float collisionSpeed = normal.DotProduct(velocity2 - velocity1);

	//If dot product is positive, it means objects are moving towards each other
	if (collisionSpeed > 0)
	{
		float j = -collisionSpeed / 2;
		//Collision impusle vector
		Vector2D impulse = normal * j;
		// change momentum of the circles
		velocity1 -= impulse;
		velocity2 += impulse;

		physicsComponent1->SetVelocity(velocity1);
		physicsComponent2->SetVelocity(velocity2);
	}
}
