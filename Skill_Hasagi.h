#pragma once
#include "Skill.h"
#include "Engine.h"

#define RUN_FORCE 4.0f

class Skill_Hasagi : public Skill
{
public:
	Skill_Hasagi(Properties* props,int damage);

	void setDamage(int damage) { m_damage = damage * 15; }
	int getDamage() { 
		if (!m_hasDealtDamage) {
			m_hasDealtDamage = true;
			return m_damage;
		}
		return 0;
	}

	virtual void Activate(Vector2D,Vector2D) override;
	virtual void Update(float dt) override;
	virtual void Draw() override;
	virtual void Clean() override;

	Collider* getAttackZone() {
		return m_Collider;
	}

	bool IsDeleted() const { return m_IsDeleted; }

private:
	int m_damage;
	int m_manacost;

	Collider* m_Collider;
	Animation* m_Animation;
	RigidBody* m_RigidBody;
	Vector2D m_Direction;
	Vector2D m_Position;

	float m_LifeTime;
	bool m_hasDealtDamage;

	bool m_IsDeleted;
};

