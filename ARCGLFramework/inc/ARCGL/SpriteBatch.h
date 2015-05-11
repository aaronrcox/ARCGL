// Author: Aaron
// Description: Sprite Batch interface class and Factory

// Usage:
/*-----------------------------------------------------------------------------

	// creating a sprite batch instance
	SpriteBatch *sb = SpriteBatch::Factory::Create( pGameInstance, SpriteBatch::IMIDIATE );

		sb->Begin(); // begin rendering 

		sb->DrawSprite(pTexture, xPos, yPos);
		sb->DrawSprite(pTexture, xPos, yPos, width, height);

		sb->SetRenderColor(1.0f, 0.0f, 0.0f, 1.0f); 
		sb->DrawSprite(pTexture, xPos, yPos); 
		sb->DrawSprite(pTexture, xPos, yPos); // these sprite should be drawn with the color set above ( red )

		// overloaded SetRenderColor function
		sb->SetRenderColor(0xFF7F00FF); 


		sb->End();	// end rendering

	SpriteBatch::Destroy( sb );

-----------------------------------------------------------------------------*/

#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

class Application;
class Texture;
class RenderTexture;
class Font;


class SpriteBatch
{
public:

	class Factory
	{
	public:
		static SpriteBatch * Create(Application *pApp);
		static void Destroy(SpriteBatch *pSpriteBatch);
	};

	virtual void Begin()								= 0;
	virtual void End()									= 0;

	virtual void DrawSprite( Texture *texture, float xPos, float yPos, float width = 0.0f, float height = 0.0f, float rotation = 0.0f, float xOrigin = 0.5f, float yOrigin = 0.5f) = 0;
	virtual void DrawString( Font *pFont, const char *string, float xPos, float yPos) = 0;
	virtual void DrawLine( float x1, float y1, float x2, float y2 ) = 0;

	void SetRenderColor(unsigned int col);
	void SetRenderColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void SetUVRect(float uvX, float uvY, float uvW, float uvH);
	void SetLineThickness(float thickness);

protected:

	SpriteBatch(Application *pApp);
	virtual ~SpriteBatch();

	// represents red, green, blue, alpha in the range of 0 - 255
	union
	{
		struct{	unsigned char m_r, m_g, m_b, m_a; };
		unsigned int m_color;
	};

	// represents UV rectangle x, y, widht, height in the range of 0.0f to 1.0f
	float m_uvX, m_uvY, m_uvW, m_uvH; 

	float m_lineThickness;

	Texture *m_nullTexture;

	Application *m_pApplication;

private:
};

#endif