#pragma once

#include "RangedType.h"
#include "CollisionHandler.h"

#define RUN_FORCE 5.0f

class FireSpell : public RangedType
{
public:
	FireSpell(Properties* props, int damage);

	void setDamage(int damage) { m_damage = damage; }
	int getDamage() {
		return m_damage;
	}

	virtual void Activate(Vector2D, Vector2D) override;
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

	bool m_IsDeleted;
};