/*-----------------------------------------------------------------------------
Author:			Aaron Cox

Description:	Abstract Application Class, Initialises Window, OpenGL and
				Manages the main game loop.

Usage:			Create a "myGame" class to inherit from Application
				overload the update and draw functions, and create an instance of
				of the "myGame" class within main()

				class Game1 : public Application
				{
				public:

					Game1( int width, int height ) : Application(width, height)
					{ // TODO: laod game assets }

					virtual ~Game1()		{ TODO: unload game assets		}
					virtual void Update()	{ TODO: insert drawing logic	}
					virtual void Draw()		{ TODO: insert drawing logic	}

				protected:
				private:
				};

				int main(int argc, char **argv)
				{
					Game1 *pGame = new Game1(640, 480);
					pGame->Run();
					delete pGame;
					return 0;
				}


-----------------------------------------------------------------------------*/


#ifndef APPLICATION_H
#define APPLICATION_H

#include "ARCGL\Input.h"

class SpriteBatch;
class RenderTexture;
class GameStateManager;

class Application
{
public:

	Application(unsigned int width, unsigned int height);
	virtual ~Application();

	// returns only when the game loop exits.
	// should only ever be called once
	void Run();
	void GameLoop();

	// abstract functions
	// must be implemented by derrived classes.
	// Update and Draw are both called once per frame in that order.
	virtual void Update(float deltaTime)	= 0;
	virtual void Draw()						= 0;

	unsigned int GetViewWidth();
	unsigned int GetViewHeight();
	
	unsigned int GetWindowWidth()				{ return m_windowWidth;			}
	unsigned int GetWindowHeight()				{ return m_windowHeight;		}

	float GetRunningTime()						{ return m_runningTime;			}
	float GetDeltaTime()						{ return m_deltaTime;			}

	unsigned int		GetFPS()				{ return m_fps;					}
	Input *				GetInput()				{ return Input::GetSingleton(); }
	SpriteBatch *		GetSpriteBatch()		{ return m_spritebatch;			}
	GameStateManager *	GetGameStateManager()	{ return m_gameStateManager;	}

	void ClearScreen(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

	
	void PushRenderTexture(RenderTexture *renderTexture);
	void PopRenderTexture();

protected:

private:

	// helper function to update the FPS
	void UpdateFPS(float dt);

	// helper function used when pushing / poping render textures
	void SetRenderTexture(RenderTexture *renderTexture);


private:

	// represents the window size
	unsigned int m_windowWidth;
	unsigned int m_windowHeight;

	// application running time variables
	float m_runningTime;
	float m_lastFrameRunningTime;
	float m_deltaTime;

	// fps calculation
	unsigned int m_fps, m_fpsCount;
	float m_fpsIntervial;

	// if set to false, the main game loop will exit
	bool m_gameOver;

	// stores a pointer to the current texture that is being rendered to.
	RenderTexture *m_renderTexture;
	std::vector<RenderTexture *> m_renderTextures;

	// spritebatch used for rendering
	SpriteBatch *m_spritebatch;

	GameStateManager *m_gameStateManager;

};

#endif