#pragma once

class Collision
{
public:
	Collision(Entity* entity);
	Entity* GetEntity();
private:
	Entity* m_collidedWith;
};