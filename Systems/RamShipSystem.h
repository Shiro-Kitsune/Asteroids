#pragma once

class RamShipSystem : public System
{
public:
	void Init(GameState& gameState);
	void Update(float deltaTime, GameState& gameState);
private:
	Vector2D Seek(const Vector2D & position, const Vector2D & velocity, float maxSpeed, float maxForce);
	void HandleCollisions(Entity& entity);
	void ChangeColor(Entity& entity, RamShipComponent& ramShip, RenderingComponent& renderingComponent, float deltaTime);
private:
	std::shared_ptr<Entity> m_player;
};
