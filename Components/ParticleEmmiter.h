#pragma once

class ParticleEmmiter : public Component
{
public:
	ParticleEmmiter(float particleLifeTime);
	const std::vector<std::unique_ptr<Entity>>& GetParticles() const;
	void ApplyForceToParticles(const Vector2D& force);
	void AddParticle(const Vector2D& velocity, float angle, const Color& color);
	void AddParticle(const Vector2D& velocity, float angle, const Color& color, std::vector<LineSegment> lines);
	void RemoveParticles();
	void RemoveExpiredParticles();
private:
	std::vector<std::unique_ptr<Entity>> m_particles;
	float m_particleLifeTime;
};
