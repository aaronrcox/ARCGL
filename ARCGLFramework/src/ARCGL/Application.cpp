#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include "ARCGL\Application.h"
#include "ARCGL\Audio.h"
#include "ARCGL\Input.h"
#include "ARCGL\RenderTexture.h"
#include "ARCGL\SpriteBatch.h"
#include "ARCGL\GameStateManager.h"

#include "GL\glew.h"
#include "SDL\SDL.h"
#include "SDL\SDL_opengl.h"

#include <stdio.h>
#include <string.h>

#include <functional>

#include <iostream>

#include "ARCGL\Texture.h"

Application::Application(unsigned int width, unsigned int height)
{
	// initialising member variables
	m_windowWidth			= width;
	m_windowHeight			= height;

	m_gameOver				= false;

	m_fps					= 0;
	m_fpsCount				= 0;
	m_fpsIntervial			= 0.0f;

	m_runningTime			= 0;
	m_lastFrameRunningTime	= 0;
	m_deltaTime				= 0.0f;

	m_renderTexture			= nullptr;


	// setup SDL and Create an OpenGL window.
	if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0 )
	{
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
	}

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,	1	);
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,		32	);
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE,		8	);
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,		8	);
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,		8	);
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE,		8	);

	unsigned int flags = SDL_OPENGL | SDL_HWSURFACE | SDL_DOUBLEBUF;

	SDL_SetVideoMode( m_windowWidth, m_windowHeight, 32, flags );

	// enable unicode characters so we can retrive the unicode value of keypresses from SDL
	SDL_EnableUNICODE(1);

	// enable basic keyboard repeate functionality.
	SDL_EnableKeyRepeat(0, 0);

	// initialise GL Extensions...
	glewInit();

	SetRenderTexture(NULL);

	// Set some Default OpenGL settings
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_DEPTH_TEST);

	// initialise our input class
	Input::CreateSingleton();
	Audio::CreateSingleton();

	m_spritebatch = SpriteBatch::Factory::Create(this);

	m_gameStateManager = new GameStateManager();
	
}

Application::~Application()
{
	delete m_gameStateManager;

	SpriteBatch::Factory::Destroy(m_spritebatch);

	Input::DestroySingleton();
	Audio::DeleteSingleton();
	SDL_Quit();
}

static struct HACK
{
	static void Loop()
	{
		pApp->GameLoop();
	}
	static Application *pApp;
};
Application *HACK::pApp = 0;

void Application::Run()
{
	HACK::pApp = this;

	#ifdef __EMSCRIPTEN__
		 emscripten_set_main_loop(HACK::Loop, 0, 1);
	#else
		while (!m_gameOver)
		{
			HACK::Loop();
		}
	#endif 
}

void Application::GameLoop()
{
	m_lastFrameRunningTime		= m_runningTime;
	m_runningTime				= SDL_GetTicks() / 1000.0f;
	m_deltaTime					= m_runningTime - m_lastFrameRunningTime;
	
	//std::cout << m_fps << std::endl;

	// calculate fps
	UpdateFPS(m_deltaTime);

	Input::GetSingleton()->Update();

	SDL_Event e;
	while( SDL_PollEvent( &e ) )
	{
		if( e.type == SDL_QUIT )
		{
			m_gameOver = true;
		}
		else if( e.type == SDL_KEYDOWN )
		{
			if( e.key.keysym.unicode >= 32 && e.key.keysym.unicode < 127 )
				Input::GetSingleton()->OnCharInput(e.key.keysym.unicode);

			Input::GetSingleton()->OnKeyPressed( e.key.keysym.sym );
		}
		else if( e.type == SDL_KEYUP )
		{
			Input::GetSingleton()->OnKeyReleased( e.key.keysym.sym );
		}
		else if( e.type == SDL_MOUSEMOTION )
		{
			Input::GetSingleton()->OnMouseMove(e.motion.x, e.motion.y);
		}
		else if( e.type == SDL_MOUSEBUTTONDOWN )
		{
			Input::GetSingleton()->OnMousePressed(e.button.button);
		}
		else if( e.type == SDL_MOUSEBUTTONUP )
		{
			Input::GetSingleton()->OnMouseReleased(e.button.button);
		}
	}


	Update(m_deltaTime);
	Draw();

	SDL_GL_SwapBuffers();
}


void Application::UpdateFPS(float dt)
{
	m_fpsIntervial += m_deltaTime;
	m_fpsCount++;

	if( m_fpsIntervial > 0.5f ) // update the fps every half second
	{
		m_fps			= m_fpsCount * 2; // multiply by 2 because we are updateing every half second
		m_fpsCount		= 0;
		m_fpsIntervial	= 0;
	}
}

void Application::ClearScreen(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

unsigned int Application::GetViewWidth()
{
	return (m_renderTexture)?m_renderTexture->GetWidth() : m_windowWidth;
}
unsigned int Application::GetViewHeight()
{
	return (m_renderTexture)?m_renderTexture->GetHeight() : m_windowHeight;
}

void Application::SetRenderTexture( RenderTexture *renderTexture )
{
	m_renderTexture = renderTexture;
	if( m_renderTexture != nullptr )
	{
		glBindFramebuffer( GL_FRAMEBUFFER, m_renderTexture->GetFrameBufferHandle() );
	}
	else
	{
		glBindFramebuffer( GL_FRAMEBUFFER, 0);
	}

	glViewport( 0,0,GetViewWidth(),GetViewHeight() );
}

void Application::PushRenderTexture(RenderTexture *renderTexture)
{
	if( renderTexture == nullptr )
		return;

	m_renderTextures.push_back(renderTexture);
	SetRenderTexture(renderTexture);
}
void Application::PopRenderTexture()
{
	if( m_renderTextures.size() <= 0 )
		return;
	
	m_renderTextures.pop_back();

	if( m_renderTextures.size() <= 0 )
		SetRenderTexture(nullptr);
	else
		SetRenderTexture(m_renderTextures.back());
}