#pragma once

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Vector2D.h"
#include "Collider.h"



class Enemy : public Character
{
public:
	Enemy(Properties* props) : Character(props){}
	virtual void Draw() = 0;
	virtual void Clean() = 0;
	virtual void Update(float dt) = 0;

	virtual void AnimationState() = 0;
	int getHealth() { return m_Health; }
	virtual int getDamage() = 0;

	//virtual int setHealth(int health) = 0;
	//int setDamage(int damage);

	virtual bool Attack(float dt) = 0;
	virtual void SetAttack() = 0;
	virtual void ResetAttack() = 0;
	//virtual void StopAttack() = 0;

	virtual void receiveDamage(int damage) = 0;
	virtual Collider* AttackZone(float dt) = 0;

	virtual Collider* getCollider() = 0;

	virtual bool isAlive() = 0;
private:
	bool m_IsRunning;

	bool m_IsAttacking;
	bool m_IsCrouching;

	bool m_IsUp;
	bool m_IsDown;

	float m_AttackTime;

	Collider* m_Collider;
	Vector2D m_LastSafePosition;
	Animation* m_Animation;
	RigidBody* m_RigidBody;

	int m_Health;
	int m_Damage;

	SDL_Rect m_Rect;
};

