#include "Game1.h"
#include "ARCGL.h"

#include <iostream>

#include "TestSelectorState.h"

Game1::Game1(unsigned int windowWidth, unsigned int windowHeight) : Application(windowWidth, windowHeight)
{	
	m_background	= new Texture("./Assets/Images/Background1.png");

	GetGameStateManager()->SetState("TEST_SELECTOR", new TestSelectorState(this) );
	GetGameStateManager()->PushState("TEST_SELECTOR");
}

Game1::~Game1()
{
	delete m_background;

	GetGameStateManager()->SetState("TEST_SELECTOR", NULL);
}

void Game1::Update(float deltaTime)
{
	if( Input::GetSingleton()->WasKeyPressed(SDLK_ESCAPE) )
		GetGameStateManager()->PopState();

	GetGameStateManager()->UpdateGameStates(deltaTime);
}

void Game1::Draw()
{
	ClearScreen();

	SpriteBatch *sb = GetSpriteBatch();
	sb->Begin();
	sb->DrawSprite(m_background, 0, 0, GetViewWidth(), GetViewHeight(), 0, 0, 0);
	sb->End();
	
	GetGameStateManager()->DrawGameStates();
}