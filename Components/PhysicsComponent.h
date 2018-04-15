#pragma once

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(const Vector2D& velocity = Vector2D(0.0f, 0.0f), const Vector2D & acceleration = Vector2D(0.0f, 0.0f), float rotationSpeed = 0.0f, float damping = 1.0f);

	void ApplyForce(Vector2D force);
	const Vector2D& GetVelocity() const;
	const Vector2D& GetAcceleration() const;
	float GetRotationalSpeed() const;
	float GetDamping() const;

	void SetVelocity(const Vector2D& velocity);
	void SetAcceleration(const Vector2D& acceleration);
	void SetRotationalSpeed(float rotSpeed);
	void SetDamping(float damping);
private:
	Vector2D m_velocity;
	Vector2D m_acceleration;
	float m_rotationalSpeed;
	float m_dampingCoefficient;
};
