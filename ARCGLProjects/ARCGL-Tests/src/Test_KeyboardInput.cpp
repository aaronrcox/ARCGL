#include "Test_KeyboardInput.h"
#include "ARCGL.h"

#include <vector>
#include <stdio.h>

Test_KeyboardInput::Test_KeyboardInput(Application *pApp) : IGameState(pApp)
{
	
	m_font = new Font("./Assets/Fonts/consolas_16px.fnt");
	m_font1 = new Font("./Assets/Fonts/arial_20px.fnt");

	m_typedCharacters = "";

}

Test_KeyboardInput::~Test_KeyboardInput()
{
	delete m_font1;
	delete m_font;
}

void Test_KeyboardInput::Update(float dt)
{
	const std::vector<unsigned int> &pressedCharacters = Input::GetSingleton()->GetPressedCharacters();
	for(int i=0; i<pressedCharacters.size(); i++)
	{
		m_typedCharacters.push_back( pressedCharacters[i] );
	}

	if( Input::GetSingleton()->WasKeyPressed( ::SDLK_BACKSPACE ) )
		if( m_typedCharacters.size() > 0 )
			m_typedCharacters.pop_back();

	if( Input::GetSingleton()->WasKeyPressed( SDLK_RETURN ) )
		m_typedCharacters.push_back('\n');

}

void Test_KeyboardInput::Draw()
{
	SpriteBatch *sb = GetApplication()->GetSpriteBatch();

	sb->Begin();

		// draw some text
		char fps[32];
		sprintf(fps, "Keyboard Input\nFPS: %i", GetApplication()->GetFPS());
		sb->DrawString(m_font, fps, 10, 10);

		sb->DrawString(m_font1, "Type into the keyboard:", 10, 100);
		sb->DrawString(m_font1, m_typedCharacters.c_str(), 10, 125);

	sb->End();
}