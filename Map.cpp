#include "Map.h"
#include "TextureManager.h"
#include <iostream>
#include <vector>
Map* Map::s_Instance = nullptr;


Map::Map()
{
	TextureManager::GetInstance()->Load("1", "assets\\tileset\\1.png");
	TextureManager::GetInstance()->Load("2", "assets\\tileset\\2.png");
	TextureManager::GetInstance()->Load("3", "assets\\tileset\\3.png");
	TextureManager::GetInstance()->Load("5", "assets\\tileset\\5.png");
	TextureManager::GetInstance()->Load("9", "assets\\tileset\\9.png");
	TextureManager::GetInstance()->Load("10", "assets\\tileset\\10.png");
	TextureManager::GetInstance()->Load("11", "assets\\tileset\\11.png");
	TextureManager::GetInstance()->Load("12", "assets\\tileset\\12.png");
	TextureManager::GetInstance()->Load("13", "assets\\tileset\\13.png");
	TextureManager::GetInstance()->Load("17", "assets\\tileset\\17.png");
	TextureManager::GetInstance()->Load("18", "assets\\tileset\\18.png");
	TextureManager::GetInstance()->Load("19", "assets\\tileset\\19.png");
	TextureManager::GetInstance()->Load("26", "assets\\tileset\\26.png");
	TextureManager::GetInstance()->Load("28", "assets\\tileset\\28.png");
	TextureManager::GetInstance()->Load("35", "assets\\tileset\\35.png");
	TextureManager::GetInstance()->Load("47", "assets\\tileset\\47.png");
	TextureManager::GetInstance()->Load("50", "assets\\tileset\\50.png");


	LoadMap();

}


void Map::LoadMap()
{
	map = {
	   {19,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,17},
	   {11,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,9},
	   {11,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,5,9},
	   {11,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,5,9},
	   {11,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,5,9},
	   {11,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,5,9},
	   {11,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,5,9},
	   {11,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,5,9},
	   {11,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,5,9},
	   {11,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,5,9},
	   {11,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,5,9},
	   {11,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,5,9},
	   {11,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,5,9},
	   {11,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,5,9},
	   {11,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,5,9},
	   {11,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,5,9},
	   {11,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,5,9},
	   {11,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,5,9},
	   {11,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,9},
	   {3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1}
	};
}
void Map::DrawMap()
{
	int type = 0;
	for (int row = 0; row < 20; row++) {

		for (int column = 0; column < 40; column++) {
			type = map[row][column];

			dest.x = column * 32;
			dest.y = row * 32;
			switch (type)
			{

			case 1:TextureManager::GetInstance()->Draw("1", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 2:TextureManager::GetInstance()->Draw("2", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 3:TextureManager::GetInstance()->Draw("3", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 5:TextureManager::GetInstance()->Draw("5", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 9:TextureManager::GetInstance()->Draw("9", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 10:TextureManager::GetInstance()->Draw("10", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 11:TextureManager::GetInstance()->Draw("11", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 12:TextureManager::GetInstance()->Draw("12", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 13:TextureManager::GetInstance()->Draw("13", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 17:TextureManager::GetInstance()->Draw("17", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 18:TextureManager::GetInstance()->Draw("18", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 19:TextureManager::GetInstance()->Draw("19", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 26:TextureManager::GetInstance()->Draw("26", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 28:TextureManager::GetInstance()->Draw("28", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 35:TextureManager::GetInstance()->Draw("35", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 47:TextureManager::GetInstance()->Draw("47", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 50:TextureManager::GetInstance()->Draw("50", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;


			default: break;
			}


		}

	}

}



