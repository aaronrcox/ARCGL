#include "ARCGL\SpriteBatch.h"

#include "ARCGL\SpriteBatch_GL3.h"


#include "ARCGL\Application.h"
#include "ARCGL\Texture.h"

#include <assert.h>

SpriteBatch *SpriteBatch::Factory::Create(Application *pApp)
{
	return new SpriteBatch_GL3(pApp);
}

void SpriteBatch::Factory::Destroy(SpriteBatch *pSpriteBatch)
{
	delete pSpriteBatch;
}

SpriteBatch::SpriteBatch(Application *pApp)
{
	m_pApplication = pApp;
	SetRenderColor(255, 255, 255, 255);
	SetUVRect(0.0f, 0.0f, 1.0f, 1.0f);

	unsigned int pixels[1] = { 0xFFFFFFFF };
	m_nullTexture = new Texture(1, 1, pixels);
}
SpriteBatch::~SpriteBatch()
{

}

void SpriteBatch::SetRenderColor(unsigned int col)
{
	m_r = ((col & 0xFF000000) >> 24);
	m_g = ((col & 0x00FF0000) >> 16);
	m_b = ((col & 0x0000FF00) >> 8);
	m_a = ((col & 0x000000FF) >> 0);
}

void SpriteBatch::SetRenderColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_r = r;
	m_b = b;
	m_g = g;
	m_a = a;
}

void SpriteBatch::SetUVRect(float uvX, float uvY, float uvW, float uvH)
{
	m_uvX = uvX;
	m_uvY = uvY;
	m_uvW = uvW;
	m_uvH = uvH;
}
