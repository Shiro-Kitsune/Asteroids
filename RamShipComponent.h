#pragma once

class RamShipComponent : public Component
{
public:
	RamShipComponent(float maxSpeed, float maxForce);
	float GetMaxSpeed() const;
	float GetMaxForce() const;
	const Color& GetNextColor();
	bool ReadyToChangeColor() const;
	void IncreaseTimeElapsedSinceColorChange(float deltaTime);
private:
	float m_maxSpeed;
	float m_maxForce;
	Color m_standardColor;
	Color m_alternateColor;
	bool m_standardColorNext;
	float m_colorDuration;
	float m_timeElapsedSinceColorChange;
};