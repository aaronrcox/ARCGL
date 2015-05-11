
/*-----------------------------------------------------------------------------
Author:			Aaron Cox
Description:	Quick and dirty demo showing off whats available in this
				little framework...

				Demonstrates Basic Rendering
				Getting Keyboard input
				Getting text input

-----------------------------------------------------------------------------*/
#ifndef GAME1_H
#define GAME1_H

#include "ARCGL\Application.h"
#include "ARCGL_Classes.h"
#include <vector>

class GameStateManager;

class BasicButton;


class Game1 : public Application
{
public:

	// assets loaded in constructor
	Game1(unsigned int windowWidth, unsigned int windowHeight);

	// assets destroyed in destructor
	virtual ~Game1();

	// update / draw called each frame automaticly
	virtual void Update(float deltaTime);
	virtual void Draw();

protected:

	Texture *m_background;

protected:
private:
};

#endif