#include "stdafx.h"

void EnemyShipSystem::Init(GameState & gameState)
{
	m_player = gameState.GetEntityManager().FindEntityByName("player1");
	m_entityManager = &gameState.GetEntityManager();
}

void EnemyShipSystem::Update(float deltaTime, GameState & gameState)
{
	EntityManager& entityManager = gameState.GetEntityManager();
	EventManager& eventManager = gameState.GetEventManager();

	HandleEvents(eventManager);

	for (auto& entity : entityManager.GetEntities())
	{
		EnemyShipComponent* ship = entity->GetComponent<EnemyShipComponent>();
		if (ship == nullptr)
		{
			continue;
		}

		PhysicsComponent* physicsComponent = entity->GetComponent<PhysicsComponent>();
		HealthComponent* healthComponent = entity->GetComponent<HealthComponent>();
		if (m_player != nullptr)
		{
			HandleCollisions(*entity, *healthComponent);

			Vector2D steeringForce;
			steeringForce = FollowPlayer(*entity, *ship, *physicsComponent);
			physicsComponent->ApplyForce(steeringForce);

			Shoot(*entity, eventManager);
		}

		ActivateShield(*entity, eventManager);

		RenderingComponent* renderingComponent = entity->GetComponent<RenderingComponent>();
		ChangeColor(ship->GetColor(), *healthComponent, *renderingComponent);
	}
}

void EnemyShipSystem::HandleEvents(EventManager& eventManager)
{
	for (auto& event : eventManager.GetEvents())
	{
		if (event->GetEventType() != EventType::GameEvent)
		{
			continue;
		}

		GameEvent* gameEvent = static_cast<GameEvent*>(event.get());
      	if (gameEvent->GetGameEventType() == GameEventType::ShipSpawned)
		{
			gameEvent->MarkAsRead();
			AddEnemyShip(gameEvent->GetEntityId());
		}
		else if (gameEvent->GetGameEventType() == GameEventType::ShipDestroyed)
		{
			gameEvent->MarkAsRead();
			RemoveEnemyShip(gameEvent->GetEntityId());
		}
	}
}

Vector2D EnemyShipSystem::FollowPlayer(Entity& entity, EnemyShipComponent& ship, PhysicsComponent& physicsComponent)
{
	entity.SetAngle(physicsComponent.GetVelocity().Heading() - 90);

	Vector2D tv = m_player->GetComponent<PhysicsComponent>()->GetVelocity();
	Vector2D steeringForce;

	// Calculate the ahead point
	tv.Normalize();
	tv *= ship.GetMinDistanceToPlayer();
	Vector2D ahead = m_player->GetPosition() + tv;

	// Calculate the behind point
	Vector2D behind = m_player->GetPosition() - entity.GetPosition();
	behind.Normalize();
	behind *= ship.GetMinDistanceToPlayer();
	behind = m_player->GetPosition() - behind;

	// If the ship is on the player's sight, add a force to evade the route immediately
	if (IsOnPlayerSight(entity.GetPosition(), ahead, ship.GetMinDistanceToPlayer()))
	{
		steeringForce += Evade(entity.GetPosition(), physicsComponent.GetVelocity(), ship.GetMaxSpeed());
	}

	// Add a force to arrive at the behind point
	steeringForce += Arrive(behind, entity.GetPosition(), physicsComponent.GetVelocity(), ship.GetMaxSpeed(), ship.GetSlowingRadius());

	// Add separation force
	steeringForce += Separate(&entity, physicsComponent.GetVelocity());
	return steeringForce;
}

Vector2D EnemyShipSystem::Arrive(const Vector2D & target, const Vector2D & position, const Vector2D & velocity, const float maxSpeed, const float slowingRadius)
{
	// Calculate the desired velocity
	Vector2D desiredVelocity = target - position;
	float distance = desiredVelocity.Magnitude();
	desiredVelocity.Normalize();
	desiredVelocity *= maxSpeed;

	// Check the distance to detect whether the ship is inside the slowing area
	if (distance < slowingRadius)
	{
		desiredVelocity *= (distance / slowingRadius);
	}

	// Return steering force
	return desiredVelocity - velocity;
}

