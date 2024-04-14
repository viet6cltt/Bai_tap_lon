﻿#include "HealthBar.h"

HealthBar::HealthBar(Properties* props, int maxHealth) : GameObject(props), m_MaxHealth(maxHealth)
{
    percent = 1;
    m_CurrentHealth = m_MaxHealth;
	m_Name = props->TextureID;
	m_Rect.x = props->X;
	m_Rect.y = props->Y;
	m_Rect.w = props->Width;
	m_Rect.h = props->Height;
}

void HealthBar::Draw() {
    
    //TextureManager::GetInstance()->Draw(m_Name, m_Rect.x, m_Rect.y, m_Rect.w, m_Rect.h);
    if (m_Name == "none_bar") {
        SDL_Rect healthBar;
        healthBar.x = m_Rect.x ;
        healthBar.y = m_Rect.y ;
        healthBar.w = m_Rect.w * percent; // Chiều rộng của thanh máu phụ thuộc vào lượng máu còn lại
        healthBar.h = m_Rect.h;

        TextureManager::GetInstance()->Draw(m_Name, m_Rect.x, m_Rect.y, m_Rect.w, m_Rect.h);
        TextureManager::GetInstance()->Draw("player_fullhealth", healthBar.x, healthBar.y, healthBar.w, healthBar.h);
        
        

        return;
    }
    
    // Tạo một hình chữ nhật đại diện cho thanh máu
    SDL_Rect healthBar;
    healthBar.x = m_Rect.x;
    healthBar.y = m_Rect.y  ;
    healthBar.w = m_Rect.w * percent; // Chiều rộng của thanh máu phụ thuộc vào lượng máu còn lại
    healthBar.h = m_Rect.h ;

    
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 0, 0, 255);

    
    SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &healthBar);
    TextureManager::GetInstance()->Draw(m_Name, m_Rect.x, m_Rect.y, m_Rect.w, m_Rect.h);
}

void HealthBar::setProperties(int x,int y,int w,int h) {
    m_Rect.x = x;
    m_Rect.y = y;
    m_Rect.w = w;
    m_Rect.h = h;
}

void HealthBar::Update(float dt) {
    percent = (float)m_CurrentHealth / m_MaxHealth;
}

void HealthBar::Clean() {
    TextureManager::GetInstance()->Drop(m_Name);
}





