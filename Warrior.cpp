#include "Warrior.h"
#include "TextureManager.h"
#include "Character.h"
#include "Input.h"
#include <SDL.h>
#include "CollisionHandler.h"
#include<iostream>
//#include "Camera.h"
#include "Engine.h"


Warrior::Warrior(Properties* props) : Character(props)
{
	m_maxHealth = 1000;
	m_Health = 500;
	m_Damage = 100;

	m_IsRunning = false;
	m_CanAttack = true;
	m_IsAttacking = false;
	m_IsCrouching = false;
	m_IsHurt = false;
	center = new SDL_Point;
	center->x = 56;
	center->y = m_Height / 2;

	m_Flip = SDL_FLIP_NONE;

	m_skill_Dao_Pha_Thien_Mon = false;
	m_FinishAttack = false;
	

	m_Collider = new Collider();
	
	//m_Collider->SetBuffer(-45, -40, 45, 40);

	m_RigidBody = new RigidBody();

	m_Animation = new Animation();

	//m_attackCollider = new Collider();
	m_isSkill_Hasagi = false;
	m_attackCollider = NULL;

	m_HealingCooldown = 10;
	m_CurrentHealingCooldown = 0;
	m_GravityCooldown = 20;
	m_GravityDamage = 2;
	m_HasagiCooldown = 15;
	m_CanUseGravity = true;
	m_CanUseHasagi = true;
	m_SlashCooldown = 6;
	m_SlashDamage = 1;
	m_CanUseSlash = true;

	
	FontManager::GetInstance()->LoadFont("healingskill_cooldown", "assets\\ExpressionPro.ttf", 25);
	FontManager::GetInstance()->LoadFont("gravityskill_cooldown", "assets\\ExpressionPro.ttf", 25);
	FontManager::GetInstance()->LoadFont("hasagiskill_cooldown", "assets\\ExpressionPro.ttf", 25);
	FontManager::GetInstance()->LoadFont("slashskill_cooldown", "assets\\ExpressionPro.ttf", 25);
}

void Warrior::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip,center);
	if (m_GravitySkillAnimation != NULL) {
		m_GravitySkillAnimation->Draw(m_Transform->X-100, m_Transform->Y-80, 288, 240);
	}

	if (m_SlashSkillAnimation != NULL) {
		std::cout<< m_SlashSkillAnimation->getSpriteFrame() << std::endl;
		std::cout << "da ve";
		m_SlashSkillAnimation->Draw(m_Transform->X - 100, m_Transform->Y - 80, 1024 / 4, 216, m_Flip);
		
	}

	if (m_skill_Hasagi != NULL) {
		m_skill_Hasagi->Draw();
	}
	
	//Vector2D cam = Camera::GetInstance()->GetPosition();
	//SDL_Rect box = m_Collider->Get();
	//attack box
	if (m_attackCollider != NULL){
		SDL_Rect attackbox = m_attackCollider->Get();
		SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &attackbox);
	}
	//gravity box
	if (m_GravitySkillCollider != NULL) {
		SDL_Rect gravitybox = m_GravitySkillCollider->Get();
		//SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &gravitybox);
	}
	//slash box
	if (m_SlashSkillCollider != NULL) {
		SDL_Rect slashbox = m_SlashSkillCollider->Get();
		SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &slashbox);
	}

	
	
	//box.x -= cam.X;
	//box.y -= cam.Y;
	//SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);

	//skill
	if(m_CanUseSlash) TextureManager::GetInstance()->Draw("slashicon", 284, 30, 48, 48);
	else TextureManager::GetInstance()->Draw("cd_slashicon", 284, 30, 48, 48);
	if(m_IsHealing) TextureManager::GetInstance()->Draw("cd_healingicon", 353, 30, 48, 48);
	else TextureManager::GetInstance()->Draw("healingicon", 353, 30, 48, 48);
	if(m_CanUseGravity) TextureManager::GetInstance()->Draw("gravityicon", 421, 30, 48, 48);
	else TextureManager::GetInstance()->Draw("cd_gravityicon", 421, 30, 48, 48);
	TextureManager::GetInstance()->Draw("u_key", 275, 604, 32, 32);
	if(m_CanUseHasagi) TextureManager::GetInstance()->Draw("hasagiicon", 489, 30, 48, 48);
	else TextureManager::GetInstance()->Draw("cd_hasagiicon", 489, 30, 48, 48);
	//healing cooldown font
	if (m_CurrentHealingCooldown == 0) {
		FontManager::GetInstance()->RenderText("healingskill_cooldown","READY", 353 - 10, 5, {255,255,255,255});
	}else FontManager::GetInstance()->RenderText("healingskill_cooldown", std::to_string(m_HealingCooldown - m_CurrentHealingCooldown).c_str(), 353 + 15, 5, { 255,255,255,255 });
	//gravity cooldown font
	if (m_CurrentGravityCooldown == 0) {
		FontManager::GetInstance()->RenderText("gravityskill_cooldown", "READY", 421 - 10, 5, { 255,255,255,255 });
	}
	else FontManager::GetInstance()->RenderText("gravityskill_cooldown", std::to_string(m_GravityCooldown - m_CurrentGravityCooldown).c_str(), 421 + 15, 5, { 255,255,255,255 });
	//hasagi cooldown font
	if (m_CurrentHasagiCooldown == 0) {
		FontManager::GetInstance()->RenderText("hasagiskill_cooldown", "READY", 489 - 10, 5, { 255,255,255,255 });
	}
	else FontManager::GetInstance()->RenderText("hasagiskill_cooldown", std::to_string(m_HasagiCooldown - m_CurrentHasagiCooldown).c_str(), 489 + 15, 5, { 255,255,255,255 });
	//slash cooldown font
	if (m_CurrentSlashCooldown == 0) {
		FontManager::GetInstance()->RenderText("slashskill_cooldown", "READY", 284 - 10, 5, { 255,255,255,255 });
	}
	else FontManager::GetInstance()->RenderText("slashskill_cooldown", std::to_string(m_SlashCooldown - m_CurrentSlashCooldown).c_str(), 284 + 15, 5, { 255,255,255,255 });
}