Vector2D EnemyShipSystem::Separate(Entity * entity, const Vector2D & velocity)
{
	Vector2D steeringForce;
	int neighborCount = 0;

	for (auto& ship : m_enemyShips)
	{
		float distance = entity->GetPosition().Distance(ship->GetPosition());
		if ( (entity->GetId() != ship->GetId()) && (distance <= 50) )
		{
			steeringForce += ship->GetPosition() - entity->GetPosition();
			neighborCount++;
		}
	}

	if (neighborCount > 0)
	{
		steeringForce /= neighborCount;
		steeringForce *= -1.0f;
		steeringForce.Normalize();
		steeringForce *= 150.0f;
	}

	return steeringForce;
}

Vector2D EnemyShipSystem::Evade(const Vector2D & position, const Vector2D & velocity, const float maxSpeed)
{
	Vector2D distance = m_player->GetPosition() - position;
	int updatesAhead = distance.Magnitude() / maxSpeed;
	Vector2D futurePosition = m_player->GetPosition() + m_player->GetComponent<PhysicsComponent>()->GetVelocity() * updatesAhead;
	return Flee(futurePosition, position, velocity, maxSpeed);
}

Vector2D EnemyShipSystem::Flee(const Vector2D & target, const Vector2D & position, const Vector2D & velocity, float maxSpeed)
{
	Vector2D desiredVelocity = position - target;
	desiredVelocity.Normalize();
	desiredVelocity *= maxSpeed;
	return desiredVelocity - velocity;
}

bool EnemyShipSystem::IsOnPlayerSight(const Vector2D & shipPosition, const Vector2D & ahead, const float sightRadius)
{
	float sightRadiusSq = sightRadius * sightRadius;
	return (shipPosition.DistanceSquared(ahead) <= sightRadiusSq) || (shipPosition.DistanceSquared(m_player->GetPosition()) <= sightRadiusSq);
}

void EnemyShipSystem::Shoot(Entity& entity, EventManager& eventManager)
{
	ShooterComponent* shooterComponent = entity.GetComponent<ShooterComponent>();
	if (shooterComponent != nullptr)
	{
		if (shooterComponent->IsReadyToShoot())
		{
			eventManager.AddEvent(std::make_unique<GameEvent>(GameEventType::ShootActionRequested, entity.GetId()));
		}
	}
}

void EnemyShipSystem::ActivateShield(Entity & entity, EventManager & eventManager)
{
	ShieldUserComponent* shieldUserComponent = entity.GetComponent<ShieldUserComponent>();
	if (shieldUserComponent != nullptr && shieldUserComponent->IsShieldReady())
	{
		eventManager.AddEvent(std::make_unique<GameEvent>(GameEventType::CreateShield, entity.GetId()));
	}
}

void EnemyShipSystem::ChangeColor(const Color & color, HealthComponent & health, RenderingComponent & renderingComponent)
{
	int lives = health.GetLives();
	int maxLives = health.GetMaxLives();
	float red = Utilities::MapValue(lives, 0.0f, maxLives, 1.0f, color.red);
	float green = Utilities::MapValue(lives, 0.0f, maxLives, 1.0f, color.green);
	float blue = Utilities::MapValue(lives, 0.0f, maxLives, 1.0f, color.blue);
	renderingComponent.SetColor(Color(red, green, blue));
}

void EnemyShipSystem::HandleCollisions(Entity & entity, HealthComponent & health)
{
	for (auto collision : entity.GetCollisions())
	{
		Entity* collidedWith = collision.GetEntity();
		PlayerComponent* player = collidedWith->GetComponent<PlayerComponent>();

		if (player != nullptr)
		{
			health.DecreaseLives();
			break;
		}
	}
}

void EnemyShipSystem::AddEnemyShip(unsigned int id)
{
	auto ship = m_entityManager->FindEntityById(id);
	if (ship != nullptr)
	{
		m_enemyShips.push_back(std::move(ship));
    }
}

void EnemyShipSystem::RemoveEnemyShip(unsigned int id)
{
	auto position = std::find_if(m_enemyShips.begin(), m_enemyShips.end(), [id](const std::shared_ptr<Entity>& ship) { return ship->GetId() == id; });
	if (position != m_enemyShips.end())
	{
		m_enemyShips.erase(position);
	}
}
