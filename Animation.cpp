#include "Animation.h"
#include "TextureManager.h"
#include <iostream>
void Animation::Update()
{
	//std::cout << SDL_GetTicks() << std::endl;

	/*if (m_StartTime == 0) {
		Start();
	}*/

	Uint32 elapsedTime = SDL_GetTicks() - m_StartTime;

	m_SpriteFrame = (elapsedTime / m_AnimSpeed) % m_FrameCount + m_StartFrame;
	m_SpriteRow = m_SpriteFrame / m_MaxFramesPerRow + m_firstlyRow;
	m_SpriteFrame = m_SpriteFrame % m_MaxFramesPerRow;
}

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip,SDL_Point* center)
{
	TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, flip, center);
}
//SetProps: set cac  thuoc tinh cua hoat anh
void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, int maxFramesPerRow, int startFrame)
{
	m_TextureID = textureID;
	m_SpriteRow = spriteRow;
	m_FrameCount = frameCount;
	m_AnimSpeed = animSpeed;

	m_MaxFramesPerRow = maxFramesPerRow;
	m_firstlyRow = m_SpriteRow;
	m_StartFrame = startFrame;
}