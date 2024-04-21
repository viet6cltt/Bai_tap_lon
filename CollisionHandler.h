#pragma once

#include <SDL.h>
#include<vector>
#include "Map.h"
#include "Engine.h"
#include "Character.h"

class CollisionHandler
{
public:
	bool CheckCollision(SDL_Rect a, SDL_Rect b);
	bool MapCollision(SDL_Rect a);
	inline static CollisionHandler* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler; }


private:
	std::vector<std::vector<int>> map_tile = Map::GetInstance()->get_Map();
	//int** map_tile = Map::GetInstance()->GetMap();

	

	static CollisionHandler* s_Instance;
};


