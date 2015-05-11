#ifndef TEST_KEYBOARDINPUT_H
#define TEST_KEYBOARDINPUT_H

#include "ARCGL\IGameState.h"
#include "ARCGL_Classes.h"

#include <string>

class Test_KeyboardInput : public IGameState
{
public:

	Test_KeyboardInput(Application *pApp);
	virtual ~Test_KeyboardInput();

	virtual void Update(float dt);
	virtual void Draw();

protected:

	Font *m_font;
	Font *m_font1;

	std::string m_typedCharacters;

private:
};

#endif