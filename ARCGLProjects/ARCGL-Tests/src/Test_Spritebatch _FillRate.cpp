#include "Test_SpriteBatch_FillRate.h"
#include "ARCGL.h"
#include <math.h>

#include <stdlib.h>
#include <stdio.h>

Test_SpriteBatch_FillRate::Test_SpriteBatch_FillRate(Application *pApp) : IGameState(pApp)
{
	m_texture0 = new Texture("./Assets/Images/box0_256.png");
	m_texture1 = new Texture("./Assets/Images/box1_256.png");
	m_texture2 = new Texture("./Assets/Images/box2_256.png");
	m_font = new Font("./Assets/Fonts/consolas_16px.fnt");

	m_numSprites = 0;

}

Test_SpriteBatch_FillRate::~Test_SpriteBatch_FillRate()
{
	delete m_font;
	delete m_texture2;
	delete m_texture1;
	delete m_texture0;
}

void Test_SpriteBatch_FillRate::Update(float dt)
{
	int w = GetApplication()->GetViewWidth();
	int h = GetApplication()->GetViewHeight();

	m_sprites.push_back( Point( rand() % w, rand() % h ) );
	m_numSprites += 1;
}

void Test_SpriteBatch_FillRate::Draw()
{
	SpriteBatch *sb = GetApplication()->GetSpriteBatch();


	sb->Begin();

	for(int i=0; i<m_numSprites; i++)
	{
		Texture *tex;

		if( i % 3 == 0 ) tex = m_texture0;
		else if( i % 3 == 1 ) tex = m_texture1;
		else tex = m_texture2;

		sb->DrawSprite(tex, m_sprites[i].x,  m_sprites[i].y, 32, 32 );
	}

	sb->End();


	sb->Begin();

	// draw some text
	char fps[64];
	sprintf(fps, "SpriteBatch Test - Fill Rate\nFPS: %i\nNum Quads:%i", GetApplication()->GetFPS(), m_numSprites);

	sb->DrawString(m_font, fps, 10, 10);

	sb->End();
}