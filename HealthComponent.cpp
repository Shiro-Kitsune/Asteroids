#include "stdafx.h"

HealthComponent::HealthComponent(int maxLives)
{
	m_maxLives = maxLives;
	m_lives = maxLives;
}

void HealthComponent::DecreaseLives()
{
	--m_lives;
}

void HealthComponent::HealFully()
{
	m_lives = m_maxLives;
}

void HealthComponent::Heal()
{
	if (m_lives < m_maxLives)
	{
		++m_lives;
	}
}

bool HealthComponent::IsDead() const
{
	return m_lives <= 0;
}

int HealthComponent::GetLives() const
{
	return m_lives;
}

int HealthComponent::GetMaxLives() const
{
	return m_maxLives;
}

void HealthComponent::SetLives(int lives)
{
	m_lives = lives;
}