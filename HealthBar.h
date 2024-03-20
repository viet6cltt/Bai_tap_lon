#pragma once

#include "GameObject.h"

#include "TextureManager.h"
#include "GameObject.h"
#include <string>
#include "Engine.h"
class HealthBar : public GameObject
{
public:
	HealthBar(Properties* props, int maxHealth);

	virtual void Draw() override;
	virtual void Update(float dt) override;
	virtual void Clean() override;

	void Decrease(int amount) {
		m_CurrentHealth -= amount;
		if (m_CurrentHealth < 0) m_CurrentHealth = 0;
	}

	void Increase(int amount) {
		m_CurrentHealth += amount;
		if (m_CurrentHealth > m_MaxHealth) m_CurrentHealth = m_MaxHealth;
	}

	void setCurrentHealth(int curr_health) {
		m_CurrentHealth = curr_health;
	}

	void setProperties(int ,int,int,int );
	
private:
	SDL_Rect m_Rect;
	int m_MaxHealth;
	int m_CurrentHealth;
	float percent;
	std::string m_Name;

};

