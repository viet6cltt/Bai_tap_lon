#pragma once

#include "Enemy.h"
#include "HealthBar.h"
#include "SoundManager.h"


#define RUN_FORCE 1.5f
#define MAX_HEALTH_TYPE1 7000
#define MAX_HEALTH_TYPE2 16000
#define DAMAGE_TYPE1 200
#define DAMAGE_TYPE2 600
class Final_Boss : public Enemy
{
public:
	Final_Boss(Properties* props);
	virtual void Draw() override;
	virtual void Clean() override{}
	virtual void Update(float dt) override;

	virtual void AnimationState() override;

	virtual bool Attack(float dt) {
		if (!m_IsAttacking && m_CanAttack) {
			m_IsRunning = false;
			m_IsAttacking = true;
			m_CanAttack = false;
			m_hasDealtDamage = false;
			m_FinishAttack = false;
			if(Type == 1) SoundManager::GetInstance()->PlaySound("final_boss_1_attacking", 0, 14);
			else SoundManager::GetInstance()->PlaySound("final_boss_2_attacking", 0, 17);
		}
		return true;
	}

	void AttackHandler();
	void DyingHandler();
	void RevivingHandler();
	void CastingHandler();

	virtual int getType() override {
		return Type;
	}
	virtual void receiveDamage(const std::string& attackType, int damage) override {
		if (attackType == "gravity" || attackType == "slash") {
			m_Health -= damage;
			return;
		}

		if (m_hasReceivedDamage[attackType] == false) {
			m_hasReceivedDamage[attackType] = true;
			m_Health -= damage;
		}

	}

	

	virtual bool is_Summoning() {
		return cast_type == 2;
	}
	


	//int setHealth(int health) { m_Health = health; }
	//void getDamage() override {m_Damage = damage; }

	virtual Collider* AttackZone(float dt) override;


	virtual bool isAlive() override { 
		if (m_FinishDyingType2) {
			return false;
		}
		return true;
		
	}

	virtual void Follow_Warrior(Vector2D F);

	virtual Vector2D getPosition() override {
		return m_Position;
	}
private:
	//dying and reviving
	bool m_IsDyingType1;
	bool m_FinishDyingType1;
	bool m_IsReviving;
	int m_DiedTimeBegin;
	bool m_FinishReviving;
	bool m_RevivingWaiting;
	//dying type 2
	bool m_IsDyingType2;
	bool m_FinishDyingType2;
	//casting
	bool m_IsCasting;
	bool m_CanCast;
	int m_CastBeginTime;
	int m_CastCooldown;
	bool m_FinishCasting;
	int cast_type; // 1 la hoi mau, 2 la trieu hoi, 3 la dung ult

	HealthBar* m_HealthBar;

	Vector2D m_LastSafePosition;
	Animation* m_Animation;
	RigidBody* m_RigidBody;

	Vector2D m_Position;

	SDL_Rect m_Rect;
	Vector2D m_FollowDirection;
	Vector2D m_Direction;

	//PathFinder* m_PathFinder;
	
	int Type;

	std::string m_LastState;

	std::vector<std::vector<int>> m_map = {
   {47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47},
   {47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,11,18,18,18,18,18,18,18,18,18,18,18,18,18,18,47,47,47,47},
   {18,18,18,18,18,18,18,47,47,47,47,47,47,47,47,47,47,47,47,47,47,11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,47,47,47},
   {10,10,10,10,10,10,17,18,18,18,18,18,18,18,18,18,18,18,18,18,18,19,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,47,47,47},
   {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,47,47,47},
   {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,47,47,47},
   {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,47,47,47},
   {2,3,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,47,47,47},
   {10,11,5,13,1,2,3,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,47,47,47},
   {18,19,13,13,9,10,11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,13,13,13},
   {5,5,13,1,10,10,11,10,10,10,10,1,2,3,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,13,13,13},
   {5,5,5,9,10,10,11,10,10,10,10,9,10,11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,13,13,13},
   {5,5,5,9,10,10,11,10,10,10,10,17,18,19,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,13,13,13},
   {13,12,5,9,10,10,11,10,10,10,10,50,50,50,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,47,47,47},
   {13,13,5,9,10,10,11,10,10,10,1,2,2,2,3,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,47,47,47},
   {13,13,12,17,18,18,19,10,10,10,9,28,28,28,11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,47,47,47},
   {35,10,10,10,10,10,10,10,10,10,9,28,28,28,11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,47,47,47},
   {35,10,10,10,10,10,10,10,10,10,9,28,28,28,11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,47,47,47},
   {35,10,10,10,10,10,10,10,10,10,9,28,28,28,11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,47,47,47},
   {35,26,26,26,26,26,26,26,26,26,26,28,28,28,28,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,13,47,47,47}
	};
};

