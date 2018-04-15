#include "stdafx.h"

RamShipComponent::RamShipComponent(float maxSpeed, float maxForce) : m_maxSpeed(maxSpeed), m_maxForce(maxForce), m_standardColor(1.0f, 1.0f, 1.0f), m_alternateColor(1.0f, 0.0f, 0.0f)
{
	m_standardColorNext = false;
	m_colorDuration = 200.0f;
	m_timeElapsedSinceColorChange = 0.0f;
}

float RamShipComponent::GetMaxSpeed() const
{
	return m_maxSpeed;
}

float RamShipComponent::GetMaxForce() const
{
	return m_maxForce;
}

const Color & RamShipComponent::GetNextColor()
{
	m_timeElapsedSinceColorChange = 0.0f;
	m_standardColorNext = !m_standardColorNext;
	return (m_standardColorNext) ? m_standardColor : m_alternateColor;
}

bool RamShipComponent::ReadyToChangeColor() const
{
	return m_timeElapsedSinceColorChange >= m_colorDuration;
}

void RamShipComponent::IncreaseTimeElapsedSinceColorChange(float deltaTime)
{
	m_timeElapsedSinceColorChange += deltaTime;
}