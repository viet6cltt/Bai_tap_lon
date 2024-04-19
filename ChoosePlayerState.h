#pragma once
#include "GameState.h"
#include "GameObject.h"
#include <vector>
#include "Engine.h"
#include <string>

#include "Engine.h"

class ChoosePlayerState : public GameState
{
public:
    bool OnEnter();

    bool OnExit();

    void Render();

    void Update(float dt);

    std::string getStateID() const { return "CHOOSEPLAYER"; }

    // Các phương thức khác của lớp Menu

    static void s_chooseplayerToPlay_1selected();
    static void s_chooseplayerToPlay_2selected();
private:
    std::vector<MenuButton*> m_buttons;
  

};

