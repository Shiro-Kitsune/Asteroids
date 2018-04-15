#include "stdafx.h"

EnemyComponent::EnemyComponent(int pointsWorth, const std::initializer_list<ItemType> & list) : m_pointsWorth(pointsWorth)
{
	int numOfLootTypes = list.size();
	
	if(numOfLootTypes != 0)
	{
		float probabilityStep = 1.0f / numOfLootTypes;

		float num = Utilities::Random(0.0f, 1.0f);
		if(num < 0.15)
		{
			num = Utilities::Random(0.0f, 1.0f);

			int count = 1;
			for (auto &element : list)
			{
				if(num < probabilityStep * count)
				{
					m_type = element;
					break;
				}
				++count;
			}
		}
		else
		{
			m_type = ItemType::None;
		}
    }
    else
    {
    	m_type = ItemType::None;
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