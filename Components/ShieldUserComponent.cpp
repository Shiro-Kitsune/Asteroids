#include "stdafx.h"

ShieldUserComponent::ShieldUserComponent(float shieldCooldown, float shieldDuration)
{
	m_shieldCooldown = shieldCooldown;
	m_shieldDuration = shieldDuration;
	m_shieldActivated = false;
	m_shieldCreated = false;
	m_timeElapsedSinceShieldActivation = 0.0f;
}

bool ShieldUserComponent::IsShieldCreated() const
{
	return m_shieldCreated;
}

bool ShieldUserComponent::IsShieldActivated() const
{
	return m_shieldActivated;
}

bool ShieldUserComponent::IsShieldReady() const
{
	return m_timeElapsedSinceShieldActivation >= m_shieldCooldown;
}

bool ShieldUserComponent::IsShieldExprired() const
{
	return m_timeElapsedSinceShieldActivation >= m_shieldDuration;
}

void ShieldUserComponent::ActivateShield()
{
	m_shieldActivated = true;
	m_shieldCreated = true;
	m_timeElapsedSinceShieldActivation = 0.0f;
}

void ShieldUserComponent::DeactivateShield()
{
	m_shieldActivated = false;
}

void ShieldUserComponent::IncreaseTimeElapsedSinceShieldActivation(float deltaTime)
{
	m_timeElapsedSinceShieldActivation += deltaTime;
}
