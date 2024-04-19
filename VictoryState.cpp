#include "VictoryState.h"
#include <fstream>
const std::string VictoryState::s_victoryID = "VICTORY";
bool VictoryState::OnEnter() {
    printf("victory  on enter\n");

    std::ifstream file;
    file.open("assets\\scores.txt");
    if (file.is_open()) {
        int n;
        file >> n;
        file.close();
        if (n < Engine::GetInstance()->getScores()) {
            std::ofstream file;
            file.open("assets\\scores.txt", std::ios::out);
            if (file.is_open()) {

                file << Engine::GetInstance()->getScores();
                file.close();
            }
        }
    }
    TextureManager::GetInstance()->Load("victory_background", "assets\\victory_background.jpg");

    TextureManager::GetInstance()->Load("menu_quit", "assets\\Menu Buttons\\Large Buttons\\Large Buttons\\Exit Button.png");
    TextureManager::GetInstance()->Load("menu_quit_hover", "assets\\Menu Buttons\\Large Buttons\\Colored Large Buttons\\Exit  col_Button.png");

    TextureManager::GetInstance()->Load("menu_menu", "assets\\Menu Buttons\\Large Buttons\\Large Buttons\\Menu Button.png");
    TextureManager::GetInstance()->Load("menu_menu_hover", "assets\\Menu Buttons\\Large Buttons\\Colored Large Buttons\\Menu  col_Button.png");

    buttons.push_back(new MenuButton(new Properties("menu_menu", 100, 200, 300, 100), s_toMenu));
    buttons.push_back(new MenuButton(new Properties("menu_quit", 1280 - (100 + 300), 200, 300, 100), s_exitFromVictory));
    return true;
}

bool VictoryState::OnExit() {
    printf("victory on exit\n");
    TextureManager::GetInstance()->Drop("victory_background");
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i]->Clean();
    }
    buttons.clear();

    //TextureManager::GetInstance()->clearFromTextureMap("menu_play");
    //TextureManager::GetInstance()->clearFromTextureMap("menu_quit");
    //TextureManager::GetInstance()->clearFromTextureMap("menu_background");
    return true;
}

void VictoryState::Render() {
    // Vẽ tất cả các nút
    TextureManager::GetInstance()->Draw("victory_background", 0, 0, 1280, 720);
    for (MenuButton* button : buttons) {
        button->Draw();
    }
}

void VictoryState::Update(float dt) {
    // Cập nhật trạng thái của tất cả các nút
    for (MenuButton* button : buttons) {
        button->Update(dt);
    }
}

