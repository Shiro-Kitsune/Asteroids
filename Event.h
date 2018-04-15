#pragma once

enum class EventType { GameEvent, UIEvent };
enum class GameEventType { PlayerDied, SmallestAsteroidDestroyed, ShipSpawned, ShipDestroyed, EnemyDestroyed, PlayerHealthChanged, 
	PlayerShieldStatusChanged, MineralCollected, ShootActionRequested, CreateShield };

class Event
{
public:
	virtual ~Event() {}
	virtual EventType GetEventType() const final;
	virtual void MarkAsRead() final;
	virtual bool IsRead() const final;
protected:
	Event(EventType type);
protected:
	bool m_read;
private:
	EventType m_type;
};


class GameEvent : public Event
{
public:
	GameEvent(GameEventType type, unsigned int entityId);
	GameEventType GetGameEventType() const;
	unsigned int GetEntityId();
private:
	GameEventType m_type;
	unsigned int m_entityId;
};


class UIEvent : public Event
{
public:
	UIEvent(const std::string& buttonName);
	const std::string& GetButtonName();
private:
	std::string m_buttonName;
};