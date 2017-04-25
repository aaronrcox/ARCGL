#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <iostream>

#include "ARCGL\Application.h"
#include "ARCGL\Input.h"

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

Application::Application(int windowWidth, int windowHeight, const char *windowTitle) : 
	m_windowWidth(windowWidth),
	m_windowHeight(windowHeight),
	m_quitApplication(false)
{
	// initialise SDL
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 0);
	
	// Build the game window
	SDL_SetVideoMode(m_windowWidth, m_windowHeight, 0, SDL_OPENGL | SDL_HWSURFACE | SDL_DOUBLEBUF);

	// enable unicode characters so we can retrive the unicode value of keypresses from SDL
	SDL_EnableUNICODE(1);

	// enable basic keyboard repeate functionality.
	SDL_EnableKeyRepeat(0, 0);

	// Initialise glew
	glewExperimental = GL_TRUE;
	GLenum glewInitResult = glewInit();

	Input::CreateSingleton();
}

Application::~Application()
{
	Input::DestroySingleton();
	SDL_Quit();
}

struct GameLoopFunc
{
	static void Loop() {
		pApp->GameLoop();
	}
	static Application *pApp;
};
Application * GameLoopFunc::pApp = NULL;


void Application::Run()
{
	#ifdef __EMSCRIPTEN__

		// The browser requires the main loop to be executed in a callback
		// this way infinite loops do not crash the browser
		GameLoopFunc::pApp = this;
		emscripten_set_main_loop(GameLoopFunc::Loop, 0, 1);

	#else

		// On windows, we control our own main loop
		// run until the m_quitApplication has been set to true
		while (!m_quitApplication)
			GameLoop();

	#endif

}

void Application::GameLoop()
{
	UpdateDeltaTime();
	UpdateFPS(m_deltaTime);

	Input::Get()->Update();

	// Process Events for the frame
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT:				Quit(); break;

			// The Below Input::Get()->OnXXX methods are protected but, they are exposed via friend class.
			//-----------------------------------
			case SDL_MOUSEMOTION:		Input::Get()->OnMouseMove(e.motion.x, e.motion.y);	break;
			case SDL_MOUSEBUTTONDOWN:	Input::Get()->OnMousePressed(e.button.button);		break;
			case SDL_MOUSEBUTTONUP:		Input::Get()->OnMouseReleased(e.button.button);		break;
			case SDL_KEYUP:				Input::Get()->OnKeyReleased(e.key.keysym.sym);		break;
			case SDL_KEYDOWN:
			{
				if (e.key.keysym.unicode >= 32 && e.key.keysym.unicode < 127)
					Input::Get()->OnCharInput(e.key.keysym.unicode);

				Input::Get()->OnKeyPressed(e.key.keysym.sym);

			}break;
			//-----------------------------------
		}
	}

	// Preform Application Update logic
	Update(m_deltaTime); 

	// Preform Application rendering logic
	Render();

	// end of frame, swap the opengl back bufer
	SDL_GL_SwapBuffers();
}

void Application::Quit()
{
	m_quitApplication = true;
}

void Application::UpdateFPS(float deltaTime)
{
	m_fpsIntervial += m_deltaTime;
	m_fpsCount++;

	if (m_fpsIntervial > 0.5f) // update the fps every half second
	{
		m_fps = m_fpsCount * 2; // multiply by 2 because we are updateing every half second
		m_fpsCount = 0;
		m_fpsIntervial = 0;
	}
}

void Application::UpdateDeltaTime()
{
	m_lastFrameRunningTime = m_runningTime;
	m_runningTime = SDL_GetTicks() / 1000.0f;
	m_deltaTime = m_runningTime - m_lastFrameRunningTime;
}

void Application::ClearScreen(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

unsigned int Application::GetWindowWidth() const
{
	return m_windowWidth;
}
unsigned int Application::GetWindowHeight() const
{
	return m_windowHeight;
}

unsigned int Application::GetFps() const
{
	return m_fps;
}