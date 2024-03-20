#include "MenuButton.h"

MenuButton::MenuButton(Properties* props, void (*callback)()) : GameObject(props), m_callback(callback)
{
	m_NormalState = props->TextureID;
	m_HoverState = props->TextureID + "_hover";
	m_Rect.x = props->X;
	m_Rect.y = props->Y;
	m_Rect.w = props->Width;
	m_Rect.h = props->Height;
	m_currentFrame = MOUSE_OUT;
}

void MenuButton :: Draw() 
{
	TextureManager::GetInstance()->Draw(m_CurrentState, m_Rect.x, m_Rect.y, m_Rect.w, m_Rect.h, SDL_FLIP_NONE);
}

void MenuButton::Update(float dt)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	if (mouseX > m_Rect.x && mouseX < m_Rect.x + m_Rect.w &&
		mouseY > m_Rect.y && mouseY < m_Rect.y + m_Rect.h) {
		m_currentFrame = MOUSE_OVER;
		m_Released = true;
		m_CurrentState = m_HoverState;
		if (Input::GetInstance()->GetLeftMouseButton()) {
			m_currentFrame = CLICKED;
			m_callback();
			m_Released = false;
		}
	}else {
		m_currentFrame = MOUSE_OUT;
		m_CurrentState = m_NormalState;
	}
}

void MenuButton::Clean() {
	TextureManager::GetInstance()->Drop(m_NormalState);
	TextureManager::GetInstance()->Drop(m_HoverState);
}