void Warrior::Update(float dt)
{
	//std::cout << "v theo x: "<<m_RigidBody->Veclocity().X <<"    v theo y:  "<< m_RigidBody->Veclocity().Y << std::endl;
	//std::cout << "mau:" << m_Health << std::endl;
	//m_Health -= dt;
	//printf("mau: %d\n", m_Health);
	if (isAlive() == false) {
		Clean();
	}
	
	m_IsRunning = false;
	m_IsCrouching = false;

	m_RigidBody->UnSetForce();

	/*-----xu li tan cong-------------------*/
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J)&&!m_IsAttacking ) {
		m_FinishAttack = false;
		m_IsRunning = false;
		m_IsAttacking = true;
		m_CanAttack = false; 
		m_hasDealtDamage = false;
	}
	if (m_IsAttacking) {
		m_RigidBody->UnSetForce();
	}
	if (m_IsAttacking && m_Animation->getSpriteFrame() == 11 && m_FinishAttack == false ) {
		m_FinishAttack = true;
	}
	if (m_IsAttacking && m_Animation->getSpriteFrame() != 11 && m_FinishAttack) {
		//std::cout << m_Animation->getSpriteFrame();
		m_IsAttacking = false;
		m_CanAttack = true;
	}
	AttackZone(dt);

	/*----------------------------------------------*/
	

	if (m_isSkill_Hasagi&&m_CanUseHasagi) {
		m_skill_Hasagi = new Skill_Hasagi(new Properties("skill_1", m_Transform->X + 40, m_Transform->Y, 64, 64), m_Damage);
		m_skill_Hasagi->Activate(m_Position, Engine::GetInstance()->getMouse());
		//std::cout << m_Position.X << " " << m_Position.Y << std::endl;
		//std::cout << Engine::GetInstance()->getMouse().X << " " << Engine::GetInstance()->getMouse().Y << std::endl;
		//m_isSkill_Hasagi = false;
		m_CanUseHasagi = false;
		m_isSkill_Hasagi = false;
		m_HasagiBeginTime = SDL_GetTicks();
	}
	if (!m_CanUseHasagi) {
		m_CurrentHasagiCooldown = (SDL_GetTicks() - m_HasagiBeginTime) / 1000;
		std::cout << "-----" << m_CurrentHasagiCooldown;
	}
	if (m_CurrentHasagiCooldown >= m_HasagiCooldown) {
		m_CurrentHasagiCooldown = 0;
		m_CanUseHasagi = true;
	}
	if (m_skill_Hasagi != NULL) {
		if (m_skill_Hasagi->IsDeleted()) {
			delete m_skill_Hasagi;
			m_skill_Hasagi = NULL;
		}
		else {
			m_skill_Hasagi->Update(dt);
		}
	}

	/*---------------------------xu li di chuyen-------------------------------------*/
	if (!m_IsAttacking) {
		Vector2D force;
		if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD) {
			force.X = FORWARD;
			m_Flip = SDL_FLIP_NONE;
			m_IsRunning = true;
		}
		if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD) {
			force.X = BACKWARD;
			m_Flip = SDL_FLIP_HORIZONTAL;
			m_IsRunning = true;
		}

		if (Input::GetInstance()->GetAxisKey(VERTICAL) == UPWARD)
		{
			force.Y = UPWARD;
			//m_Flip = SDL_FLIP_NONE;
			m_IsRunning = true;
		}
		if (Input::GetInstance()->GetAxisKey(VERTICAL) == DOWNWARD)
		{
			force.Y = DOWNWARD;
			//m_Flip = SDL_FLIP_NONE;
			m_IsRunning = true;
		}

		// Chuan hoa vector 
		if (force.Length() > 0) {
			force.Normalize();
			force = force * RUN_FORCE;
			m_RigidBody->ApplyForce(force);
		}
	}

	/*-------------------------------------------------------------------------------------*/

	/*--------------------------xu li bi thuong-----------------------*/
	if (m_IsHurt) {
		m_IsRunning = false;
	}
	if (m_IsHurt && m_Animation->getSpriteFrame() == 4 && m_FinishHurt == false) {
		m_FinishHurt = true;
	}
	if (m_FinishHurt && m_Animation->getSpriteFrame() != 4) {
		m_IsHurt = false;
	}
	/*-------------------------------------------------------------------------------------*/
	//move on X axis

	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->Position().X;
	m_Collider->SetBuffer(-25, -35, 35, 50);
	m_Collider->Set(m_Transform->X, m_Transform->Y, 66 , 80);
	
	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->X = m_LastSafePosition.X;
	}
	//move on Y axis

	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->Position().Y;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 66, 80);
	m_Collider->SetBuffer(-25, -35, 35, 50);
	
	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->Y = m_LastSafePosition.Y;
	}

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	/*--------------xu li skill----------*/
	//healing skill
	HealingSkillHandler();
	//gravityskil
	GravitySkillHandler();
	//slashskill
	SlashSkillHandler();

	/*--------xu li animation ---------*/
	AnimationState();
	m_Animation->Update();
	if (m_GravitySkillAnimation != NULL) {
		m_GravitySkillAnimation->Update();
	}
	if (m_SlashSkillAnimation != NULL) {
		m_SlashSkillAnimation->Update();
	}
}


