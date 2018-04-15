#include "stdafx.h"

LoseState LoseState::m_loseState;

void LoseState::Init()
{
	m_entityFactory.ResetIdCounter();
	CreateUI();
}

void LoseState::Cleanup()
{
	m_entityManager.RemoveAllEntities();
}

void LoseState::HandleEvents(GameEngine & game)
{
	if (App::IsKeyPressed(VK_RETURN))
	{
		game.ChangeState(StartMenuState::Instance());
	}
}

void LoseState::Update(GameEngine & game, float deltaTime)
{
}

void LoseState::CreateUI()
{
	Color color(0.863f, 0.078f, 0.235f);
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(APP_VIRTUAL_WIDTH / 2 - 260, APP_VIRTUAL_HEIGHT / 2 + 155), "GAME OVER", color));
	m_entityManager.AddEntity(m_entityFactory.CreateUIText(Vector2D(APP_VIRTUAL_WIDTH / 2 - 180, APP_VIRTUAL_HEIGHT / 2 + 65), "Press Enter to return to Start menu", Color(1.0f, 1.0f, 1.0f)));
}
