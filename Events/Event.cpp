#include "stdafx.h"

Event::Event(EventType type) : m_type(type), m_read(false)
{
}

EventType Event::GetEventType() const
{
	return m_type;
}

void Event::MarkAsRead()
{
	m_read = true;
}

bool Event::IsRead() const
{
	return m_read;
}


GameEvent::GameEvent(GameEventType type, unsigned int entityId) : Event(EventType::GameEvent), m_type(type)
{
	m_entityId = entityId;
}

GameEventType GameEvent::GetGameEventType() const
{
	return m_type;
}

unsigned int GameEvent::GetEntityId()
{
	m_read = true;
	return m_entityId;
}


UIEvent::UIEvent(const std::string& buttonName) : Event(EventType::UIEvent), m_buttonName(buttonName)
{
}

const std::string& UIEvent::GetButtonName()
{
	m_read = true;
	return m_buttonName;
}
