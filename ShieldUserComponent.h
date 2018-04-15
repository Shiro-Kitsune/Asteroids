#pragma once

class ShieldUserComponent : public Component
{
public:
	ShieldUserComponent(float shieldCooldown, float shieldDuration);
	bool IsShieldCreated() const;
	bool IsShieldActivated() const;
	bool IsShieldReady() const;
	bool IsShieldExprired() const;
	void ActivateShield();
	void DeactivateShield();
	void IncreaseTimeElapsedSinceShieldActivation(float deltaTime);
private:
	float m_shieldCooldown;
	float m_shieldDuration;
	bool m_shieldActivated;
	bool m_shieldCreated;
	float m_timeElapsedSinceShieldActivation;
};