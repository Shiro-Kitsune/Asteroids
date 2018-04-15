#include "stdafx.h"

ExpireComponent::ExpireComponent(float timeToLive) : m_timeToLive(timeToLive), m_existenceTime(0.0f)
{
}

void ExpireComponent::IncreaseExistenceTime(float deltaTime)
{
	m_existenceTime += deltaTime;
}

bool ExpireComponent::IsExpired() const
{
	return (m_existenceTime >= m_timeToLive);
}

