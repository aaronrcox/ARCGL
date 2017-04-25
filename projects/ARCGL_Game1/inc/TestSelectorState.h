#ifndef TESTSELECTORSTATE_H
#define TESTSELECTORSTATE_H

#include "ARCGL_Classes.h"
#include "ARCGL\IGameState.h"

#include <vector>
#include <string>

class Game1;

class TestSelectorState : public TIGameState<Game1>
{
public:

	TestSelectorState(Game1 *pApp);
	virtual ~TestSelectorState();

	virtual void Update(float dt);
	virtual void Draw();

protected:

	Font *m_font;

	Texture *m_background;
	Texture *m_logo;

	int m_mouseOverTestID;
	float m_menuXPos;
	float m_menuYPos;
	float m_menuWidth;
	float m_menuHeight;

	std::vector<std::string> m_tests;
	std::vector<IGameState *> m_testStates;

};

#endif