#include "TestSelectorState.h"
#include "ARCGL.h"

#include "Test_Spritebatch.h"
#include "Test_Spritebatch_FillRate.h"
#include "Test_KeyboardInput.h"
#include "Test_MouseInput.h"
#include "Test_SoundEffects.h"

TestSelectorState::TestSelectorState(Game1 *pApp) : IGameState((Application *)pApp)
{
	m_font			= new Font("./Assets/Fonts/consolas_16px.fnt");
	m_logo			= new Texture("./Assets/Images/Logo.png");

	
	m_tests.push_back("SpriteBatch Rendering");
	m_tests.push_back("SpriteBatch Stress Test");
	m_tests.push_back("Keyboard Input");
	m_tests.push_back("Mouse Input");
	//m_tests.push_back("Sound Effects");


	m_mouseOverTestID = -1;

	m_menuXPos		= 25;
	m_menuYPos		= 100;
	m_menuHeight	= m_font->GetLineHeight() * 2;
	m_menuWidth		= 300;
}
TestSelectorState::~TestSelectorState()
{
	delete m_logo;
	delete m_font;
}

void TestSelectorState::Update(float dt)
{
	int mx = Input::GetSingleton()->GetMouseX();
	int my = Input::GetSingleton()->GetMouseY();

	if( mx > m_menuXPos && mx < m_menuXPos + m_menuWidth && my > m_menuYPos )
	{
		m_mouseOverTestID = (my + (m_menuHeight*0.25f) - m_menuYPos) / m_menuHeight;
		if( m_mouseOverTestID >= m_tests.size() )
			m_mouseOverTestID = -1;
	}
	else 
	{
		m_mouseOverTestID = -1;
	}

	if( Input::GetSingleton()->WasMouseButtonPressed(1) && m_mouseOverTestID != -1 )
	{
		GameStateManager *gm = GetApplication()->GetGameStateManager();

		IGameState * state = nullptr;

		if(		 m_tests[m_mouseOverTestID] == "SpriteBatch Rendering" )	{ state = new Test_SpriteBatch(GetApplication());			}
		else if( m_tests[m_mouseOverTestID] == "SpriteBatch Stress Test" )	{ state = new Test_SpriteBatch_FillRate(GetApplication());	}
		else if( m_tests[m_mouseOverTestID] == "Keyboard Input" )			{ state = new Test_KeyboardInput(GetApplication());			}
		else if( m_tests[m_mouseOverTestID] == "Mouse Input" )				{ state = new Test_MouseInput(GetApplication());			}
		//else if( m_tests[m_mouseOverTestID] == "Sound Effects" )			{ state = new Test_SoundEffects(GetApplication());			}

		gm->SetState(m_tests[m_mouseOverTestID].c_str(), state);
		state->SetDrawBlocking(true);
		state->SetUpdateBlocking(true);
		gm->PushState(state);
	}

}
void TestSelectorState::Draw()
{
	SpriteBatch *sb = GetApplication()->GetSpriteBatch();
	sb->Begin();

	for(int i=0; i<m_tests.size(); i++)
	{
		if( i == m_mouseOverTestID ) sb->SetRenderColor(0xfcbb7cff);
		else sb->SetRenderColor(0xffffffff);
		sb->DrawString(m_font, m_tests[i].c_str(), m_menuXPos + 25, m_menuYPos + (i * m_menuHeight) );
	}

	sb->SetRenderColor(0x0000003F);
	sb->DrawSprite(NULL, m_menuXPos, 0, m_menuWidth, GetApplication()->GetViewHeight(), 0, 0, 0);

	sb->SetRenderColor(0xed8a1fff);
	sb->DrawSprite(m_logo, m_menuXPos + 25 ,20, 0, 0, 0, 0, 0);

	sb->SetRenderColor(0xFFFFFFFF);

	sb->End();
}