#pragma once

class ExpireComponent : public Component
{
public:
	ExpireComponent(float timeToLive);
	void IncreaseExistenceTime(float deltaTime);
	bool IsExpired() const;
private:
	float m_timeToLive;
	float m_existenceTime;
};
