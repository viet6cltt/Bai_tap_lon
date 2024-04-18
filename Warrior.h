
#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Vector2D.h"
#include "Collider.h"
#include "Skill_Hasagi.h"
#include "FontManager.h"
#include "SpecialAbiliyState.h"


#define RUN_FORCE 2.5f

class Warrior : public Character
{
public:

	Warrior(Properties* props);
	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);

	void LoadSound();
	void Warrior_VoiceHanlder();

	int getHealth() { return m_Health; }
	int getmaxHealth() { return m_maxHealth; }
	//get Damage
	int getDamage() {
		return m_Damage;
	}
	int getGravitySkillDamage() {
		return m_GravityDamage;
	}

	int getSlashSkillDamage() {
		return m_SlashDamage;
	}

	int setHealth(int health) { m_Health = health; }
	int setDamage(int damage) { m_Damage = damage; }

	bool canUseHasage() {
		return m_CanUseHasagi;
	}
	void setisSkill_Hasagi(bool k) {
		if (m_CanUseHasagi) {
			m_isSkill_Hasagi = k;
		}
	}

	Collider* getCollider() { return m_Collider; }
	Collider* AttackZone(float dt);
	Collider* getAttackZone() {
		return m_attackCollider;
	}
	Collider* getGravityZone() {
		return m_GravitySkillCollider;
	}
	Skill_Hasagi* getHasagiSkill() {
		return m_skill_Hasagi;
	}
	Collider* getSlashZone() {
		return m_SlashSkillCollider;
	}
	void receiveDamage(int damage){
		if (!m_IsAttacking) {
			m_IsHurt = true;
			m_FinishHurt = false;
		}
		m_Health -= damage;
	}

	virtual Vector2D getPosition() override
	{
		//printf("toa do cua nhan vat: %f %f\n", m_Position.X, m_Position.Y);
		m_Position.X = m_Origin->X;
		m_Position.Y = m_Origin->Y;
		return m_Position;
	}
	
	void HealingSkill() {
		m_Health += 90;
		if (m_Health > m_maxHealth) {
			m_Health = m_maxHealth;
		}
	}

	void HealingSkillHandler();
	void GravitySkillHandler();
	void SlashSkillHandler();
	void HasagiSkillHandler(float dt);
	void SlideSkillHandler();

	bool isAlive() const { return m_Health > 0; }
private:
	void AnimationState();
private:
	bool m_IsRunning;
	bool m_isSkill_Hasagi;
	bool m_IsHurt;
	bool m_FinishHurt;
	bool m_IsAttacking;
	bool m_IsCrouching;
	bool m_CanAttack;
	bool m_hasDealtDamage;
	bool m_FinishAttack;

	bool m_skill_Dao_Pha_Thien_Mon;

	float m_AttackTime;

	Vector2D m_Position;
	Vector2D m_SkillDirection;

	Collider* m_attackCollider;
	Collider* m_Collider;
	Vector2D m_LastSafePosition;
	Animation* m_Animation;
	
	RigidBody* m_RigidBody;

	int m_Health;
	int m_maxHealth;
	int m_Damage;

	SDL_Rect m_Rect;
	SDL_Point* center;
	Vector2D force;

	Skill_Hasagi* m_skill_Hasagi;

	std::string m_LastState;
	// slide skill
	int m_SlideCooldown;
	bool m_CanSlide;
	int m_CurrentSlideCooldown;
	bool m_IsSlide;
	int m_SlideBeginTime;
	int m_SlideCount;
	Animation* m_SlideIconAnimation;
	//healing skill
	int m_HealingCooldown;
	int m_CurrentHealingCooldown;
	bool m_IsHealing;
	int m_HealingBeginTime;
	int m_HealingTimeBefore;
	Animation* m_HealingIconAnimation;
	//gravity skill
	bool m_IsGravitySkill;//kiem soat viec gay damage, collider
	bool m_CanUseGravity; //kiem soat viec co dung duoc skill khong
	Collider* m_GravitySkillCollider;
	bool m_GravitySKillBegin;
	int m_GravityCooldown;
	int m_CurrentGravityCooldown;
	int m_GravityBeginTime;
	int m_GravityDamage;
	Animation* m_GravitySkillAnimation;
	Animation* m_GravityIconAnimation;
	//hasagi skill
	bool m_CanUseHasagi;
	int m_HasagiCooldown;
	int m_CurrentHasagiCooldown;
	int m_HasagiBeginTime;
	Animation* m_HasagiIconAnimation;
	//bigslash skill
	bool m_IsSlashSkill;//kiem soat viec gay damage, collider
	bool m_CanUseSlash; //kiem soat viec co dung duoc skill khong
	Collider* m_SlashSkillCollider;
	bool m_SlashSkillBegin;
	int m_SlashCooldown;
	int m_CurrentSlashCooldown;
	int m_SlashBeginTime;
	int m_SlashDamage;
	Animation* m_SlashSkillAnimation;
	Animation* m_SlashIconAnimation;
	//sound
	bool m_IsSoundPlay;

};

#endif

