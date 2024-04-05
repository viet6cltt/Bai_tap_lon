#include "SpecialAbiliyState.h"

const std::string SpecialAbilityState::s_specialabilityID = "SPECIALABILITY";

void SpecialAbilityState::s_resumePlay()
{
	printf("resume play\n");
	Engine::GetInstance()->getStateMachine()->popState();
}

bool SpecialAbilityState::OnEnter()
{
	SDL_Surface* screenshot = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	SDL_RenderReadPixels(Engine::GetInstance()->GetRenderer(), NULL, SDL_PIXELFORMAT_ARGB8888, screenshot->pixels, screenshot->pitch);
	background = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), screenshot);
	SDL_FreeSurface(screenshot);

	m_MousePressedInThisState = false;
	return true;
}

bool SpecialAbilityState::OnExit()
{
	SDL_DestroyTexture(background);
	return true;
}

void SpecialAbilityState::Render()
{
	SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), background, NULL, NULL);
}

void SpecialAbilityState::Update(float dt)
{
	if (Input::GetInstance()->GetLeftMouseButton())
	{
		m_MousePressedInThisState = true;
		Engine::GetInstance()->setMouse(Input::GetInstance()->GetMouseX(), Input::GetInstance()->GetMouseY());
		if (m_MousePressedInThisState)
		{
			Engine::GetInstance()->getStateMachine()->popState();
		}
	}
}


