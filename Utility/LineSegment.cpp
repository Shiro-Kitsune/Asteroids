#include "stdafx.h"

LineSegment::LineSegment(const Vector2D& startPoint, const Vector2D& endPoint) : m_startPoint(startPoint), m_endPoint(endPoint)
{
}

float LineSegment::Length() const
{
	return m_startPoint.Distance(m_endPoint);
}

float LineSegment::LengthSquared() const
{
	return m_startPoint.DistanceSquared(m_endPoint);
}

Vector2D LineSegment::Normal() const
{
	Vector2D diff = m_endPoint - m_startPoint;
	return Vector2D(-diff.y, diff.x);
}