Collider* Warrior::AttackZone(float dt)
{
	if (m_IsAttacking && m_Animation->getSpriteFrame() >= 10 && m_Animation->getSpriteFrame() <= 11) {
		if (m_attackCollider == NULL) {
			m_attackCollider = new Collider();
			
		}
		if (m_Flip == SDL_FLIP_NONE) {
			//std::cout << "da chinh";
			m_attackCollider->SetBuffer(-30, -10, 30, 25);
			m_attackCollider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
		}
		else {
			//std::cout << "da chinh";
			m_attackCollider->SetBuffer(0, -10, 30, 25);
			m_attackCollider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
		}
	}
	if (!m_IsAttacking) {
		if(m_attackCollider != NULL) {
			delete m_attackCollider;
			m_attackCollider = NULL;
		}
	}
	return m_attackCollider;

}

void Warrior::AnimationState()
{
	std::string currentState;
	
	//idle
	if (!m_IsRunning && !m_IsAttacking && !m_IsHurt) {
		currentState = "idle";
		if (currentState != m_LastState) {
			m_Animation->SetProps("player", 1, 9, 120, 9);
			m_Animation->Start();
		}
	}

	//running
	if (m_IsRunning && !m_IsAttacking && !m_IsHurt) {
		currentState = "running";
		if (currentState != m_LastState) {
			m_Animation->SetProps("player", 2, 6, 120, 6);
			m_Animation->Start();
		}
	}
	
	//attacking
	if (m_IsAttacking) {
		//std::cout << m_Animation->getSpriteFrame() << std::endl;
		currentState = "attacking";
		if (currentState != m_LastState) {
			m_Animation->SetProps("player", 3, 12, 30, 12);
			m_Animation->Start();
		}
	}

	//hurting
	if (m_IsHurt && !m_IsRunning && !m_IsAttacking) {
		currentState = "hurt";
		if (currentState != m_LastState) {
			m_Animation->SetProps("player", 4, 5, 120, 5);
			m_Animation->Start();
		}
	}
	
	//if (m_skill_Dao_Pha_Thien_Mon) m_Animation->SetProps("skillDao_Pha_Thien_Mon", 1, 4, 100, 4);


	if (m_IsGravitySkill)
	{
		if (m_GravitySKillBegin) {
			m_GravitySkillAnimation->SetProps("gravityskill", 1, 20, 150, 4);
			m_GravitySkillAnimation->Start();
			m_GravitySKillBegin = false;
		}
	}

	if (m_IsSlashSkill) {
		if (m_SlashSkillBegin) {
			m_SlashSkillAnimation->SetProps("slashskill", 1, 4, 90, 4);
			m_SlashSkillAnimation->Start();
			m_SlashSkillBegin = false;
		}
	}
	m_LastState = currentState;
}


