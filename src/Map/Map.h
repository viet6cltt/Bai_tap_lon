#pragma once

#include "GameObject.h"

class Map
{
public:

	static Map* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Map(); }


	Map();

	void LoadMap(int arr[20][40]);
	void DrawMap();


private:
	int map[20][40];
	SDL_Rect src, dest;

	static Map* s_Instance;

};

