#include "Engine.h"
#include "TextureManager.h"
#include "Input.h"
#include "Warrior.h"
#include <SDL.h>
#include "Timer.h"
#include "MenuButton.h"
#include "Map.h"

#include "GameStateMachine.h"
#include "SoundManager.h"
#include "PauseState.h"
#include "PlayState.h"
#include "MenuState.h"
Engine* Engine::s_Instance = nullptr;

bool Engine::Init()
{
	m_scores = 0;
	player_type = 0;
	screen_type = 1;
	m_Time = 0;
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	m_Window = SDL_CreateWindow("Everpath", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
	if (m_Window == nullptr)
	{
		SDL_Log("Failed to creat Window: %s", SDL_GetError());
		return false;
	}

	/*
	SDL_RENDERER_ACCELERATED: use hardware accelerate(tang toc)
	*/
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr)
	{
		SDL_Log("Failed to create Renderer: %s", SDL_GetError());
		return false;
	}
	
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MenuState());

	return m_IsRunning = true;
}

void Engine::Update()
{
	if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_LCTRL)&&Input::GetInstance()->GetKeyDown(SDL_SCANCODE_M)){
		//std::cout << "dang tang am";
		SoundManager::GetInstance()->AdjustMasterVolume(5);
	}
	else if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_LCTRL) && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_N)){
		//std::cout << "dang giam am";
		SoundManager::GetInstance()->AdjustMasterVolume(-5);
	}


	float dt = Timer::GetInstance()->GetDealtaTime();
	//SDL_Log("%f", dt);
	m_pGameStateMachine->Update(dt);

}

void Engine::Render()
{
	SDL_RenderClear(m_Renderer); //clear the window to blank
	
	
	m_pGameStateMachine->Render();
	SDL_RenderPresent(m_Renderer); //cap nhat man hinh
}

void Engine::Events()
{
	Input::GetInstance()->Listen();
}


bool Engine::Clean()
{
	TextureManager::GetInstance()->Clean();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	IMG_Quit();
	SDL_Quit();
	return true;
}

void Engine::Quit()
{
	m_IsRunning = false;
}