#include "VictoryState.h"
#include <fstream>
#include <string>
#include <sstream>
const std::string VictoryState::s_victoryID = "VICTORY";
bool VictoryState::OnEnter() {
    printf("victory  on enter\n");

    std::ifstream file;
    file.open("assets\\scores.txt");
    std::string line;
    if (file.is_open()) {
        //diem
        int n;
        if (std::getline(file, line)) {
            n = std::stoi(line);
        }
        int times = Engine::GetInstance()->getTime() / 1000;
        //thoi gian
        int minutes = 0, seconds = 0;
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            char ch;
            iss >> minutes >> ch >> seconds;
        }
        if (minutes > times / 60) {
            minutes = times / 60;
            seconds = times % 60;
        }
        if (minutes == times / 60) {
            if (seconds > times % 60) {
                seconds = times % 60;
            }
        }
        
        file.close();
        if (n < Engine::GetInstance()->getScores()) n = Engine::GetInstance()->getScores();
        std::ofstream file;
        file.open("assets\\scores.txt");
        file << n;
        file << "\n";
        std::string new_time = std::to_string(minutes) + ":" + std::to_string(seconds);
        file << new_time;
        file.close();
    }
    TextureManager::GetInstance()->Load("victory_background", "assets\\victory_background.png");
    SoundManager::GetInstance()->Load("victory_music", "assets\\victory_music.mp3", SOUND_MUSIC);
    SoundManager::GetInstance()->PlayMusic("victory_music",-1);


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
    Mix_HaltMusic();
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
    TextureManager::GetInstance()->Draw("victory_background", 0, 0, 1280, 720);
    for (MenuButton* button : buttons) {
        button->Draw();
    }
}

void VictoryState::Update(float dt) {
    for (MenuButton* button : buttons) {
        button->Update(dt);
    }
}

