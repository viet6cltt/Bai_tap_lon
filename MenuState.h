#pragma once

#include "GameState.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "GameStateMachine.h"
#include <vector>
#include "Engine.h"
#include "FontManager.h"
#include <string>

class MenuState : public GameState{
public:
  
    bool OnEnter();

    bool OnExit();

    void Render();

    void Update(float dt);

    std::string getStateID() const { return "MENU"; }

    // Các phương thức khác của lớp Menu

    static void s_menuToPlay() {
        Engine::GetInstance()->getStateMachine()->changeState(new PlayState());
    }

    static void s_exitFromMenu() {
        Engine::GetInstance()->Quit();
    }

private:
    std::vector<MenuButton*> buttons;  // Danh sách các nút
    int time;
};
