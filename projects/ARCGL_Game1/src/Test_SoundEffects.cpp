//#include "Test_SoundEffects.h"
//#include "ARCGL.h"
//
//#include <stdio.h>
//
//Test_SoundEffects::Test_SoundEffects(Application *pApp) : IGameState(pApp)
//{
//	m_backgroundMusic = Audio::GetInstance()->LoadSound("./Audio/barn-beat.ogg", "BACKGROUND");
//	m_font = new Font("./Assets/Fonts/consolas_16px.fnt");
//}
//
//Test_SoundEffects::~Test_SoundEffects()
//{
//	delete m_font;
//}
//
//void Test_SoundEffects::Update(float dt)
//{
//	if(Input::GetSingleton()->WasKeyPressed(' ') )
//		m_backgroundMusic->Play();
//}
//
//void Test_SoundEffects::Draw()
//{
//	SpriteBatch *sb = GetApplication()->GetSpriteBatch();
//	
//}