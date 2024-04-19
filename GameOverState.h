#pragma once

#include "GameState.h"
#include "MenuButton.h"

#include "GameStateMachine.h"
#include <vector>
#include "Engine.h"

#include "MenuState.h"

class GameOverState : public GameState {
public:

    bool OnEnter();

    bool OnExit();

    void Render();

    void Update(float dt);

    virtual std::string getStateID() const { return s_gameoverID; }
    static void s_toMenu() {
        Engine::GetInstance()->getStateMachine()->changeState(new MenuState());
    }

    static void s_exitFromGameOver() {
        Engine::GetInstance()->Quit();
    }

private:
    std::vector<MenuButton*> buttons; 
    static const std::string s_gameoverID;
};

