/*-----------------------------------------------------------------------------
Author: Aaron Cox
Description:	Basic Game State for use with the GameStateManager class
				GameStates are a thin wrapper around an update and render loop,
				can be be easily added and removed from the GameStateManager,

Usage:
-------------------------------------------------------------------------------

See GameStateManager.h for example usage

-----------------------------------------------------------------------------*/

#pragma once

class Application;

class IGameState
{
public:

	IGameState() : m_updateBlocking(false), m_drawBlocking(false) { }

	virtual ~IGameState() {/* intentionally left blank */}


	// OnPush called by the GameStateManager when the PushState action is executed
	virtual void OnPush() { /* optionally overload this method */ }


	// OnPop called by the GameStateManager when the PopState action is executed
	virtual void OnPop() { /* optionally overload this method */ }


	// Update called by the GameStateManager every frame
	// unless a game state on the stack is blocking the update
	virtual void Update(float dt) {/* optionally overload this method */}


	// Render called by the game state manager every frame
	// unless a game state on the stack is blocking the update
	virtual void Draw()	{/* optionally overload this method */}


	// When blocking is true, the gamestates below in the stack will not have the Update method called.
	// particurally usefull for pause screens.
	void SetUpdateBlocking(bool blocking)	{ m_updateBlocking = blocking;	}

	// When blocking is true, the gamestates below in the stack will not receive a draw
	void SetDrawBlocking(bool blocking)		{ m_drawBlocking = blocking;	}

	bool IsUpdateBlocking() { return m_updateBlocking; }
	bool IsDrawBlocking() { return m_drawBlocking; }

protected:

	bool m_updateBlocking;
	bool m_drawBlocking;

	

private:
};


template<typename T>
class TIGameState : public IGameState
{
public:

	TIGameState(T *pApp) : m_pApp(pApp), IGameState() { }
	virtual ~TIGameState() {}

	T *GetApplication() { return m_pApp; }

protected:

	T *m_pApp;
};
