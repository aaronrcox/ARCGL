
// Author: Aaron
// Description: Basic Keyboard and Mouse Management

// the following functions are provided:
/*-----------------------------------------------------------------------------

	IsKeyDown		( key );
	IsKeyUp			( key );
	WasKeyPressed	( key);
	WasKeyReleased	( key);

	GetPressedKeys( );			// returns a list of pressed physical keys

	GetPressedCharacters( );	// returns a list of unicode printable characters (modifier keys are supported)
								// eg if the GLFW_KEY_A button on the keyboard was pressed whilst capslock or shift was on,
								// the list would contain the 'A' character otherwise 'a' character

	IsMouseButtonDown( mouseButton )
	IsMouseButtonUp( mouseButton )

	WasMouseButtonPressed( mouseButton )
	WasMouseButtonReleased( mouseButton )


	// key:			refers to a unique key identifier    eg: SDLK_SPACE or SDLK_ESCAPE etc
	// mouseButton:	refers to a unique button identifier eg: GLFW_MOUSE_BUTTON_LEFT or GLFW_MOUSE_BUTTON_RIGHT

-----------------------------------------------------------------------------*/

#ifndef INPUT_H
#define INPUT_H


#include <vector>
#include <map>

class Input
{
public:

	// just giving the Application class access to the Input singleton!
	friend class Application;

	static Input *GetSingleton()			{ return ms_singleton;					}



	bool IsKeyDown(int keyID);
	bool IsKeyUp(int keyID);
	bool WasKeyPressed(int keyID);
	bool WasKeyReleased(int keyID);

	const std::vector<int> &GetPressedKeys( );
	const std::vector<unsigned int> &GetPressedCharacters( );

	bool IsMouseButtonDown( int mbID );
	bool IsMouseButtonUp( int mbID );
	bool WasMouseButtonPressed( int mbID );
	bool WasMouseButtonReleased( int mbID );

	int GetMouseX();
	int GetMouseY() ;
	void GetMouseXY(int *x, int *y);

	enum EKeyStatus
	{
		E_JUST_RELEASED,
		E_UP,
		E_JUST_PRESSED,
		E_DOWN,		
	};

protected:

	// singleton stuff
	static Input * ms_singleton;

	static void CreateSingleton()			{ ms_singleton = new Input();			}
	static void DestroySingleton()			{ delete ms_singleton;					}

	Input();
	~Input();
	

	// should be called once by the application each frame
	// just before SDL_PollEvents updates the new state of the keyboard
	void Update();

private:

	std::vector<int>			m_keysToUpdate;
	std::map<int, int>			m_keyStatus;

	std::vector<int>			m_pressedKeys;
	std::vector<unsigned int>	m_pressedCharacters;

	std::vector<int>			m_mouseToUpdate;
	std::map<int, int>			m_mouseState;

	int m_mouseX;
	int m_mouseY;

protected:

	// These methods are called by glfw function pointers
	// GLFWkeyFun and GLFWcharFun - see constructor for setup
	// The function pointers are called during the GLFWPollEvents function
	// which is called at the end of the game loop after SwapBuffers
	// effectivelly at the beginning of each frame.
	//-------------------------------------------------------------
	void OnKeyPressed( int keyID );
	void OnKeyReleased( int keyID );
	void OnKeyRepeate(int key);
	void OnCharInput(unsigned int character);

	void OnMouseMove(int newXPos, int newYPos);
	void OnMousePressed(int mbID);
	void OnMouseReleased(int mbID);
	//-------------------------------------------------------------

private:






	
};

#endif