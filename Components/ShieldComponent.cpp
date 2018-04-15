#include "stdafx.h"

ShieldComponent::ShieldComponent(const Color & color) : m_shieldColor(color)
{
	m_shieldRenderingComponent = nullptr;
}

void ShieldComponent::IncreaseShieldLastUsedTime(float deltaTime)
{
	m_shieldLastUsedTime += deltaTime;
}

bool ShieldComponent::IsShieldActive() const
{
	return m_shieldActive;
}

void ShieldComponent::ActivateShield()
{
	if ((m_shieldLastUsedTime >= SHIELD_COOLDOWN) && !m_shieldActive)
	{
		m_shieldActive = true;
		m_shieldLastUsedTime = 0.0f;
	}
}

void ShieldComponent::DeactivateShield()
{
	m_shieldActive = false;
}

float ShieldComponent::GetShieldLastUsedTime() const
{
	return m_shieldLastUsedTime;
}

void ShieldComponent::SetShieldRenderingComponent(RenderingComponent * shieldRenderingComponent)
{
	m_shieldRenderingComponent = shieldRenderingComponent;
}

RenderingComponent * ShieldComponent::GetShieldRenderingComponent()
{
	return m_shieldRenderingComponent;
}
