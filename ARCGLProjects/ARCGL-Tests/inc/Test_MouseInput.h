#ifndef TEST_MOUSEINPUT_H
#define TEST_MOUSEINPUT_H

#include "ARCGL\IGameState.h"
#include "ARCGL_Classes.h"

#include <string>

class Test_MouseInput : public IGameState
{
public:

	Test_MouseInput(Application *pApp);
	virtual ~Test_MouseInput();

	virtual void Update(float dt);
	virtual void Draw();

protected:

	Font *m_font;

	int m_mouseX;
	int m_mouseY;

	bool m_leftPressed;
	bool m_middlePressed;
	bool m_rightPressed;
	bool m_scrollValue;

private:
};

#endif