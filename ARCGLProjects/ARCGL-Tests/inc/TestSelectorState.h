#ifndef TESTSELECTORSTATE_H
#define TESTSELECTORSTATE_H

#include "ARCGL_Classes.h"
#include "ARCGL\IGameState.h"

#include <vector>
#include <string>

class Game1;

class TestSelectorState : public IGameState
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
	int m_menuXPos;
	int m_menuYPos;
	int m_menuWidth;
	int m_menuHeight;

	std::vector<std::string> m_tests;
	std::vector<IGameState *> m_testStates;

};

#endif