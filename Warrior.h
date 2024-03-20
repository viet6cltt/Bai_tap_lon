
#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Vector2D.h"
#include "Collider.h"

#define ATTACK_TIME 30.0f
#define RUN_FORCE 4.0f

class Warrior : public Character
{
public:

	Warrior(Properties* props);
	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);

	int getHealth() { return m_Health; }
	int getDamage() { return m_Damage; }

	int setHealth(int health) { m_Health = health; }
	int setDamage(int damage) { m_Damage = damage; }

	Collider* getCollider() { return m_Collider; }
	Collider* AttackZone(float dt);
	void receiveDamage(int damage){
		m_Health -= damage;
	}

	bool isAlive() const { return m_Health > 0; }
private:
	void AnimationState();
private:
	bool m_IsRunning;
	
	bool m_IsAttacking;
	bool m_IsCrouching;

	bool m_IsUp;
	bool m_IsDown;

	float m_AttackTime;

	Collider* m_attackCollider;
	Collider* m_Collider;
	Vector2D m_LastSafePosition;
	Animation* m_Animation;
	RigidBody* m_RigidBody;

	int m_Health;
	int m_Damage;

	SDL_Rect m_Rect;
};

#endif

