#include "PlayerInputComponent.h"

PlayerInputComponent::PlayerInputComponent(int accelerateKeyCode, int shootKeyCode, int shieldKeyCode, int rotateLeftKeyCode, int rotateRightKeyCode)
{
	m_accelerateKeyCode = accelerateKeyCode;
	m_shootKeyCode = shootKeyCode;
	m_shieldKeyCode = shieldKeyCode;
	m_rotateLeftKeyCode = rotateLeftKeyCode;
	m_rotateRightKeyCode = rotateRightKeyCode;
}

int PlayerInputComponent::AccelerateKeyCode() const
{
	return m_accelerateKeyCode;
}

int PlayerInputComponent::ShootKeyCode() const
{
	return m_shootKeyCode;
}

int PlayerInputComponent::ShieldKeyCode() const
{
	return m_shieldKeyCode;
}

int PlayerInputComponent::RotateLeftKeyCode() const
{
	return m_rotateLeftKeyCode;
}

int PlayerInputComponent::RotateRightKeyCode() const
{
	return m_rotateRightKeyCode;
}