#include "Test_Spritebatch.h"
#include "ARCGL.h"

#include <stdio.h>

Test_SpriteBatch::Test_SpriteBatch(Application *pApp) : IGameState(pApp)
{
	m_texture0 = new Texture("./Assets/Images/box0_256.png");
	m_texture1 = new Texture("./Assets/Images/box1_256.png");
	m_texture2 = new Texture("./Assets/Images/box2_256.png");
	m_font = new Font("./Assets/Fonts/consolas_16px.fnt");
	m_rotation = 0.0f;
}

Test_SpriteBatch::~Test_SpriteBatch()
{
	delete m_font;
	delete m_texture2;
	delete m_texture1;
	delete m_texture0;
}

void Test_SpriteBatch::Update(float dt)
{
	m_rotation += dt;
}

void Test_SpriteBatch::Draw()
{
	SpriteBatch *sb = GetApplication()->GetSpriteBatch();
	unsigned int windowWidth = GetApplication()->GetViewWidth();
	unsigned int windowHeight = GetApplication()->GetViewHeight();

	float left	= 64;
	float right	= windowWidth - 64;
	float top		= 64;
	float bottom	= windowHeight - 64;
	float hCenter = windowWidth / 2;
	float vCenter = windowHeight / 2;

	sb->Begin();

	// drawing sprites, specifying rotation and origin changes
	sb->DrawSprite(m_texture0, left,		top, 64, 64, m_rotation, 0.0f,		0.0f);
	sb->DrawSprite(m_texture0, hCenter,		top, 64, 64, m_rotation, 0.5f,		0.0f);
	sb->DrawSprite(m_texture0, right,		top, 64, 64, m_rotation, 1.0f,		0.0f);

	sb->DrawSprite(m_texture1, left,		vCenter, 64, 64, m_rotation, 0.0f,	0.5f);
	sb->DrawSprite(m_texture1, hCenter,		vCenter, 64, 64, m_rotation, 0.5f,	0.5f);
	sb->DrawSprite(m_texture1, right,		vCenter, 64, 64, m_rotation, 1.0f,	0.5f);

	sb->DrawSprite(m_texture2, left,		bottom, 64, 64, m_rotation, 0.0f,	1.0f);
	sb->DrawSprite(m_texture2, hCenter,		bottom, 64, 64, m_rotation, 0.5f,	1.0f);
	sb->DrawSprite(m_texture2, right,				bottom, 64, 64, m_rotation, 1.0f,	1.0f); // test rendering null texture

	// draw some lines
	sb->DrawLine(left, top, right, top);
	sb->DrawLine(left, top, left, bottom);
	sb->DrawLine(left, bottom, right, bottom);
	sb->DrawLine(right, top, right, bottom);
	sb->DrawLine(hCenter, top, hCenter, bottom);
	sb->DrawLine(left, vCenter, right, vCenter);

	// draw some text
	char fps[32];
	sprintf(fps, "SpriteBatch Test\n%i", GetApplication()->GetFPS());

	sb->DrawString(m_font, fps, 10, 10);


	sb->End();
}