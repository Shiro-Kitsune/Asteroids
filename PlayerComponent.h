#pragma once

class PlayerComponent : public Component
{
public:
	PlayerComponent(float powerUpTimeLimit, float m_rotationFactor);

	void AddToScore(int points);
	int GetScore() const;

	float GetRotationFactor() const;
	void SetRotationFactor(float rotFactor);

	void Deactivate();
	void Activate();
	bool IsActive() const;
	bool ReadyToBeActivated() const;
	void IncreaseTimeElapsedSinceDeactivation(float deltaTime);
	
	void PowerUp();
	void IncreasePowerUpInEffectTime(float deltaTime);
	bool IsPowerUpInEffect() const;
private:
	float m_rotationFactor;
	int m_score;
	bool m_active;
	float m_deactivationTimeLimit;
	float m_timeElapsedSinceDeactivation;
	bool m_powerUp;
	float m_powerUpTime;
	float m_powerUpTimeLimit;
};