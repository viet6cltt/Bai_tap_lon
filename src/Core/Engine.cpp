#include "Engine.h"
#include "TextureManager.h"
#include "Input.h"
#include "Warrior.h"
#include <SDL.h>
#include "Timer.h"
#include "Map.h"
#include "Camera.h"

Map* map = nullptr;

Engine* Engine::s_Instance = nullptr;
Warrior* player = nullptr;
bool Engine::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	m_Window = SDL_CreateWindow("Wash Dishes", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
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
	/* SDL_RENDERER_ACCELERATED: dung phan cung de tang toc do hoa
	SDL_RENDERER_PRESENTVSYNC: dong bo voi tan so man hinh*/

	TextureManager::GetInstance()->Load("background", "assets\\Background_2.png");
	
	map = new Map();

	TextureManager::GetInstance()->Load("player_idle", "assets\\Knight\\Colour2\\Outline\\120x80_PNGSheets\\_Idle.png");
	TextureManager::GetInstance()->Load("player_run", "assets\\Knight\\Colour2\\Outline\\120x80_PNGSheets\\_Run.png");
	TextureManager::GetInstance()->Load("player_attack", "assets\\Knight\\Colour2\\Outline\\120x80_PNGSheets\\_AttackNoMovement.png");
	TextureManager::GetInstance()->Load("player_jump", "assets\\Knight\\Colour2\\Outline\\120x80_PNGSheets\\_Jump.png");
	player = new Warrior(Properties("player_idle",350, 100, 120, 80));
	


	Camera::GetInstance()->SetTarget(player->GetOrigin());

	return m_IsRunning = true;
}

void Engine::Update()
{
	float dt = Timer::GetInstance()->GetDealtaTime();
	SDL_Log("%f", dt);
	player->Update(dt);

}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255); //set color
	SDL_RenderClear(m_Renderer); //clear the window to blank
	TextureManager::GetInstance()->Draw("background", 0,0,1390,640);
	map->DrawMap();
	player->Draw(); //ve nhan vat chinh
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