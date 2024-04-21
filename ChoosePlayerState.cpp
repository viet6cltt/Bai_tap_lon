#include "ChoosePlayerState.h"
#include "PlayState.h"

void ChoosePlayerState::s_chooseplayerToPlay_1selected() {
	Engine::GetInstance()->setPlayerType(1);
	Engine::GetInstance()->getStateMachine()->changeState(new PlayState());
}

void ChoosePlayerState::s_chooseplayerToPlay_2selected() {
	Engine::GetInstance()->setPlayerType(2);
	Engine::GetInstance()->getStateMachine()->changeState(new PlayState());
}
bool ChoosePlayerState::OnEnter() {
	SoundManager::GetInstance()->Load("chooseplayer_music", "assets\\chooseplayer_music.mp3", SOUND_MUSIC);
	SoundManager::GetInstance()->PlayMusic("chooseplayer_music", -1);
	TextureManager::GetInstance()->Load("chooseplayer_background", "assets\\chooseplayerstate_background.png");
	TextureManager::GetInstance()->Load("player1_icon", "assets\\player1.png");
	TextureManager::GetInstance()->Load("player1_icon_hover", "assets\\selected_player1.png");
	TextureManager::GetInstance()->Load("player2_icon", "assets\\player2.png");
	TextureManager::GetInstance()->Load("player2_icon_hover", "assets\\selected_player2.png");
	FontManager::GetInstance()->LoadFont("player_Name", "assets\\ExpressionPro.ttf", 40);
	m_buttons.push_back(new MenuButton(new Properties("player1_icon", 100, 40, 452, 579), s_chooseplayerToPlay_1selected));
	m_buttons.push_back(new MenuButton(new Properties("player2_icon", 728, 40, 452, 579), s_chooseplayerToPlay_2selected));
	//Engine::GetInstance()->setName(Input::GetInstance()->GetTextInput());
	
	
	return true;
}

bool ChoosePlayerState::OnExit()
{
	
	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->Clean();
	}
	TextureManager::GetInstance()->Drop("chooseplayer_background");
	SDL_StopTextInput();
	return true;
}

void ChoosePlayerState::Render()
{
	
	TextureManager::GetInstance()->Draw("chooseplayer_background", 0, 0, 1280, 720);
	TextureManager::GetInstance()->Draw("player1_icon", 100, 40, 452, 579);
	TextureManager::GetInstance()->Draw("player2_icon", 728, 40, 452, 579);
	FontManager::GetInstance()->RenderText("player_Name", " CHOOSE YOUR CHARACTER", 400, 10, { 255,255,255,255 });
	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->Draw();
	}
}

void ChoosePlayerState::Update(float dt)
{
		for (int i = 0; i < m_buttons.size(); i++) {
			if (m_buttons.size() > 1000) return;
			m_buttons[i]->Update(dt);
		}
	

}
