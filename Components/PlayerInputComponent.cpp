#include "stdafx.h"

PlayerInputComponent::PlayerInputComponent(int accelerateKeyCode, int shootKeyCode, int rotateLeftKeyCode, int rotateRightKeyCode, int shieldKeyCode)
{
	m_accelerateKeyCode = accelerateKeyCode;
	m_shootKeyCode = shootKeyCode;
	m_rotateLeftKeyCode = rotateLeftKeyCode;
	m_rotateRightKeyCode = rotateRightKeyCode;
	m_shieldKeyCode = shieldKeyCode;
}

int PlayerInputComponent::AccelerateKeyCode() const
{
	return m_accelerateKeyCode;
}

int PlayerInputComponent::ShootKeyCode() const
{
	return m_shootKeyCode;
}

int PlayerInputComponent::RotateLeftKeyCode() const
{
	return m_rotateLeftKeyCode;
}

int PlayerInputComponent::RotateRightKeyCode() const
{
	return m_rotateRightKeyCode;
}

int PlayerInputComponent::ShieldKeyCode() const
{
	return m_shieldKeyCode;
}

bool PlayerInputComponent::AccelerateAction() const
{
	return App::IsKeyPressed(m_accelerateKeyCode);
}

bool PlayerInputComponent::ShootAction() const
{
	return App::IsKeyPressed(m_shootKeyCode);
}

bool PlayerInputComponent::RotateLeftAction() const
{
	return App::IsKeyPressed(m_rotateLeftKeyCode);
}

bool PlayerInputComponent::RotateRightAction() const
{
	return App::IsKeyPressed(m_rotateRightKeyCode);
}

bool PlayerInputComponent::ActivateShieldAction() const
{
	return App::IsKeyPressed(m_shieldKeyCode);
}
