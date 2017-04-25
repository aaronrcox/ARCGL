/*-----------------------------------------------------------------------------
Author:			Aaron Cox
Description:	Basic Game State manager
				Handles a stack of game states
Usage:

An instance of the GameStateManager will need to be provided to any object
that needs to minipulate game state. Recomended usage: provide a getter from
the application class.

	// Sample Game State
	//===================================================
	class MenuState : public IGameState {
	public:
		MenuState(GameStateManager *gsm) : IGameState(), m_gsm(gsm) {}
		virtual ~MenuState() {}

		virtual void Update(float deltaTime)
		{ 
			m_gsm->PopState(); // removes the top state from the stack
		
		}
		virtual void Draw() { Insert Draw Logic }

	private:
		GameStateManager *m_gsm;
		Insert any state specific member variables here.
		 - textures, objects, all thoes sort of things.
	};

Given an instance, here's a rundown of usage:

	// Setup
	//===================================================
		GameStateManager *gsm = new GameStateManager();

		gsm->SetState("MenuState", new MenuState(gsm)); // where MenuState is of type IGameState

		// Note: the constructors could be setup to receive an instance of the game state manager
		// allowing them to change state

		gm->PushState("MenuState"); // the menuState will be updated / rendered when the gameSate is rendered
	

	// Update Loop
	//===================================================

		gm->UpdateGameStates(deltaTime); // all states "pushed" will be updated

	// Draw Loop
	//===================================================

		gm->DrawGameStates(); // all states "pushed" will be rendered


-----------------------------------------------------------------------------*/

#pragma once

#include <map>
#include <vector>

#include "IGameState.h"

class GameStateManager
{
public:

	//constructor
	GameStateManager();

	//destructor
	virtual ~GameStateManager();

	// should be called only once each frame during the update phase of the game loop
	// will process any pending state actions before updating the game states.
	void UpdateGameStates(float dt);

	// should be called only once each frame during the render phase of the game loop
	void DrawGameStates();

	// Register a state name with the game state manager
	// if the "name" already exists, the old state will be destroyed
	// an assert will be thrown if the state is on the stack (debug only)
	// This action is executed at beginning of the next GameStateManager update
	void SetState(const char *name,  IGameState *pState);

	// Gets a gamestate by name, and pushes it onto the gamestate stack (becomes topmost)
	// this action will be executed at the beginning of the next GameStateManager update.
	// an assert will be thrown if the state is already on the stack (debug only)
	void PushState(const char *name);

	// Pushes the given state onto the gamestate stack (becomes topmost)
	// this action will be executed at the beginning of the next GameStateManager update.
	// an assert will be thrown if the state is already on the stack (debug only)
	void PushState(IGameState *pState);
	
	// Removes the topmost state from the stack
	// If no states exist, no action is taken
	void PopState();

	// Gets the gamestate by name and removes it from the stack
	// this allows states which are not topmost to be no longer part if the stack
	void RemoveState(const char *name);

	// Removes the given state from the stack
	// this allows states which are not topmost to be no longer part if the stack
	void RemoveState(IGameState *pState);

	// Returns the number of states that are currently on the stack
	// including update and draw blocked states.
	unsigned int GetActiveStackSize();

	// Get a state at a given index on the stack.
	// bottom most state is index:0
	// null returned if index is out of bounds
	IGameState *GetStateFromStack(int index);

	// GetGameStateByName returns the IGameState associated with the given name.
	// See SetState which is used to "rgister" states with a name.
	IGameState *GetStateByName(const char *name);

	// finds the given state and returns true if it is currently on the stack
	// will return false if the state does not exist, or is not on the stack
	bool IsStateOnStack(const char *name);
	bool IsStateOnStack(IGameState *state);

protected:

	// this method should be called only once at the beginning of the Update method
	// will process each of the stored commands - PUSH, POP, SET
	// and clear the pending commands.
	void ProcessCommands();

protected:

	//contains all of the available game states that have been
	//registered with the game state manager by name
	std::map<const char *, IGameState *> m_availableStates;

	//list of game states that are being updated and drawn
	std::vector< IGameState* > m_gameStateStack;

	// commands used to minipulate the game state stack
	enum ECommands
	{
		E_PUSH_BY_NAME,
		E_PUSH_BY_PTR,
		E_POP,
		E_REMOVE_BY_NAME,
		E_REMOVE_BY_PTR,
		E_SET
	};

	// arguments that are stored for each command
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

