#pragma once

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Vector2D.h"
#include "Collider.h"
#include <map>
#include "FireSpell.h"



class Enemy : public Character
{
public:
	Enemy(Properties* props) : Character(props){}
	virtual void Draw() = 0;
	virtual void Clean() = 0;
	virtual void Update(float dt) = 0;

	virtual void AnimationState() = 0;
	int getHealth() { return m_Health; }
	virtual int getDamage() {
		if (m_IsAttacking && !m_hasDealtDamage) {
			m_hasDealtDamage = true;
			return m_Damage;
		}
	
		return 0;
	}

	//virtual int setHealth(int health) = 0;
	//int setDamage(int damage);

	virtual bool Attack(float dt) {
		if (!m_IsAttacking && m_CanAttack) {
			
			m_IsRunning = false;
			m_IsAttacking = true;
			m_CanAttack = false; 
			m_hasDealtDamage = false;
			m_FinishAttack = false;
		}
		return true;
	}
	//virtual void StopAttack() = 0;
	
	virtual void receiveDamage(const std::string& attackType, int damage) {
		if (attackType == "gravity" || attackType == "slash") {
			m_Health -= damage;
			m_IsHurt = true;
			m_FinishHurt = false;
			return;
		}
		
		if (m_hasReceivedDamage[attackType] == false) {
			m_hasReceivedDamage[attackType] = true;
			m_Health -= damage;
			if (attackType == "hasagi") {
				m_IsHurt = true;
				m_FinishHurt = false;
			}
		}
		
	}

	virtual bool is_Summoning() { return 0; }

	void resetgetDamage(const std::string& attackType) {
		m_hasReceivedDamage[attackType] = false;
	}

	virtual FireSpell* getFireSpell() {
		return m_FireSpell;
	}

	virtual int getType() { return 0; }

	virtual Collider* AttackZone(float dt) = 0;
	virtual Collider* getattackZone() { return m_attackCollider; }
	bool getIsAttack() { return m_IsAttacking; }
	Collider* getCollider() { return m_Collider; }
	virtual void Follow_Warrior(Vector2D F) = 0;

	virtual bool isAlive() = 0;
protected:
	FireSpell* m_FireSpell;
	bool m_IsRunning;
	std::map<std::string, bool> m_hasReceivedDamage;
	bool m_IsAttacking;
	bool m_IsHurt;
	bool m_FinishHurt;
	bool m_hasDealtDamage;
	bool m_CanAttack;
	bool m_FinishAttack;

	bool m_IsDying;
	bool m_FinishDying;

	Collider* m_attackCollider;

	Collider* m_Collider;
	Vector2D m_LastSafePosition;
	Animation* m_Animation;
	RigidBody* m_RigidBody;

	int m_Health;
	int m_Damage;

	SDL_Rect m_Rect;
	std::string m_LastState;
	
};

