#pragma once
#include "Enemy.h"
#include "HealthBar.h"


#define RUN_FORCE 0.85f

class Enemy_Boss1 : public Enemy
{
public:
	Enemy_Boss1(Properties* props);
	virtual void Draw() override;
	virtual void Clean() override;
	virtual void Update(float dt) override;

	virtual void AnimationState() override;

	
	
	//int setHealth(int health) { m_Health = health; }
	//void getDamage() override {m_Damage = damage; }

	virtual Collider* AttackZone(float dt) override;
	

	virtual bool isAlive() override { 
		if (m_FinishDying) {
			return false;
		}
		return true;
	}

	void DyingHandler();
	virtual void Follow_Warrior(Vector2D F);

	virtual Vector2D getPosition() override {
		return m_Position;
	}

private:

	bool hasFlipped;

	HealthBar* m_HealthBar;

	Vector2D m_LastSafePosition;
	Animation* m_Animation;
	RigidBody* m_RigidBody;

	Vector2D m_Position;

	Vector2D m_attackDirection;
	SDL_Rect m_Rect;
	Vector2D m_FollowDirection;
	Vector2D m_Direction;
	int m_AttackBeginFrames, m_AttackFinishFrames;
	SDL_Point* center;

	std::string m_LastState;

};

