#include "GuideState.h"
#include "MenuState.h"

const std::string GuideState::s_guideID = "GUIDE";

void GuideState::s_guidetoMain()
{
	printf("guide to menu\n");
	Engine::GetInstance()->getStateMachine()->changeState(new MenuState());
}

void GuideState::Update(float dt)
{

	for (int i = 0; i < m_buttons.size(); i++) {
		if (m_buttons.size() > 1000) return;
		m_buttons[i]->Update(dt);
	}
}

void GuideState::Render()
{
	TextureManager::GetInstance()->Draw("guide_background", 0, 0, 1280, 640);
	TextureManager::GetInstance()->Draw("guide", 256, 40, 768, 560);
	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->Draw();
	}
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 255, 0, 255);
}

bool GuideState::OnEnter()
{
	is_Out = false;
	TextureManager::GetInstance()->Load("guide", "assets\\guide.png");
	TextureManager::GetInstance()->Load("guide_exit", "assets\\x_button.png");
	TextureManager::GetInstance()->Load("guide_exit_hover", "assets\\x_button_hover.png");
	TextureManager::GetInstance()->Load("guide_background", "assets\\guide_background.png");
	m_buttons.push_back(new MenuButton(new Properties("guide_exit", 968, 45, 50, 50), s_guidetoMain));

	SoundManager::GetInstance()->Load("pausestate_music", "assets\\pausestate_music.mp3", SOUND_MUSIC, 128);
	SoundManager::GetInstance()->PlayMusic("pausestate_music", -1);
	return true;
}

bool GuideState::OnExit()
{
	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->Clean();
	}
	TextureManager::GetInstance()->Drop("pause_background");
	return true;
}