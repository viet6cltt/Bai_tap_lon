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


class PlayState : public GameState
{
public:
	virtual void Update(float dt);
	virtual void Render();
	virtual bool OnEnter();
	virtual bool OnExit();

	void SpawnEnemy();
	Vector2D FollowWarrior(Enemy* enemy);

	virtual std::string getStateID() const { return s_playID; }
private:
	static const std::string s_playID;
	//std::vector<Warrior*> m_playerObjects;
	std::vector<Warrior*> m_Warrior;
	HealthBar* m_playerheal;
	std::vector<Enemy*> m_Enemies;
	std::vector<HealthBar*> m_EnemyHealth;

	double m_SpawnTimer;
};



