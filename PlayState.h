#pragma once

#include "GameObject.h"
#include "MenuButton.h"
#include "TextureManager.h"
#include <vector>
#include <string>
#include "GameState.h"
#include "Warrior.h"
#include "Map.h"
#include "Input.h"
#include "HealthBar.h"
#include "Engine.h"
#include "Enemy1.h"
#include "Enemy.h"
#include "Enemy_Boss1.h"
#include "FontManager.h"
#include "Pyromancer.h"
#include "Final_Boss.h"
#include "Obelysk.h"


class PlayState : public GameState
{
public:
	virtual void Update(float dt);
	virtual void Render();
	virtual bool OnEnter();
	virtual bool OnExit();

	void Lv1();
	void Lv2();
	void Lv3();
	void Lv4();
	void Lv5();
	void Lv6();

	void SpawnEnemy();
	Vector2D getWarriorPosition() {
		return m_Warrior->getPosition();
	}
	virtual std::string getStateID() const { return s_playID; }
private:
	static const std::string s_playID;
	//std::vector<Warrior*> m_playerObjects;
	Warrior* m_Warrior;
	HealthBar* m_playerheal;
	std::vector<Enemy*> m_Enemies;
	Obelysk* m_Obelysk;
	std::vector<HealthBar*> m_EnemyHealth;
	Animation* test; 
	int summon_ememies_count;
	bool is_summoned;
	
	int m_Score;

	int m_TimeBegin;
	double m_SpawnTimer;
	bool is_FinishLv;
};



