#pragma once

enum class ItemType;

class EntityFactory
{
public:
	EntityFactory();
	Entity CreatePlayer(int accelerateKeyCode, int shootKeyCode, int rotateLeftKeyCode, int rotateRightKeyCode, int shieldKeyCode, const std::string& name);
	Entity CreateAsteroid();
	Entity CreateAsteroid(const Vector2D & position);
	Entity CreateAsteroid(const Vector2D & position, int size, const Vector2D & velocity);
	Entity CreateShip(const Vector2D & position);
	Entity CreateRamShip(const Vector2D & position);
	Entity CreateBoss(const Vector2D & position);
	Entity CreateBullet(const Vector2D & position, float angle, Entity* owner, bool playerOwner);
	Entity CreateItem(const Vector2D & position, ItemType type);
	Entity CreateExplosion(const Vector2D & position);
	Entity CreateShield(Entity* parent);
	Entity CreateUIText(const Vector2D & position, const std::string& text, const Color & color, const std::string& name);
	Entity CreateUIText(const Vector2D & position, const std::string& text, const Color & color);
	Entity CreateUIButton(const Vector2D & position, float width, float height, const std::string& text, const Color & color, const Color & hoverColor, const std::string& name);
	void ResetIdCounter();
private:
	unsigned int GenerateId();
private:
	unsigned int m_nextId;
};