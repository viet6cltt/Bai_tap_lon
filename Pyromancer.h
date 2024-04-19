#pragma once

#include "Enemy.h"
#include "HealthBar.h"
#include "FireSpell.h"


#define RUN_FORCE 0.8f

class Pyromancer : public Enemy
{
public:
	Pyromancer(Properties* props);
	virtual void Draw() override;
	virtual void Clean() override {}
	virtual void Update(float dt) override;

	virtual void AnimationState() override;

	//int setHealth(int health) { m_Health = health; }
	//void getDamage() override {m_Damage = damage; }

	virtual int getDamage() {
		if (m_FireSpell != NULL && !m_hasDealtDamage) {
			m_hasDealtDamage = true;
			return m_Damage;
		}
		return 0;
	}
	virtual Collider* getattackZone() {
		if (m_FireSpell != NULL) {
			return m_FireSpell->getAttackZone();
		}
		return NULL;
	}

	void DyingHandler();

	virtual Collider* AttackZone(float dt) override { return m_attackCollider; }
	virtual void Follow_Warrior(Vector2D F);

	virtual bool isAlive() override { 
		if (m_FinishDying) {
			return false;
		}
		return true;
	}

	virtual Vector2D getPosition() override {
		return m_Position;
	}
	virtual void Attack();
private:
	
	int m_AttackBegin;
	int m_AttackCooldown;
	bool m_IsAttacked;
	FireSpell* m_FireSpell;
	HealthBar* m_HealthBar;
	Vector2D m_LastSafePosition;
	Animation* m_Animation;
	RigidBody* m_RigidBody;

	Vector2D m_Position;

	SDL_Rect m_Rect;
	Vector2D m_FollowDirection;
	Vector2D m_Direction;
	Vector2D m_attackDirection;
	float dt = 0;
	SDL_Point* center;

	std::string m_LastState;
};

