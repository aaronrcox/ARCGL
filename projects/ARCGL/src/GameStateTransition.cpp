//#include "ARCGL\GameStateTransition.h"
//#include "ARCGL.h"
//
//GameStateTransition::GameStateTransition(Application *pApp) : IGameState(pApp)
//{
//	m_fromStateTexture = new RenderTexture(pApp->GetWindowWidth(), pApp->GetWindowHeight());
//	m_toStateTexture = new RenderTexture(pApp->GetWindowWidth(), pApp->GetWindowHeight());
//
//	m_fromState = GetApplication()->GetGameStateManager()->GetStateFromStack(-2);
//	m_toState	= GetApplication()->GetGameStateManager()->GetStateFromStack(-1);
//
//	SetUpdateBlocking(true);
//	SetDrawBlocking(true);
//
//	m_alpha = 1.0f;
//}
//GameStateTransition::~GameStateTransition()
//{
//	delete m_fromStateTexture;
//	delete m_toStateTexture;
//}
//
//void GameStateTransition::Update(float dt)
//{
//	m_alpha -= dt;
//	if( m_alpha <= 0 )
//	{
//		GetApplication()->GetGameStateManager()->PopState();
//		GetApplication()->GetGameStateManager()->RemoveState(m_fromState);
//	}
//}
//void GameStateTransition::Draw()
//{
//	GetApplication()->PushRenderTexture(m_fromStateTexture);
//	GetApplication()->ClearScreen(0,0,0,0);
//	if( m_fromState != nullptr )
//		m_fromState->Draw();
//	GetApplication()->PopRenderTexture();
//
//	GetApplication()->PushRenderTexture(m_fromStateTexture);
//	GetApplication()->ClearScreen(0,0,0,0);
//	if( m_fromState != nullptr )
//		m_fromState->Draw();
//	GetApplication()->PopRenderTexture();
//
//	SpriteBatch *sb = GetApplication()->GetSpriteBatch();
//	
//	sb->Begin();
//
//	sb->SetRenderColor(255, 255, 255, 255 * m_alpha);
//	sb->DrawSprite(m_toStateTexture, 0, 0, 0, 0, 0, 0, 0);
//	
//	sb->SetRenderColor(255, 255, 255, 255 * (1.0f - m_alpha));
//	sb->DrawSprite(m_fromStateTexture, 0, 0, 0, 0, 0, 0, 0);
//
//	sb->End();
//
//}
