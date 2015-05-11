#ifndef IGAMESTATE_H
#define IGAMESTATE_H

class Application;

class IGameState
{
public:

	IGameState(Application * pApp)		{ m_updateBlocking = false; m_drawBlocking = false; m_pApp = pApp;	}

	virtual ~IGameState()				{/* intentionally left blank */}

	virtual void Update(float dt)		{/* intentionally left blank */}
	virtual void Draw()					{/* intentionally left blank */}

	Application *GetApplication()					{ return m_pApp;	}

	void SetUpdateBlocking(bool blocking)	{ m_updateBlocking = blocking;	}
	void SetDrawBlocking(bool blocking)		{ m_drawBlocking = blocking;	}

	bool IsUpdateBlocking() { return m_updateBlocking; }
	bool IsDrawBlocking() { return m_drawBlocking; }

protected:

	bool m_updateBlocking;
	bool m_drawBlocking;

	Application *m_pApp;

private:
};

#endif