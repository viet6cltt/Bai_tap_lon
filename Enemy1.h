#pragma once
#include "Enemy.h"
#include "HealthBar.h"

#define RUN_FORCE 0.8f

class Enemy1 : public Enemy
{
public:
	Enemy1(Properties* props);
	virtual void Draw() override;
	virtual void Clean() override;
	virtual void Update(float dt) override;

	virtual void AnimationState() override;

	//int setHealth(int health) { m_Health = health; }
	//void getDamage() override {m_Damage = damage; }
	

	virtual Collider* AttackZone(float dt) override;

	virtual bool isAlive() override { return m_Health > 0; }

	virtual void Follow_Warrior(Vector2D F);

	virtual Vector2D getPosition() override {
		return m_Position;
	}


private:

	HealthBar* m_HealthBar;
	Vector2D m_LastSafePosition;
	Animation* m_Animation;
	RigidBody* m_RigidBody;

	Vector2D m_Position;

	SDL_Rect m_Rect;
	Vector2D m_FollowDirection;
	Vector2D m_Direction;

	SDL_Point* center;

	std::string m_LastState;
};

