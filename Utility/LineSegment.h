#pragma once

class LineSegment
{
public:
	LineSegment(const Vector2D& startPoint, const Vector2D& endPoint);
	float Length() const;
	float LengthSquared() const;
	Vector2D Normal() const;
public:
	Vector2D m_startPoint;
	Vector2D m_endPoint;
};
