
#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Vector2D.h"
#include "Collider.h"
#include "Skill_Hasagi.h"

#include "SpecialAbiliyState.h"

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

	void setisSkill_Hasagi(bool k) { m_isSkill_Hasagi = k; }

	Collider* getCollider() { return m_Collider; }
	Collider* AttackZone(float dt);
	void receiveDamage(int damage){
		m_Health -= damage;
	}

	virtual Vector2D getPosition() override
	{
		//printf("toa do cua nhan vat: %f %f\n", m_Position.X, m_Position.Y);
		m_Position.X = m_Origin->X;
		m_Position.Y = m_Origin->Y;
		return m_Position;
	}



	bool isAlive() const { return m_Health > 0; }
private:
	void AnimationState();
private:
	bool m_IsRunning;

	bool m_isSkill_Hasagi;
	
	bool m_IsAttacking;
	bool m_IsCrouching;

	bool m_skill_Dao_Pha_Thien_Mon;

	bool m_IsUp;
	bool m_IsDown;

	float m_AttackTime;

	Vector2D m_Position;
	Vector2D m_SkillDirection;

	Collider* m_attackCollider;
	Collider* m_Collider;
	Vector2D m_LastSafePosition;
	Animation* m_Animation;
	RigidBody* m_RigidBody;

	int m_Health;
	int m_Damage;

	SDL_Rect m_Rect;
	SDL_Point* center;

	Skill_Hasagi* m_skill_Hasagi;


};

#endif

