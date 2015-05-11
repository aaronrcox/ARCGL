#include "Test_MouseInput.h"
#include "ARCGL.h"

#include <stdio.h>

Test_MouseInput::Test_MouseInput(Application *pApp) : IGameState(pApp)
{
	
	m_font = new Font("./Assets/Fonts/consolas_16px.fnt");

}

Test_MouseInput::~Test_MouseInput()
{
	delete m_font;
}

void Test_MouseInput::Update(float dt)
{

	Input *input = Input::GetSingleton();

	m_mouseX = input->GetMouseX();
	m_mouseY = input->GetMouseY();

	m_leftPressed = input->IsMouseButtonDown(1);
	m_middlePressed = input->IsMouseButtonDown(2);
	m_rightPressed = input->IsMouseButtonDown(3);
}

void Test_MouseInput::Draw()
{
	SpriteBatch *sb = GetApplication()->GetSpriteBatch();

	sb->Begin();

		// draw some text
		char text[256];
		sprintf(text,	"Mouse Input\n"\
						"FPS: %i\n"\
						"XPos: %i\n"\
						"YPos: %i\n"\
						"Left: %i\n"\
						"Middle: %i\n"\
						"Right: %i", GetApplication()->GetFPS(), m_mouseX, m_mouseY, m_leftPressed, m_middlePressed, m_rightPressed);


		sb->DrawString(m_font, text, 10, 10);

	sb->End();
}