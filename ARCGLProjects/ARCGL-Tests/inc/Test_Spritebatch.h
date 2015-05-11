#ifndef TEST_01_SPRITEBATCH_H
#define TEST_01_SPRITEBATCH_H

#include "ARCGL\IGameState.h"
#include "ARCGL_Classes.h"

class Test_SpriteBatch : public IGameState
{
public:

	Test_SpriteBatch(Application *pApp);
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