#pragma once

class EnemyShipComponent : public Component
{
public:
	EnemyShipComponent(float maxSpeed, float maxForce, float minDistanceToPlayer, float slowingRadius, const Color & color);
	float GetMaxSpeed() const;
	float GetMaxForce() const;
	float GetMinDistanceToPlayer() const;
	float GetSlowingRadius() const;
	const Color& GetColor() const;
private:
	float m_maxSpeed;
	float m_maxForce;
	float m_minDistanceToPlayer;
	float m_slowingRadius;
	Color m_color;
};
