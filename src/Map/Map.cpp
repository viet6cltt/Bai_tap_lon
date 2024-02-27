#include "Map.h"
#include "TextureManager.h"
#include <iostream>

Map* Map::s_Instance = nullptr;

 int arr[20][40] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{6,14,13,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,14,14,10,0,0,0,0,0,0,0,0,0,0,0},
	{5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,11,9,5,0,0,0,0,0,0,0,0,0,0,0},
	{9,9,9,9,2,1,2,4,1,2,3,4,1,2,3,4,1,13,13,13,13,13,2,3,1,9,9,9,5,0,0,0,0,0,0,0,0,0,0,0},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,17,17,17,17,17,9,9,9,9,9,9,11,1,2,1,2,1,2,1,2,1,2,1},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,17,17,17,17,17,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}
};
Map::Map()
{
	
	TextureManager::GetInstance()->Load("9","assets\\9.png");
	TextureManager::GetInstance()->Load("1", "assets\\2.png");
	TextureManager::GetInstance()->Load("2", "assets\\3.png");
	TextureManager::GetInstance()->Load("11", "assets\\7.png");
	TextureManager::GetInstance()->Load("5", "assets\\5.png");
	TextureManager::GetInstance()->Load("10", "assets\\6.png");
	TextureManager::GetInstance()->Load("14", "assets\\1.png");
	TextureManager::GetInstance()->Load("6", "assets\\4.png");
	TextureManager::GetInstance()->Load("3", "assets\\3_1.png");
	TextureManager::GetInstance()->Load("17", "assets\\water.png");
	TextureManager::GetInstance()->Load("13", "assets\\8.png");
	TextureManager::GetInstance()->Load("4", "assets\\3_2.png");
	
	
	/*m_TextureMap da chua cac phan cua  map tile*/


	LoadMap(arr);

}


void Map::LoadMap(int arr[20][40])
{
	for (int row = 0; row < 20; row++) {
		for (int column = 0; column < 40; column++) {
			map[row][column] = arr[row][column];
		}
	}
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
			
			case 1:TextureManager::GetInstance()->Draw("1", dest.x, dest.y, 32, 32, SDL_FLIP_NONE);break;
			case 2:TextureManager::GetInstance()->Draw("2", dest.x, dest.y, 32, 32, SDL_FLIP_NONE);break;
			case 3:TextureManager::GetInstance()->Draw("3", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 4:TextureManager::GetInstance()->Draw("4", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 5:TextureManager::GetInstance()->Draw("5", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 6:TextureManager::GetInstance()->Draw("6", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 9:TextureManager::GetInstance()->Draw("9", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 10:TextureManager::GetInstance()->Draw("10", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 11:TextureManager::GetInstance()->Draw("11", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 13:TextureManager::GetInstance()->Draw("13", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 14:TextureManager::GetInstance()->Draw("14", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;
			case 17:TextureManager::GetInstance()->Draw("17", dest.x, dest.y, 32, 32, SDL_FLIP_NONE); break;

			default: break;
			}
			
			
		}
		
	}

}



