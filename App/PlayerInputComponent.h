#pragma once

class PlayerInputComponent : public Component
{
public:
	PlayerInputComponent(int accelerateKeyCode, int shootKeyCode, int shieldKeyCode, int rotateLeftKeyCode, int rotateRightKeyCode);
	int AccelerateKeyCode() const;
	int ShootKeyCode() const;
	int ShieldKeyCode() const;
	int RotateLeftKeyCode() const;
	int RotateRightKeyCode() const;

private:
	int m_accelerateKeyCode; 
	int m_shootKeyCode;
	int m_shieldKeyCode;
	int m_rotateLeftKeyCode;
	int m_rotateRightKeyCode;
};