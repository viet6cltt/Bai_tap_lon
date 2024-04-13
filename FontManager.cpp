#include "FontManager.h"

FontManager* FontManager::s_Instance = nullptr;

bool FontManager::LoadFont(std::string ID, std::string fontPath, int fontSize) 
{
	if (TTF_Init() == -1) {
		SDL_Log("Failed to initialize SDL_ttf: %s", TTF_GetError());
		return false;
	}
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (font == NULL) {
		SDL_Log("Failed to load font");
		return false;
	}
	m_Fonts[ID] = font;
	return true;
}

void FontManager::RenderText(std::string ID, std::string text, int x, int y, SDL_Color color)
{
	TTF_Font* font = m_Fonts[ID];
	if (font == nullptr)
	{
		SDL_Log("Failed to find font");
		return;
	}
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (surface == nullptr)
	{
		SDL_Log("Failed to load texture");
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
	if (texture == nullptr)
	{
		SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
	}
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);

	SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), texture, NULL, &dst);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}