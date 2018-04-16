#include "stdafx.h"

EnemyComponent::EnemyComponent(int pointsWorth) : m_pointsWorth(pointsWorth)
{
	float num = Utilities::Random(0.0f, 1.0f);
	if (num < 0.9f)
	{
		m_type = ItemType::None;
	}
	else
	{
		num = Utilities::Random(0.0f, 1.0f);
		if (num < 0.1f)
		{
			m_type = ItemType::Heart;
		}
		else if (num < 0.35)
		{
			m_type = ItemType::PowerUp;
		}
		else
		{
			m_type = ItemType::Mineral;
		}
	}
}

int EnemyComponent::GetPointsWorth() const
{
	return m_pointsWorth;
}

ItemType EnemyComponent::GetLootType() const
{
	return m_type;
}
