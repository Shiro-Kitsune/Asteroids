#pragma once

class EnemyShipSystem : public System
{
public:
	void Init(GameState& gameState);
	void Update(float deltaTime, GameState& gameState);
private:
	void HandleEvents(EventManager& eventManager);
	Vector2D FollowPlayer(Entity& entity, EnemyShipComponent& ship, PhysicsComponent& physicsComponent);
	Vector2D Arrive(const Vector2D& target, const Vector2D& position, const Vector2D& velocity, float maxSpeed, float slowingRadius);
	Vector2D Separate(Entity* entity, const Vector2D & velocity);
	Vector2D Evade(const Vector2D& position, const Vector2D& velocity, float maxSpeed);
	Vector2D Flee(const Vector2D& target, const Vector2D& position, const Vector2D& velocity, float maxSpeed);
	bool IsOnPlayerSight(const Vector2D& position, const Vector2D& pointAheadOfTarget, float sightRadius);
	void Shoot(Entity& entity, EventManager& manager);
	void ActivateShield(Entity& entity, EventManager & eventManager);
	void ChangeColor(const Color& color, HealthComponent& health, RenderingComponent& renderingComponent);
	void HandleCollisions(Entity& entity, HealthComponent& health);
	void AddEnemyShip(unsigned int id);
	void RemoveEnemyShip(unsigned int id);
private:
	std::shared_ptr<Entity> m_player;
	std::vector<std::shared_ptr<Entity>> m_enemyShips;
	EntityManager* m_entityManager;
};