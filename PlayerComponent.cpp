#include "stdafx.h"

PlayerComponent::PlayerComponent(float powerUpTimeLimit, float rotationFactor)
{
	m_score = 0;
	m_active = false;
	m_deactivationTimeLimit = 1000.0f;
	m_timeElapsedSinceDeactivation = 1000.0f;
	m_powerUp = false;
	m_powerUpTime = 0.0f;
	m_powerUpTimeLimit = powerUpTimeLimit;
	m_rotationFactor = rotationFactor;
}

void PlayerComponent::AddToScore(const int points)
{
	m_score += points;
}

int PlayerComponent::GetScore() const
{
	return m_score;
}

float PlayerComponent::GetRotationFactor() const
{
	return m_rotationFactor;
}

void PlayerComponent::SetRotationFactor(const float rotationFactor)
{
	m_rotationFactor = rotationFactor;
}

void PlayerComponent::Deactivate()
{
	m_active = false;
	m_timeElapsedSinceDeactivation = 0.0f;
}

void PlayerComponent::Activate()
{
	m_active = true;
}

bool PlayerComponent::IsActive() const
{
	return m_active;
}

bool PlayerComponent::ReadyToBeActivated() const
{
	return m_timeElapsedSinceDeactivation >= m_deactivationTimeLimit;
}

void PlayerComponent::IncreaseTimeElapsedSinceDeactivation(const float deltaTime)
{
	m_timeElapsedSinceDeactivation += deltaTime;
}

void PlayerComponent::PowerUp()
{
	m_powerUpTime = 0.0f;
	m_powerUp = true;
}

void PlayerComponent::IncreasePowerUpInEffectTime(const float deltaTime)
{
	m_powerUpTime += deltaTime;
	if (m_powerUpTime >= m_powerUpTimeLimit)
	{
		m_powerUp = false;
	}
}

bool PlayerComponent::IsPowerUpInEffect() const
{
	return m_powerUp;
}