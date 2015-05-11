#include "ARCGL\SpriteBatch_Immediate.h"

#include "GL\glew.h"
#include "SDL\SDL_opengl.h"


#include "ARCGL\Application.h"
#include "ARCGL\Font.h"
#include "ARCGL\Texture.h"


#include <math.h>
#include <cstring>

// helper function defined below
// defined static in global scope so that its only accessable to this file
static void RotateAround(float inX, float inY, float rotation, float &outX, float &outY);


SpriteBatch_Immediate::SpriteBatch_Immediate(Application *pApp) : SpriteBatch(pApp)
{

}

SpriteBatch_Immediate::~SpriteBatch_Immediate()
{

}

void SpriteBatch_Immediate::Begin()
{
	//RenderTexture *renderTexture = m_pApplication->GetRenderTarget();

	unsigned int viewWidth	= m_pApplication->GetWindowWidth();		//( renderTexture != nullptr ) ? renderTexture->GetWidth()	: m_pApplication->GetWindowWidth();
	unsigned int viewHeight = m_pApplication->GetWindowHeight();	// ( renderTexture != nullptr ) ? renderTexture->GetHeight()	: m_pApplication->GetWindowHeight();


	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	glOrtho(0.0f, viewWidth, viewHeight, 0.0f, -1.0f, 1.0f);

	glPushAttrib(GL_VIEWPORT_BIT);
	glViewport(0, 0, viewWidth, viewHeight);	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);		

	glEnable(GL_TEXTURE_2D); 

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	SetRenderColor(0xFFFFFFFF);

}

void SpriteBatch_Immediate::End()
{
	unsigned int viewWidth	= m_pApplication->GetWindowWidth();
	unsigned int viewHeight = m_pApplication->GetWindowHeight();

	// resetup the projection and view
	glMatrixMode(GL_PROJECTION); 
	glPopMatrix();

	glPopAttrib();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}

void SpriteBatch_Immediate::DrawSprite( Texture *texture, float xPos, float yPos, float width, float height, float rotation, float xOrigin, float yOrigin )
{
	if( width  == 0.0f )	width  = texture->GetWidth();
	if( height == 0.0f )	height = texture->GetHeight();

	float tlX = (0.0f - xOrigin) * width;		float tlY = (0.0f - yOrigin) * height;
	float trX = (1.0f - xOrigin) * width;		float trY = (0.0f - yOrigin) * height;
	float brX = (1.0f - xOrigin) * width;		float brY = (1.0f - yOrigin) * height;
	float blX = (0.0f - xOrigin) * width;		float blY = (1.0f - yOrigin) * height;

	if( rotation != 0.0f )
	{
		RotateAround(tlX, tlY, rotation, tlX, tlY);
		RotateAround(trX, trY, rotation, trX, trY);
		RotateAround(brX, brY, rotation, brX, brY);
		RotateAround(blX, blY, rotation, blX, blY);
	}

	glBindTexture( GL_TEXTURE_2D, texture->GetTextureHandle() );
	glColor4f(m_r/255.0f, m_g/255.0f, m_b/255.0f, m_a/255.0f);


	glBegin(GL_QUADS);
	
		glTexCoord2f(m_uvX,			m_uvY + m_uvH);			glVertex2f(xPos + tlX,	yPos + tlY);
		glTexCoord2f(m_uvX + m_uvW, m_uvY + m_uvH);			glVertex2f(xPos + trX,	yPos + trY);
		glTexCoord2f(m_uvX + m_uvW, m_uvY);					glVertex2f(xPos + brX,	yPos + brY);
		glTexCoord2f(m_uvX,			m_uvY);					glVertex2f(xPos + blX,	yPos + blY);
	
	glEnd();

}

void SpriteBatch_Immediate::DrawString( Font *pFont, const char *string, float xPos, float yPos)
{
	int len = strlen(string);
	float lineHeight = pFont->GetLineHeight();

	float X = xPos;
	float Y = yPos;

	for(int i=0; i<len; ++i)
	{
		if( string[i] == '\n' )
		{
			X = xPos;
			Y += lineHeight;
		}

		const Font::CharInfo *charInfo = pFont->GetCharInfo(string[i]);

		float x = X + charInfo->xOffset;
		float y = Y + charInfo->yOffset;
		float w = charInfo->width;
		float h = charInfo->height;

		Font::Rect uvRect = pFont->GetCharacterTexCoord(charInfo);

		glBindTexture( GL_TEXTURE_2D, pFont->GetFontBitmap()->GetTextureHandle() );
		glColor4f(m_r/255.0f, m_g/255.0f, m_b/255.0f, m_a/255.0f);

		glBegin(GL_QUADS);
	
			glTexCoord2f(uvRect.x,				uvRect.y + uvRect.h);	glVertex2f(x,		y);
			glTexCoord2f(uvRect.x + uvRect.w,	uvRect.y + uvRect.h);	glVertex2f(x + w,	y);
			glTexCoord2f(uvRect.x + uvRect.w,	uvRect.y);				glVertex2f(x + w,	y + h);
			glTexCoord2f(uvRect.x,				uvRect.y);				glVertex2f(x,		y + h);
	
		glEnd();

		X += charInfo->xAdvance;
	}
}

void SpriteBatch_Immediate::DrawLine( float x1, float y1, float x2, float y2 )
{
	glDisable(GL_TEXTURE_2D);
	glColor4f(m_r/255.0f, m_g/255.0f, m_b/255.0f, m_a/255.0f);
	glBegin(GL_LINES);
	
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	
	glEnd();
	glEnable(GL_TEXTURE_2D);
}

// this function returns a new position that has been rotated around the origion.
void RotateAround(float inX, float inY, float rotation, float &outX, float &outY)
{
    outX = inX * cosf(rotation) - inY * sinf(rotation);
    outY = inX * sinf(rotation) + inY * cosf(rotation);
}