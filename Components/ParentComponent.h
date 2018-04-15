#pragma once

class ParentComponent : public Component
{
public:
	ParentComponent(Entity* parentEntity);
	Entity * GetParentEntity() const;
private:
	Entity * m_parentEntity;
};
