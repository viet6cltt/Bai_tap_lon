#pragma once
#include "Enemy.h"
#include "HealthBar.h"
#define ATTACK_TIME 70.0f
#define RUN_FORCE 2.0f

class Enemy1 : public Enemy
{
public:
	Enemy1(Properties* props);
	virtual void Draw() override;
	virtual void Clean() override;
	virtual void Update(float dt) override;

	virtual void AnimationState() override;

	int getHealth() { return m_Health; }
	virtual int getDamage() override { return m_Damage; }

	//int setHealth(int health) { m_Health = health; }
	//void getDamage() override {m_Damage = damage; }
	virtual void SetAttack() override {
		m_HasAttackedPostCollision = true;
	}
	virtual void ResetAttack() override{
		m_HasAttackedPostCollision = false;
	}

	virtual Collider* AttackZone(float dt) override;
	virtual bool Attack(float dt) override;
	//virtual void StopAttack() override;
	virtual Collider* getCollider() override { return m_Collider; }

	virtual bool isAlive() override { return m_Health > 0; }

	virtual void receiveDamage(int damage) override{
		m_Health -= damage;
		printf("%d\n", m_Health);
	}

	

private:
	bool m_IsRunning;

	bool m_HasAttackedPostCollision;
	bool m_IsAttacking;
	bool m_IsCrouching;

	bool m_IsUp;
	bool m_IsDown;

	float m_AttackTime;
	bool m_CanAttack;
	
	HealthBar* m_HealthBar;
	Collider* m_attackCollider;

	Collider* m_Collider;
	Vector2D m_LastSafePosition;
	Animation* m_Animation;
	RigidBody* m_RigidBody;

	int m_Health;
	int m_Damage;

	SDL_Rect m_Rect;
};

