#pragma once

class EnemySpawnerSystem : public System
{
public:
	void Init(GameState& gameState);
	void Update(float deltaTime, GameState& gameState);
private:
	void SpawnShips(EventManager & eventManager, EntityManager & entityManager);
	void SpawnAsteroid(EntityManager & manager);
	bool SmallestAsteroidDestroyed(EventManager & eventManager);
private:
	std::array<Vector2D, 4> m_shipSpawnPoints;
	float m_timeElapsedSinceShipSpawning;
	float m_shipSpawnCooldown;
	int m_numOfAsteroidsToCreate;
	int m_numOfSmallestAsteroidsDestroyed;

	EntityFactory* m_entityFactory;
};