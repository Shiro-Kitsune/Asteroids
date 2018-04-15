#pragma once

#include "Renderer.h"

class GameState
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;
	virtual void HandleEvents(GameEngine & game) = 0;
	virtual void Update(GameEngine& game, float deltaTime) = 0;
	virtual void Render() final;

	virtual EventManager& GetEventManager() final;
	virtual EntityManager& GetEntityManager() final;
	virtual EntityFactory& GetEntityFactory() final;
protected:
	GameState() { }
protected:
	EntityManager m_entityManager;
	EventManager m_eventManager;
	Renderer m_renderingSystem;
	EntityFactory m_entityFactory;
};