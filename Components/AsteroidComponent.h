#pragma once

class AsteroidComponent : public Component
{
public:
	AsteroidComponent(int size = 1);
	int GetSize() const;
private:
	int m_size;
};
