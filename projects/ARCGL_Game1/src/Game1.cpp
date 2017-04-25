#include "Game1.h"
#include "ARCGL.h"

#include "TestSelectorState.h"


Game1::Game1(unsigned int windowWidth, unsigned int windowHeight, const char *windowTitle) : 
	Application(windowWidth, windowHeight, windowTitle)
{
	m_spriteBatch = SpriteBatch::Factory::Create((Application *)this);
	m_gameStateManager = new GameStateManager();

	m_background = new Texture("./Assets/Images/Background1.png");

	m_gameStateManager->SetState("TEST_SELECTOR", new TestSelectorState(this));
	m_gameStateManager->PushState("TEST_SELECTOR");

}

Game1::~Game1()
{
	delete m_gameStateManager;

	SpriteBatch::Factory::Destroy(m_spriteBatch);
}

void Game1::Update(float deltaTime)
{
	if (Input::Get()->WasKeyPressed(SDLK_ESCAPE))
		m_gameStateManager->PopState();

	m_gameStateManager->UpdateGameStates(deltaTime);
}

void Game1::Render()
{
	ClearScreen();

	m_spriteBatch->Begin();
	m_spriteBatch->DrawSprite(m_background, 0, 0, (float)GetWindowWidth(), (float)GetWindowHeight(), 0, 0, 0);
	m_spriteBatch->End();

	m_gameStateManager->DrawGameStates();
}

SpriteBatch *Game1::GetSpriteBatch()
{
	return m_spriteBatch;
}

GameStateManager *Game1::GetGameStateManager()
{
	return m_gameStateManager;
}