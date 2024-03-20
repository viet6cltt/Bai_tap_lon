#include "PauseState.h"
#include "MenuState.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain() 
{
	printf("pause to menu\n");
	Engine::GetInstance()->getStateMachine()->changeState(new MenuState());
}

void PauseState::s_resumePlay() 
{
	printf("resume play\n");
	Engine::GetInstance()->getStateMachine()->popState();//quay lai trang thai truoc do
}

void PauseState::Update(float dt)
{
	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->Update(dt);
	}
}

void PauseState::Render() 
{
	TextureManager::GetInstance()->Draw("pause_background", 0, 0, 1280, 640);
	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->Draw();
	}
}

bool PauseState::OnEnter() 
{

	TextureManager::GetInstance()->Load("pause_background", "assets\\pause_background.png");

	TextureManager::GetInstance()->Load("menu_resume", "assets\\Menu Buttons\\Large Buttons\\Large Buttons\\Resume Button.png");
	TextureManager::GetInstance()->Load("menu_resume_hover", "assets\\Menu Buttons\\Large Buttons\\Colored Large Buttons\\Resume  col_Button.png");

	TextureManager::GetInstance()->Load("menu_menu", "assets\\Menu Buttons\\Large Buttons\\Large Buttons\\Menu Button.png");
	TextureManager::GetInstance()->Load("menu_menu_hover", "assets\\Menu Buttons\\Large Buttons\\Colored Large Buttons\\Menu  col_Button.png");

	m_buttons.push_back(new MenuButton(new Properties("menu_resume", 200, 400, 300, 100), s_resumePlay));
	m_buttons.push_back(new MenuButton(new Properties("menu_menu", 1280 - (200 + 300), 400, 300, 100), s_pauseToMain));
	return true;
}

bool PauseState::OnExit() 
{
	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->Clean();
	}
	TextureManager::GetInstance()->Drop("pause_background");
	m_buttons.clear();
	//TextureManager::GetInstance()->clearFromTextureMap("menu_resume");
	//TextureManager::GetInstance()->clearFromTextureMap("menu_menu");
	return true;
}