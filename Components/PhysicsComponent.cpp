#include "stdafx.h"

PhysicsComponent::PhysicsComponent(const Vector2D & velocity, const Vector2D & acceleration, const float rotationSpeed,
	const float dragFactor) : m_velocity(velocity), m_acceleration(acceleration)
{
	m_rotationalSpeed = rotationSpeed;
	m_dampingCoefficient = dragFactor;
}

void PhysicsComponent::ApplyForce(Vector2D force)
{
	m_acceleration += force;
}

const Vector2D& PhysicsComponent::GetVelocity() const
{
	return m_velocity;
}

const Vector2D & PhysicsComponent::GetAcceleration() const
{
	return m_acceleration;
}

float PhysicsComponent::GetRotationalSpeed() const
{
	return m_rotationalSpeed;
}

float PhysicsComponent::GetDamping() const
{
	return m_dampingCoefficient;
}

//Setters
void PhysicsComponent::SetVelocity(const Vector2D& velocity)
{
	m_velocity = velocity;
}

void PhysicsComponent::SetAcceleration(const Vector2D & acceleration)
{
	m_acceleration = acceleration;
}

void PhysicsComponent::SetRotationalSpeed(const float rotSpeed)
{
	m_rotationalSpeed = rotSpeed;
}

void PhysicsComponent::SetDamping(const float dragFactor)
{
	m_dampingCoefficient = dragFactor;
}
