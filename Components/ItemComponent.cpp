#include "stdafx.h"

ItemComponent::ItemComponent(ItemType type)
{
	m_type = type;
}

ItemType ItemComponent::GetType() const
{
	return m_type;
}
