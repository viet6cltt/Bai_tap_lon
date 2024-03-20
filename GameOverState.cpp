#include "GameOverState.h"

const std::string GameOverState::s_gameoverID = "GAMEOVER";
bool GameOverState::OnEnter() {
    printf("gameover on enter\n");

    TextureManager::GetInstance()->Load("gameover_background", "assets\\GAME OVER.png");

    TextureManager::GetInstance()->Load("menu_quit", "assets\\Menu Buttons\\Large Buttons\\Large Buttons\\Exit Button.png");
    TextureManager::GetInstance()->Load("menu_quit_hover", "assets\\Menu Buttons\\Large Buttons\\Colored Large Buttons\\Exit  col_Button.png");

    TextureManager::GetInstance()->Load("menu_menu", "assets\\Menu Buttons\\Large Buttons\\Large Buttons\\Menu Button.png");
    TextureManager::GetInstance()->Load("menu_menu_hover", "assets\\Menu Buttons\\Large Buttons\\Colored Large Buttons\\Menu  col_Button.png");

    buttons.push_back(new MenuButton(new Properties("menu_menu", 100, 200, 300, 100), s_toMenu));
    buttons.push_back(new MenuButton(new Properties("menu_quit", 1280 - (100 + 300), 200, 300, 100), s_exitFromGameOver));
    return true;
}

bool GameOverState::OnExit() {
    printf("gameover on exit\n");
    TextureManager::GetInstance()->Drop("gameover_background");
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i]->Clean();
    }
    buttons.clear();

    //TextureManager::GetInstance()->clearFromTextureMap("menu_play");
    //TextureManager::GetInstance()->clearFromTextureMap("menu_quit");
    //TextureManager::GetInstance()->clearFromTextureMap("menu_background");
    return true;
}

void GameOverState::Render() {
    // Vẽ tất cả các nút
    TextureManager::GetInstance()->Draw("gameover_background", 0, 0, 1280, 640);
    for (MenuButton* button : buttons) {
        button->Draw();
    }
}

void GameOverState::Update(float dt) {
    // Cập nhật trạng thái của tất cả các nút
    for (MenuButton* button : buttons) {
        button->Update(dt);
    }
}

