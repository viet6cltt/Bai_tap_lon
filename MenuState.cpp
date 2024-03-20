#include "MenuState.h"


bool MenuState::OnEnter() {
    printf("menu on enter\n");

    TextureManager::GetInstance()->Load("menu_background", "assets\\darkest.png");

    TextureManager::GetInstance()->Load("menu_play", "assets\\Menu Buttons\\Large Buttons\\Large Buttons\\Play Button.png");
    TextureManager::GetInstance()->Load("menu_play_hover", "assets\\Menu Buttons\\Large Buttons\\Colored Large Buttons\\Play col_Button.png");

    TextureManager::GetInstance()->Load("menu_quit", "assets\\Menu Buttons\\Large Buttons\\Large Buttons\\Exit Button.png");
    TextureManager::GetInstance()->Load("menu_quit_hover", "assets\\Menu Buttons\\Large Buttons\\Colored Large Buttons\\Exit  col_Button.png");

    buttons.push_back(new MenuButton(new Properties("menu_play", 100, 400, 300, 100), s_menuToPlay));
    buttons.push_back(new MenuButton(new Properties("menu_quit", 1280 - (100 + 300), 400, 300, 100), s_exitFromMenu));
    return true;
}

bool MenuState::OnExit() {
    printf("menu on exit\n");
    TextureManager::GetInstance()->Drop("menu_background");
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i]->Clean();
    }
    buttons.clear();

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
    // Cập nhật trạng thái của tất cả các nút
    for (MenuButton* button : buttons) {
        button->Update(dt);
    }
}

