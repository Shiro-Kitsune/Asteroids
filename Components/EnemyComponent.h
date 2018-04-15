#pragma once

class EnemyComponent : public Component
{
public:
	EnemyComponent(int pointsWorth, const std::initializer_list<ItemType> & list);
	int GetPointsWorth() const;
	ItemType GetLootType() const;
private:
	int m_pointsWorth;
	ItemType m_type;
};
