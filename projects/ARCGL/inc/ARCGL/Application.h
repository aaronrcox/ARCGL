#pragma once

class Application
{
public:

	Application(int windowWidth, int windowHeight, const char *windowTitle);
	virtual ~Application();

	void Run();

	void GameLoop();


	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	void Quit();

	unsigned int GetWindowWidth() const;
	unsigned int GetWindowHeight() const;

	unsigned int GetFps() const;


	void ClearScreen(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);



private:

	// helper function to update the FPS
	void UpdateFPS(float deltaTime);

	// helper function to update the delta time variables
	void UpdateDeltaTime();

private:

	unsigned int m_windowWidth;
	unsigned int m_windowHeight;

	bool m_quitApplication;

	// application running time variables
	float m_runningTime;
	float m_lastFrameRunningTime;
	float m_deltaTime;

	// fps calculation
	unsigned int m_fps;
	unsigned int m_fpsCount;
	float m_fpsIntervial;

private:
};