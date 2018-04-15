#pragma once

class PhysicsSystem : public System
{
public:
	void Init(GameState& gameState) {}
	void Update(float deltaTime, GameState& gameState);
private:
	void UpdateEntity(float deltaTime, Entity& entity, PhysicsComponent& physComponent, bool wrapAroundScreen);
	void UpdateParticles(float deltaTime, const ParticleEmmiter& particleEmmiter);
};
