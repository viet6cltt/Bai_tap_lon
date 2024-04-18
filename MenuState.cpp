#include "MenuState.h"
#include "GuideState.h"

void MenuState::s_menuToGuide() {
    Engine::GetInstance()->getStateMachine()->changeState(new GuideState());
}

bool MenuState::OnEnter() {
    time = 0;
    printf("menu on enter\n");

    SoundManager::GetInstance()->Load("menu_music", "assets\\menu_music.mp3", SOUND_MUSIC, 64);
    SoundManager::GetInstance()->PlayMusic("menu_music", -1);

    TextureManager::GetInstance()->Load("menu_background", "assets\\darkest.png");

    TextureManager::GetInstance()->Load("menu_play", "assets\\Menu Buttons\\Large Buttons\\Large Buttons\\Play Button.png");
    TextureManager::GetInstance()->Load("menu_play_hover", "assets\\Menu Buttons\\Large Buttons\\Colored Large Buttons\\Play col_Button.png");

    TextureManager::GetInstance()->Load("menu_control", "assets\\Menu Buttons\\Large Buttons\\Large Buttons\\Controls Button.png");
    TextureManager::GetInstance()->Load("menu_control_hover", "assets\\Menu Buttons\\Large Buttons\\Colored Large Buttons\\Controls  col_Button.png");

    TextureManager::GetInstance()->Load("menu_quit", "assets\\Menu Buttons\\Large Buttons\\Large Buttons\\Exit Button.png");
    TextureManager::GetInstance()->Load("menu_quit_hover", "assets\\Menu Buttons\\Large Buttons\\Colored Large Buttons\\Exit  col_Button.png");

    buttons.push_back(new MenuButton(new Properties("menu_play", 500, 250, 300, 100), s_menuToPlay));
    buttons.push_back(new MenuButton(new Properties("menu_control", 500, 400, 300, 100), s_menuToGuide));
    buttons.push_back(new MenuButton(new Properties("menu_quit", 880, 400, 300, 100), s_exitFromMenu));
    return true;
}

bool MenuState::OnExit() {
    printf("menu on exit\n");
    TextureManager::GetInstance()->Drop("menu_background");
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i]->Clean();
    }
    buttons.clear();
    Mix_HaltMusic();

    //TextureManager::GetInstance()->clearFromTextureMap("menu_play");
    //TextureManager::GetInstance()->clearFromTextureMap("menu_quit");
    //TextureManager::GetInstance()->clearFromTextureMap("menu_background");
    return true;
}

void MenuState::Render() {
    // Vẽ tất cả các nút
    TextureManager::GetInstance()->Draw("menu_background", 0, 0, 1280, 640);
    for (MenuButton* button : buttons) {
        button->Draw();
    }
}

void MenuState::Update(float dt) {
    time++;
    // Cập nhật trạng thái của tất cả các nút
    for (MenuButton* button : buttons) {
        button->Update(dt);
    }
}

