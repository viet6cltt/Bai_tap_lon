#pragma once

#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:
	void pushState(GameState* pState); //add a state without removing the pevious state
	void changeState(GameState* pState); //remvoe prev  state before adding another
	void popState(); //remove without adding another

	void Update(float dt);
	void Render();
private:
	std::vector<GameState*> m_gameStates;
};
