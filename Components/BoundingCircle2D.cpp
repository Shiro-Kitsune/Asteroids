#include "stdafx.h"

BoundingCircle2D::BoundingCircle2D(float radius, bool trigger) : m_radius(radius), m_trigger(trigger)
{}

float BoundingCircle2D::GetRadius() const
{
	return m_radius;
}

void BoundingCircle2D::SetRadius(float radius)
{
	m_radius = radius;
}

bool BoundingCircle2D::IsTrigger() const
{
	return m_trigger;
}
