#ifndef GAMESTATETRANSITION_H
#define GAMESTATETRANSITION_H

#include "ARCGL\IGameState.h"
#include "ARCGL_Classes.h"

class GameStateTransition : public IGameState
{
public:

	GameStateTransition(Application *pApp);
	virtual ~GameStateTransition();

	virtual void Update(float dt);
	virtual void Draw();

protected:

	IGameState *m_fromState;
	IGameState *m_toState;

	RenderTexture *m_fromStateTexture;
	RenderTexture *m_toStateTexture;

	float m_alpha;

private:
};


#endif


