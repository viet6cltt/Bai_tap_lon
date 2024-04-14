#pragma once

#include "GameState.h"
#include "GameObject.h"
#include "Engine.h"
#include <string>
#include "Engine.h"

class SpecialAbilityState : public GameState
{
public:
	virtual void Update(float dt);
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string getStateID() const { return s_specialabilityID; }
private:
	static void s_resumePlay();

	static const std::string s_specialabilityID;

	bool m_MousePressedInThisState;

	SDL_Texture* background;
	//std::vector<MenuButton*> m_buttons;


};
