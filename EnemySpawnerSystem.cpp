#include "stdafx.h"

void EnemySpawnerSystem::Init(GameState& gameState)
{
	m_timeElapsedSinceShipSpawning = 0.0f;
	m_shipSpawnCooldown = 30000.0f;
	m_numOfAsteroidsToCreate = 4;
	m_numOfSmallestAsteroidsDestroyed = 0;

	m_shipSpawnPoints[0] = Vector2D(10.0f, 10.0f);
	m_shipSpawnPoints[1] = Vector2D(10.0f, APP_VIRTUAL_HEIGHT-10.0f);
	m_shipSpawnPoints[2] = Vector2D(APP_VIRTUAL_WIDTH - 10.0f, APP_VIRTUAL_HEIGHT - 10.0f);
	m_shipSpawnPoints[3] = Vector2D(APP_VIRTUAL_WIDTH - 10.0f, 10.0f);

	m_entityFactory = &gameState.GetEntityFactory();
}

void EnemySpawnerSystem::Update(const float deltaTime, GameState & gameState)
{
	EntityManager& entityManager = gameState.GetEntityManager();
	EventManager& eventManager = gameState.GetEventManager();

	m_timeElapsedSinceShipSpawning += deltaTime;
	if (m_timeElapsedSinceShipSpawning >= m_shipSpawnCooldown)
	{
		SpawnShips(eventManager, entityManager);
    }

    if (SmallestAsteroidDestroyed(eventManager))
    {
    	if (++m_numOfSmallestAsteroidsDestroyed == 4)
        {
        	m_numOfSmallestAsteroidsDestroyed = 0;
        	++m_numOfAsteroidsToCreate;
        }
    }

    if (m_numOfAsteroidsToCreate > 0)
    {
    	SpawnAsteroid(entityManager);
    }
}

void EnemySpawnerSystem::SpawnShips(EventManager & eventManager, EntityManager & entityManager)
{
	m_timeElapsedSinceShipSpawning = 0.0f;
	int shipType = Utilities::Random(0, 1); // 0 is RamShip, 1 is Ship
	int numOfShips = Utilities::Random(1, 4);

	//Shuffle spawn points so that we can spawn ships in different places
	unsigned seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
	std::shuffle(m_shipSpawnPoints.begin(), m_shipSpawnPoints.end(), std::default_random_engine(seed));

	for (int i = 0; i < numOfShips; ++i)
	{
		if (shipType == 0)
		{
			entityManager.AddEntity(m_entityFactory->CreateRamShip(m_shipSpawnPoints[i]));
		}
		else
		{
		    unsigned int id = entityManager.AddEntity(m_entityFactory->CreateShip(m_shipSpawnPoints[i]));
			eventManager.AddEvent(std::make_unique<GameEvent>(GameEventType::ShipSpawned, id));
		}
    }
}

void EnemySpawnerSystem::SpawnAsteroid(EntityManager & entityManager)
{
	for (int i = 0; i < 5; ++i)
	{
		float x = static_cast<float>(Utilities::Random(0, APP_VIRTUAL_WIDTH));
		float y = static_cast<float>(Utilities::Random(0, APP_VIRTUAL_HEIGHT));
		Vector2D newPosition(x, y);
		float checkRadius = 63.0f;

		bool noCollision = true;
		for (auto& entity : entityManager.GetEntities())
		{
			BoundingCircle2D* circle = entity->GetComponent<BoundingCircle2D>();
			if (circle != nullptr)
			{
				if (Utilities::CircleOverlap(newPosition, checkRadius, entity->GetPosition(), circle->GetRadius()))
				{
					noCollision = false;
					break;
				}
			}
		}

		if (noCollision)
		{
			--m_numOfAsteroidsToCreate;
			entityManager.AddEntity(m_entityFactory->CreateAsteroid(newPosition));
			break;
		}
	}
}

bool EnemySpawnerSystem::SmallestAsteroidDestroyed(EventManager & eventManager)
{
	for (auto& event : eventManager.GetEvents())
	{
		if(event->GetEventType() != EventType::GameEvent)
		{
			continue;
		}

		GameEvent* gameEvent = static_cast<GameEvent*>(event.get());
		if (gameEvent->GetGameEventType() == GameEventType::SmallestAsteroidDestroyed)
		{
			gameEvent->MarkAsRead();
			gameEvent->GetEntityId();
			return true;
		}
	}
	return false;
}