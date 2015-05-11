
/*-----------------------------------------------------------------------------
Author:			Aaron Cox
Description:	Implements Immidiate mode rendering for old graphics cards.
				See SpriteBatch.h for usage!
				
-----------------------------------------------------------------------------*/

#include "ARCGL\SpriteBatch.h"

class SpriteBatch_Immediate : public SpriteBatch
{
public:

	// befriend the SpriteBatch factory so that it is the only one that can create an instance of us.
	friend class SpriteBatch::Factory;

	virtual void Begin();
	virtual void End();

	virtual void DrawSprite( Texture *texture, float xPos, float yPos, float width, float height, float rotation, float xOrigin, float yOrigin);
	virtual void DrawString( Font *pFont, const char *string, float xPos, float yPos);
	virtual void DrawLine( float x1, float y1, float x2, float y2 );

protected:

	// constructors / destructors are protected
	// only the factory functions should be able to create a SpriteBatch object
	SpriteBatch_Immediate(Application *pApp);
	virtual ~SpriteBatch_Immediate();


private:
};