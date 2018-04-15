#pragma once

class BoundingCircle2D : public Component
{
public:
	BoundingCircle2D(float radius, bool trigger = true);
	float GetRadius() const;
	void SetRadius(float radius);
	bool IsTrigger() const;
private:
	float m_radius;
	float m_trigger;
};