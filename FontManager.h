#pragma once

#include <SDL_ttf.h>
#include "Engine.h"
#include <string>
#include <map>

class FontManager
{
public:
	static FontManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new FontManager(); }
	
	bool LoadFont(std::string ID, std::string fontPath, int fontSize);
	void RenderText(std::string ID, std::string text, int x, int y, SDL_Color color);
private:
	FontManager(){}
	~FontManager() {}

	std::map<std::string, TTF_Font*> m_Fonts;
	static FontManager* s_Instance;
};

