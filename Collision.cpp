#include "stdafx.h"

Collision::Collision(Entity* entity)
{
	m_collidedWith = entity;
}

Entity* Collision::GetEntity()
{
	return m_collidedWith;
}