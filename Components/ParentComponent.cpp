#include "stdafx.h"

ParentComponent::ParentComponent(Entity * parentEntity)
{
	m_parentEntity = parentEntity;
}

Entity * ParentComponent::GetParentEntity() const
{
	return m_parentEntity;
}