void Warrior::Clean()
{
	TextureManager::GetInstance()->Clean();
}

void Warrior::HealingSkillHandler() {
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_E) && m_IsHealing == false) {
		m_IsHealing = true;
		m_HealingBeginTime = SDL_GetTicks();
		m_CurrentHealingCooldown = 0;
		m_HealingTimeBefore = -2;
	}
	if (m_IsHealing) {
		m_CurrentHealingCooldown = (SDL_GetTicks() - m_HealingBeginTime) / 1000;
		if (m_CurrentHealingCooldown <= 5 && m_HealingTimeBefore != m_CurrentHealingCooldown) {
			HealingSkill();
			m_HealingTimeBefore = m_CurrentHealingCooldown;
		}
	}
	if (m_CurrentHealingCooldown >= m_HealingCooldown) {
		m_IsHealing = false;
		m_CurrentHealingCooldown = 0;
	}
}

void Warrior::GravitySkillHandler() {
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_I) && m_CanUseGravity) {
		m_CanUseGravity = false;
		m_IsGravitySkill = true;
		m_GravitySkillAnimation = new Animation();
		m_GravitySkillCollider = new Collider();
		m_GravitySKillBegin = true;
		m_CurrentGravityCooldown = 0;
		m_GravityBeginTime = SDL_GetTicks();
	}
	if (!m_CanUseGravity) {
		m_CurrentGravityCooldown = (SDL_GetTicks() - m_GravityBeginTime) / 1000;
		//std::cout << "-----" << m_CurrentGravityCooldown;
	}
	if (m_CurrentGravityCooldown >= m_GravityCooldown) {
		m_CurrentGravityCooldown = 0;
		m_CanUseGravity = true;
	}
	if (m_IsGravitySkill && m_CurrentGravityCooldown > 5) {
		m_IsGravitySkill = false;
		if (m_GravitySkillAnimation != NULL) {
			delete m_GravitySkillAnimation;
			m_GravitySkillAnimation = NULL;
		}
		if (m_GravitySkillCollider != NULL) {
			delete m_GravitySkillCollider;
			m_GravitySkillCollider = NULL;
		}
	}
	else if (m_GravitySkillCollider != NULL) {
		m_GravitySkillCollider->SetBuffer(-20, -20, 40, 40);
		m_GravitySkillCollider->Set(m_Transform->X - 100, m_Transform->Y - 80, 288, 240);
	}
}

void Warrior::SlashSkillHandler() 
{
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_U) && m_CanUseSlash) {
		m_CanUseSlash = false;
		m_IsSlashSkill = true;
		m_SlashSkillAnimation = new Animation();
		m_SlashSkillCollider = new Collider();
		m_SlashSkillBegin = true;
		m_CurrentSlashCooldown = 0;
		m_SlashBeginTime = SDL_GetTicks();
	}
	if (!m_CanUseSlash) {
		m_CurrentSlashCooldown = (SDL_GetTicks() - m_SlashBeginTime) / 1000;
	}
	if (m_CurrentSlashCooldown >= m_SlashCooldown) {
		m_CurrentSlashCooldown = 0;
		m_CanUseSlash = true;
	}
	if (m_IsSlashSkill && m_CurrentSlashCooldown > 1) {
		m_IsSlashSkill = false;
		if (m_SlashSkillAnimation != NULL) {
			delete m_SlashSkillAnimation;
			m_SlashSkillAnimation = NULL;
		}
		
		if (m_SlashSkillCollider != NULL) {
			delete m_SlashSkillCollider;
			m_SlashSkillCollider = NULL;
		}
	}
	else if (m_SlashSkillCollider != NULL) {
		if (m_Flip == SDL_FLIP_NONE) {
			m_SlashSkillCollider->SetBuffer(90, 70, 20, 25);
			m_SlashSkillCollider->Set(m_Transform->X, m_Transform->Y, 256, 216);
		}
		else {
			m_SlashSkillCollider->SetBuffer(70, 70, 20, 25);
			m_SlashSkillCollider->Set(m_Transform->X, m_Transform->Y, 256, 216);
		}
	}

}


