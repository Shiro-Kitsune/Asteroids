#include "stdafx.h"

EnemyShipComponent::EnemyShipComponent(float maxSpeed, float maxForce, float minDistanceToPlayer, float slowingRadius, const Color & color) : m_color(color)
{
	m_maxSpeed = maxSpeed;
	m_maxForce = maxForce;
	m_minDistanceToPlayer = minDistanceToPlayer;
	m_slowingRadius = slowingRadius;
}

float EnemyShipComponent::GetMaxSpeed() const
{
	return m_maxSpeed;
}

float EnemyShipComponent::GetMaxForce() const
{
	return m_maxForce;
}

float EnemyShipComponent::GetMinDistanceToPlayer() const
{
	return m_minDistanceToPlayer;
}

float EnemyShipComponent::GetSlowingRadius() const
{
	return m_slowingRadius;
}

const Color& EnemyShipComponent::GetColor() const
{
	return m_color;
}