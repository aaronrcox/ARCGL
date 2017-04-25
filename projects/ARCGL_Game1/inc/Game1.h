#pragma once

#include "ARCGL\Application.h"
#include "ARCGL_Classes.h"


class Game1 : public Application
{
public:

	Game1(unsigned int windowWidth, unsigned int windowHeight, const char *windowTitle);
	virtual ~Game1();

	virtual void Update(float deltaTime);
	virtual void Render();

	GameStateManager *GetGameStateManager();
	SpriteBatch *GetSpriteBatch();

protected:

	Texture *m_background;
	GameStateManager *m_gameStateManager;
	SpriteBatch *m_spriteBatch;

private:
};