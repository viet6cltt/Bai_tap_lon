#include "Animation.h"
#include "TextureManager.h"

void Animation::Update()
{
	m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
	/*
		SDL_GetTicks(): tra ve so milisecond da troi qua
		m_AnimSpeed: toc do hoat anh
		m_FramCount: so luong khung trong hoat anh(1 sheeet co 10 anh thi la 10)
		m_SpriteFrame: tinh toan khung hien tai
	*/
}

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip)
{
	TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, flip);
}
//SetProps: set cac  thuoc tinh cua hoat anh
void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed)
{
	m_TextureID = textureID;
	m_SpriteRow = spriteRow;
	m_FrameCount = frameCount;
	m_AnimSpeed = animSpeed;

}