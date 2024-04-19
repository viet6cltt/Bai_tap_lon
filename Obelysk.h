#pragma once

#include "Enemy.h"
#include "SoundManager.h"

class Obelysk : public Enemy
{
public:
	Obelysk(Properties* props);
	virtual void Draw() override;
	virtual void Clean() override {}
	virtual void Update(float dt) override;

	virtual void AnimationState() override;

	virtual bool Attack(float dt) {
		if (!m_IsAttacking && m_CanAttack) {
			m_IsAttacking = true;
			m_CanAttack = false;
		}
		
		return true;
	}

	Transform* getTransform() {
		return m_Transform;
	}

	void AttackHandler();
	void DyingHandler();

	virtual void receiveDamage(const std::string& attackType, int damage) {}

	//int setHealth(int health) { m_Health = health; }
	//void getDamage() override {m_Damage = damage; }

	virtual Collider* AttackZone(float dt) override {
		return nullptr;
	}


	virtual bool isAlive() override {
		return true;
	}

	virtual void Follow_Warrior(Vector2D F){}

	virtual Vector2D getPosition() override {
		return m_Position;
	}
private:
	Animation* m_Animation;
	RigidBody* m_RigidBody;
	Vector2D m_Position;

	int m_AttackBeginTime;
	
};

