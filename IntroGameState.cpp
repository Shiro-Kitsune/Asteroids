#include "stdafx.h"

IntroGameState IntroGameState::m_introGameState;

void IntroGameState::Init()
{
	CreateUI();
}

void IntroGameState::Cleanup()
{
	m_entityManager.RemoveAllEntities();
}

void IntroGameState::HandleEvents(GameEngine & game)
{
	if (App::IsKeyPressed(VK_RETURN))
	{
		game.ChangeState(SinglePlayerGameState::Instance());
	}
}

void IntroGameState::Update(GameEngine& game, float deltaTime)
{
}

void IntroGameState::CreateUI()
{
	Color color(0.8f, 0.8f, 0.8f);
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(APP_VIRTUAL_WIDTH / 2 - 30.0f, APP_VIRTUAL_HEIGHT - 100), "CONTROLS", Color(0.0f, 0.8f, 0.8f)));
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(100, APP_VIRTUAL_HEIGHT - 200), "Up arrow = acceleration", color));
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(100, APP_VIRTUAL_HEIGHT - 250), "Right and left arrows = turn right or left", color));
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(700, APP_VIRTUAL_HEIGHT - 200), "Space = shoot", color));
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(700, APP_VIRTUAL_HEIGHT - 250), "Shift = generate shield", color));
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(412, APP_VIRTUAL_HEIGHT - 400), "Press Enter to start a game", Color(0.855f, 0.647f, 0.125f)));
}