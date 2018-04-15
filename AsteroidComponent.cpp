#include "stdafx.h"

AsteroidComponent::AsteroidComponent(int size)
{
	m_size = size;
}

int AsteroidComponent::GetSize() const
{
	return m_size;
}