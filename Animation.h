
#ifndef ANIMATION_H
#define ANIMATION_H

#include<SDL.h>
#include<string>


class Animation
{
public:
	Animation() {}

	void Update();
	void Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE,SDL_Point* center = nullptr);
	void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed,int maxFramesPerRow,int startFrame = 0);
	int getSpriteFrame() {
		return m_SpriteFrame;
	}
	int getSpriteRow() {
		return m_SpriteRow;
	}
	int get_sprite() {
		return m_FrameCount;
	}
	void Start() {
		m_StartTime = SDL_GetTicks();
	}
private:
	int m_StartFrame;
	int m_SpriteRow, m_SpriteFrame;
	int m_AnimSpeed, m_FrameCount;
	std::string m_TextureID;

	int m_MaxFramesPerRow;
	int m_firstlyRow;

	Uint32 m_StartTime;
};

#endif