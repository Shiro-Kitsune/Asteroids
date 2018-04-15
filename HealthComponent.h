#pragma once

class HealthComponent : public Component
{
public:
	HealthComponent(int maxLives);

	void DecreaseLives();
	void HealFully();
	void Heal();
	bool IsDead() const;

	int GetLives() const;
	int GetMaxLives() const;
	void SetLives(int lives);
private:
	int m_lives;
	int m_maxLives;
};