#include "GameOverState.h"
#include <fstream>
const std::string GameOverState::s_gameoverID = "GAMEOVER";
bool GameOverState::OnEnter() {
    printf("gameover on enter\n");

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

    SoundManager::GetInstance()->Load("gameover_music", "assets\\gameover_music.mp3", SOUND_MUSIC);
    SoundManager::GetInstance()->PlayMusic("gameover_music", -1);
    TextureManager::GetInstance()->Load("gameover_background", "assets\\gameoverstate_background.png");

    TextureManager::GetInstance()->Load("menu_quit", "assets\\Menu Buttons\\Large Buttons\\Large Buttons\\Exit Button.png");
    TextureManager::GetInstance()->Load("menu_quit_hover", "assets\\Menu Buttons\\Large Buttons\\Colored Large Buttons\\Exit  col_Button.png");

    TextureManager::GetInstance()->Load("menu_menu", "assets\\Menu Buttons\\Large Buttons\\Large Buttons\\Menu Button.png");
    TextureManager::GetInstance()->Load("menu_menu_hover", "assets\\Menu Buttons\\Large Buttons\\Colored Large Buttons\\Menu  col_Button.png");

    buttons.push_back(new MenuButton(new Properties("menu_menu", 70, 300, 300, 100), s_toMenu));
    buttons.push_back(new MenuButton(new Properties("menu_quit", 70, 450, 300, 100), s_exitFromGameOver));
    return true;
}

bool GameOverState::OnExit() {
    printf("gameover on exit\n");
    Mix_HaltMusic();
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
    TextureManager::GetInstance()->Draw("gameover_background", 0, 0, 1280, 720);
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

