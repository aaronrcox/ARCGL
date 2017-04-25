#ifndef TEST_01_SPRITEBATCH_H
#define TEST_01_SPRITEBATCH_H

#include "ARCGL\IGameState.h"
#include "ARCGL_Classes.h"

class Game1;

class Test_SpriteBatch : public TIGameState<Game1>
{
public:

	Test_SpriteBatch(Game1 *pApp);
	virtual ~Test_SpriteBatch();

	virtual void Update(float dt);
	virtual void Draw();

protected:

	Texture *m_texture0;
	Texture *m_texture1;
	Texture *m_texture2;

	Font *m_font;

	float m_rotation;


private:
};

#endif