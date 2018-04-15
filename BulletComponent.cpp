#include "stdafx.h"

BulletComponent::BulletComponent(Entity * owner, bool playerOwner) : m_owner(owner), m_playerOwner(playerOwner)
{
}

Entity * BulletComponent::GetOwner() const
{
	return m_owner;
}

bool BulletComponent::IsPlayerOwner() const
{
	return m_playerOwner;
}