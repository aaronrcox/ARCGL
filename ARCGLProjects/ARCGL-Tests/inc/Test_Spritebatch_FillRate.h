#ifndef TEST_SPRITEBATCH_FILLRATE_H
#define TEST_SPRITEBATCH_FILLRATE_H

#include "ARCGL\IGameState.h"
#include "ARCGL_Classes.h"

#include <vector>

class Test_SpriteBatch_FillRate : public IGameState
{
public:

	Test_SpriteBatch_FillRate(Application *pApp);
	virtual ~Test_SpriteBatch_FillRate();

	virtual void Update(float dt);
	virtual void Draw();

protected:

	Texture *m_texture0;
	Texture *m_texture1;
	Texture *m_texture2;

	Font *m_font;
	int m_numSprites;

	struct Point
	{
		Point(float X, float Y) : x(X), y(Y){}
		float x, y;
	};


	std::vector<Point> m_sprites;

private:
};

#endif