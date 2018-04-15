#pragma once

enum class ItemType { Mineral, Heart, PowerUp, None };

class ItemComponent : public Component
{
public:
	ItemComponent(ItemType type);
	ItemType GetType() const;
private:
	ItemType m_type;
};