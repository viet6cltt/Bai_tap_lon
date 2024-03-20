#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* pState)
{
	m_gameStates.push_back(pState);
	m_gameStates.back()->OnEnter();
}

void GameStateMachine::popState()
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->OnExit())
		{
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}
	}
}

void GameStateMachine::changeState(GameState* pState)
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->getStateID() == pState->getStateID())
		{
			return; // do nothing
		}
		if (m_gameStates.back()->OnExit())
		{
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}
	}
	// push back our new state
	m_gameStates.push_back(pState);
	// initialise it
	m_gameStates.back()->OnEnter();
}

void GameStateMachine::Update(float dt) {
	if (!m_gameStates.empty()) {
		m_gameStates.back()->Update(dt);
	}
}

void GameStateMachine::Render()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->Render();
	}
}