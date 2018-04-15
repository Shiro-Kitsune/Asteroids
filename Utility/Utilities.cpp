#include "stdafx.h"



int Utilities::Random(int min, int max)
{
	return (min + (rand() % (int)(max - min + 1)));
}

float Utilities::ToRadians(float angle)
{
	return static_cast<float>(angle * M_PI / 180.0f);
}

float Utilities::ToDegrees(float angle)
{
	return static_cast<float>(angle * 180.0f / M_PI);
}

float Utilities::MapValue(float value, float start1, float end1, float start2, float end2)
{
	float result = start2 + (end2 - start2) * ((value - start1) / (end1 - start1));
	return result;
}

bool Utilities::CircleOverlap(const Vector2D & position1, float radius1, const Vector2D & position2, float radius2)
{
	float distanceSquared = position1.DistanceSquared(position2);
	float radiusSum = radius1 + radius2;

	return (distanceSquared < radiusSum * radiusSum);
}