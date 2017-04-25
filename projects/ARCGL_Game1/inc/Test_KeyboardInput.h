#ifndef TEST_KEYBOARDINPUT_H
#define TEST_KEYBOARDINPUT_H

#include "ARCGL\IGameState.h"
#include "ARCGL_Classes.h"

#include <string>

class Game1;

class Test_KeyboardInput : public TIGameState<Game1>
{
public:

	Test_KeyboardInput(Game1 *pApp);
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