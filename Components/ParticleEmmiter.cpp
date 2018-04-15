#include "stdafx.h"

struct predicate
{
	bool operator()(const std::unique_ptr<Entity> & entity) const
	{
		return entity->NeedsToBeRemoved();
	}
};

ParticleEmmiter::ParticleEmmiter(float particleLifeTime)
{
	m_particleLifeTime = particleLifeTime;
}

const std::vector<std::unique_ptr<Entity>>& ParticleEmmiter::GetParticles() const
{
	return m_particles;
}

void ParticleEmmiter::ApplyForceToParticles(const Vector2D & force)
{
	for (auto& particle : m_particles)
	{
		particle->GetComponent<PhysicsComponent>()->ApplyForce(force);
	}
}

void ParticleEmmiter::AddParticle(const Vector2D & velocity, const float angle, const Color & color)
{
	float radius = 1.5f;
	std::vector<Vector2D> points;
	for (double ang = 0; ang < 2 * M_PI; ang += 1)
	{
		float px = static_cast<float>(sin(ang) * radius);
		float py = static_cast<float>(-cos(ang) * radius);
		points.push_back(Vector2D(px, py));
	}

	std::vector<LineSegment> lines;
	for (int i = 0; i < points.size(); ++i)
	{
		if (i != points.size() - 1)
		{
			lines.push_back(LineSegment(points[i], points[i + 1]));
	    }
	    else
	    {
	    	lines.push_back(LineSegment(points[i], points[0]));
	    }
	}

	std::unique_ptr<Entity> particle = std::make_unique<Entity>(0, Vector2D(0.0f, 0.0f), angle);
	particle->AddComponent(std::make_unique<PhysicsComponent>(velocity));
	particle->AddComponent(std::make_unique<RenderingComponent>(color, lines));
	particle->AddComponent(std::make_unique<ExpireComponent>(m_particleLifeTime));
	m_particles.push_back(std::move(particle));
}

void ParticleEmmiter::AddParticle(const Vector2D & velocity, const float angle, const Color & color, std::vector<LineSegment> lines)
{
	std::unique_ptr<Entity> particle = std::make_unique<Entity>(0, Vector2D(0.0f, 0.0f), angle);
	particle->AddComponent(std::make_unique<RenderingComponent>(color, lines));
	particle->AddComponent(std::make_unique<ExpireComponent>(m_particleLifeTime));
	m_particles.push_back(std::move(particle));
}

void ParticleEmmiter::RemoveParticles()
{
	m_particles.clear();
}

void ParticleEmmiter::RemoveExpiredParticles()
{
	m_particles.erase(std::remove_if(m_particles.begin(), m_particles.end(), predicate()), m_particles.end());
}
