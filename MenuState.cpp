#include "MenuState.h"
#include "GuideState.h"
#include <string>
#include <fstream>
void MenuState::s_menuToGuide() {
    Engine::GetInstance()->getStateMachine()->changeState(new GuideState());
}

bool MenuState::OnEnter() {
    printf("menu on enter\n");

    FontManager::GetInstance()->LoadFont("highest_scores", "assets\\ExpressionPro.ttf", 40);
    FontManager::GetInstance()->LoadFont("current_highest_scores", "assets\\ExpressionPro.ttf", 40);
    FontManager::GetInstance()->LoadFont("best_time", "assets\\ExpressionPro.ttf", 40);
    FontManager::GetInstance()->LoadFont("current_best_time", "assets\\ExpressionPro.ttf", 40);
    std::ifstream file;
    file.open("assets\\scores.txt");
    if (file.is_open()) {
        std::getline(file, highest_scores);
        std::getline(file, record_time);
    }
    file.close();
    


    SoundManager::GetInstance()->Load("menu_music", "assets\\menu_music.mp3", SOUND_MUSIC, 64);
    SoundManager::GetInstance()->PlayMusic("menu_music", -1);

    TextureManager::GetInstance()->Load("menu_background", "assets\\darkest2.png");

    TextureManager::GetInstance()->Load("menu_play", "assets\\Menu Buttons\\Large Buttons\\Large Buttons\\Play Button.png");
    TextureManager::GetInstance()->Load("menu_play_hover", "assets\\Menu Buttons\\Large Buttons\\Colored Large Buttons\\Play col_Button.png");

    TextureManager::GetInstance()->Load("menu_control", "assets\\Menu Buttons\\Large Buttons\\Large Buttons\\Controls Button.png");
    TextureManager::GetInstance()->Load("menu_control_hover", "assets\\Menu Buttons\\Large Buttons\\Colored Large Buttons\\Controls  col_Button.png");

    TextureManager::GetInstance()->Load("menu_quit", "assets\\Menu Buttons\\Large Buttons\\Large Buttons\\Exit Button.png");
    TextureManager::GetInstance()->Load("menu_quit_hover", "assets\\Menu Buttons\\Large Buttons\\Colored Large Buttons\\Exit  col_Button.png");

    buttons.push_back(new MenuButton(new Properties("menu_play", 600, 250, 300, 100), s_menuToChoosePlayer));
    buttons.push_back(new MenuButton(new Properties("menu_control", 600, 400, 300, 100), s_menuToGuide));
    buttons.push_back(new MenuButton(new Properties("menu_quit", 950, 400, 300, 100), s_exitFromMenu));
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
    TextureManager::GetInstance()->Draw("menu_background", 0, 0, 1280, 720);
    for (MenuButton* button : buttons) {
        button->Draw();
    }
    FontManager::GetInstance()->RenderText("highest_scores", "HIGHEST SCORES: " , 900, 600, {255,0,255,255});
    FontManager::GetInstance()->RenderText("current_highest_scores", highest_scores.c_str(),1200 , 600, { 255,0,255,255 });
    FontManager::GetInstance()->RenderText("best_time", "BEST TIME: ", 900, 640, { 255,0,255,255 });
    FontManager::GetInstance()->RenderText("current_best_time", record_time.c_str(), 1100, 640, { 255,0,255,255 });
}

void MenuState::Update(float dt) {
   
    // Cập nhật trạng thái của tất cả các nút
    for (MenuButton* button : buttons) {
        button->Update(dt);
    }
}

