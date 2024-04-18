#pragma once

#include "GameState.h"
#include "GameObject.h"
#include <vector>
#include "Engine.h"
#include <string>
#include "MenuButton.h"
#include "Engine.h"

class PauseState : public GameState
{
public:
	virtual void Update(float dt);
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string getStateID() const { return s_pauseID; }
private:

	static void s_pauseToMain();
	static void s_resumePlay();

	static const std::string s_pauseID;

	std::vector<MenuButton*> m_buttons;

	bool is_Out;

	
};

