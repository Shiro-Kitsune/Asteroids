#pragma once

class PlayerInputComponent : public Component
{
public:
	PlayerInputComponent(int accelerateKeyCode, int shootKeyCode, int rotateLeftKeyCode, int rotateRightKeyCode, int shieldKeyCode);
	int AccelerateKeyCode() const;
	int ShootKeyCode() const;
	int RotateLeftKeyCode() const;
	int RotateRightKeyCode() const;
	int ShieldKeyCode() const;
	bool AccelerateAction() const;
	bool ShootAction() const;
	bool RotateLeftAction() const;
	bool RotateRightAction() const;
	bool ActivateShieldAction() const;
private:
	int m_accelerateKeyCode;
	int m_shootKeyCode;
	int m_rotateLeftKeyCode;
	int m_rotateRightKeyCode;
	int m_shieldKeyCode;
};