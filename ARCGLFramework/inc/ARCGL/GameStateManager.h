/*-----------------------------------------------------------------------------
		Author:			Shane Coates
		Description:	Basic Game State manager
						Handles a stack of game states
-----------------------------------------------------------------------------*/

#ifndef GAMESTATEMANAGER_H
#define	GAMESTATEMANAGER_H

#include <map>
#include <vector>

#include "ARCGL\IGameState.h"

class GameStateManager
{
public:

	//constructor
	GameStateManager();

	//destructor
	virtual ~GameStateManager();

	//should be called each frame by the "Game" class
	void UpdateGameStates(float dt);
	void DrawGameStates();

	// Register a state name with the game state manager
	// if the "name" already exists, the old state will be destroyed
	// on the next update.
	void SetState(const char *name,  IGameState *pState);

	void PushState(const char *name);
	void PushState(IGameState *pState);
	void PopState();
	void RemoveState(const char *name);
	void RemoveState(IGameState *pState);

	unsigned int GetActiveStackSize() { return m_gameStateStack.size(); }

	IGameState *GetStateFromStack(int index);
	IGameState *GetStateByName(const char *name);

protected:

	void ProcessCommands();

protected:

	//contains all of the available game states that have been
	//registered with the game state manager
	std::map<const char *, IGameState *> m_availableStates;

	//list of game states that are being updated and drawn
	std::vector< IGameState* > m_gameStateStack;

	
	enum ECommands
	{
		E_PUSH_BY_NAME,
		E_PUSH_BY_PTR,
		E_POP,
		E_REMOVE_BY_NAME,
		E_REMOVE_BY_PTR,
		E_SET
	};


	struct SCommand
	{
		const char *name;
		ECommands cmd;
		IGameState *pState;
	};


	// After Update and Draw has been called for the frame,
	// all commands are processed in order.
	std::vector< SCommand > m_commands;



private:
};



#endif