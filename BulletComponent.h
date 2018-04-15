#pragma once

class BulletComponent : public Component
{
public:
	BulletComponent(Entity* owner, bool playerOwner);
	Entity* GetOwner() const;
	bool IsPlayerOwner() const;
private:
	Entity * m_owner;
	bool m_playerOwner;
};