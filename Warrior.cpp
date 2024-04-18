#include "Warrior.h"
#include "TextureManager.h"
#include "Character.h"
#include "Input.h"
#include <SDL.h>
#include "CollisionHandler.h"
#include<iostream>
//#include "Camera.h"
#include "Engine.h"
#include "SoundManager.h"

Warrior::Warrior(Properties* props) : Character(props)
{
	m_maxHealth = 2000;
	m_Health = 2000;
	m_Damage = 100;

	m_IsRunning = false;
	m_CanAttack = true;
	m_IsAttacking = false;
	m_IsCrouching = false;
	m_IsHurt = false;
	center = new SDL_Point;
	center->x = 56;
	center->y = m_Height / 2;
	m_IsSoundPlay = false;
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
	m_GravityCooldown = 25;
	m_GravityDamage = 7;
	m_HasagiCooldown = 15;
	m_CanUseGravity = true;
	m_CanUseHasagi = true;
	m_SlashCooldown = 20;
	m_SlashDamage = 15;
	m_CanUseSlash = true;

	m_SlideCooldown = 2;
	m_CurrentSlideCooldown = 0;
	m_CanSlide = true;
	m_SlideCount = 0;

	TextureManager::GetInstance()->Load("slideicon", "assets\\slide.png");
	TextureManager::GetInstance()->Load("cd_slideicon", "assets\\slide_cooldown.png"); 
	TextureManager::GetInstance()->Load("slash_icon", "assets\\slash_icon.png");
	TextureManager::GetInstance()->Load("cd_slash_icon", "assets\\cd_slash_icon.png");
	TextureManager::GetInstance()->Load("hasagi_icon", "assets\\hasagi_icon.png");
	TextureManager::GetInstance()->Load("cd_hasagi_icon", "assets\\cd_hasagi_icon.png");
	TextureManager::GetInstance()->Load("gravity_icon", "assets\\gravity_icon.png");
	TextureManager::GetInstance()->Load("cd_gravity_icon", "assets\\cd_gravity_icon.png"); 
	TextureManager::GetInstance()->Load("healing_icon", "assets\\healing_icon.png");
	TextureManager::GetInstance()->Load("cd_healing_icon", "assets\\cd_healing_icon.png");


	m_SlideIconAnimation = new Animation();
	m_HasagiIconAnimation = new Animation();
	m_GravityIconAnimation = new Animation();
	m_HealingIconAnimation = new Animation();
	m_HealingIconAnimation->SetProps("healing_icon", 1, 6, 100, 6);
	m_SlashIconAnimation = new Animation();
	
	FontManager::GetInstance()->LoadFont("healingskill_cooldown", "assets\\ExpressionPro.ttf", 25);
	FontManager::GetInstance()->LoadFont("gravityskill_cooldown", "assets\\ExpressionPro.ttf", 25);
	FontManager::GetInstance()->LoadFont("hasagiskill_cooldown", "assets\\ExpressionPro.ttf", 25);
	FontManager::GetInstance()->LoadFont("slashskill_cooldown", "assets\\ExpressionPro.ttf", 25);
	FontManager::GetInstance()->LoadFont("slideskill_cooldown", "assets\\ExpressionPro.ttf", 25);
	LoadSound();
	
}

void Warrior::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip,center);
	if (m_GravitySkillAnimation != NULL) {
		m_GravitySkillAnimation->Draw(m_Transform->X-100, m_Transform->Y-80, 288, 240);
	}

	if (m_SlashSkillAnimation != NULL) {
		m_SlashSkillAnimation->Draw(m_Transform->X - 100, m_Transform->Y - 80, 1024 / 4, 216, m_Flip);
	}

	if (m_skill_Hasagi != NULL) {
		m_skill_Hasagi->Draw();
	}
	
	//Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect box = m_Collider->Get();
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
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);

	//skill icon
	/*if(m_CanUseSlash) TextureManager::GetInstance()->Draw("slashicon", 284, 30, 48, 48);
	else TextureManager::GetInstance()->Draw("cd_slashicon", 284, 30, 48, 48);
	if(m_IsHealing) TextureManager::GetInstance()->Draw("cd_healingicon", 353, 30, 48, 48);
	else TextureManager::GetInstance()->Draw("healingicon", 353, 30, 48, 48);
	if(m_CanUseGravity) TextureManager::GetInstance()->Draw("gravityicon", 421, 30, 48, 48);
	else TextureManager::GetInstance()->Draw("cd_gravityicon", 421, 30, 48, 48);
	TextureManager::GetInstance()->Draw("u_key", 275, 604, 32, 32);
	if(m_CanUseHasagi) TextureManager::GetInstance()->Draw("hasagiicon", 489, 30, 48, 48);
	else TextureManager::GetInstance()->Draw("cd_hasagiicon", 489, 30, 48, 48);*/
	if (m_SlideIconAnimation != NULL)
	{
		m_SlideIconAnimation->Draw(550, 17, 72, 72);
	}
	if (m_HealingIconAnimation != NULL) {
		m_HealingIconAnimation->Draw(353, 17, 72, 72);
	}
	if (m_GravityIconAnimation != NULL) {
		m_GravityIconAnimation->Draw(421, 17, 72, 72);
	}
	if (m_SlashIconAnimation != NULL) {
		m_SlashIconAnimation->Draw(284, 17, 72, 72);
	}
	if (m_HasagiIconAnimation != NULL) {
		m_HasagiIconAnimation->Draw(489, 17, 72, 72);
	}

	//slide cooldown font
	if (m_CurrentSlideCooldown == 0) {
		FontManager::GetInstance()->RenderText("slideskill_cooldown", "READY", 550 + 12 - 10, 5, { 255,255,255,255 });
	}
	else {
		FontManager::GetInstance()->RenderText("slideskill_cooldown", std::to_string(m_SlideCooldown - m_CurrentSlideCooldown).c_str(), 550 + 12 + 15, 5, { 255,255,255,255 });
	}
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
	std::cout << m_SlashIconAnimation->getSpriteFrame() << std::endl;
	//m_Health -= dt;
	//printf("mau: %d\n", m_Health);
	Warrior_VoiceHanlder();

	if (isAlive() == false) {
		Clean();
	}
	
	m_IsRunning = false;
	m_IsCrouching = false;

	force = (0, 0);
	m_RigidBody->UnSetForce();

	/*-----xu li tan cong-------------------*/
	
	/*----------------------------------------------*/

	/*---------------------------xu li di chuyen-------------------------------------*/
	
	
	if (!m_IsAttacking) {
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

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J) && !m_IsAttacking && !m_IsSlide) {
		SoundManager::GetInstance()->PlaySound("swordslash_sfx", 0, 7);
		m_FinishAttack = false;
		m_IsRunning = false;
		m_IsAttacking = true;
		m_CanAttack = false;
		m_hasDealtDamage = false;
	}
	if (m_IsAttacking && m_Animation->getSpriteFrame() == 32 && m_FinishAttack == false) {
		m_FinishAttack = true;
	}
	if (m_IsAttacking && m_Animation->getSpriteFrame() != 32 && m_FinishAttack) {
		//std::cout << m_Animation->getSpriteFrame();
		m_IsAttacking = false;
		m_CanAttack = true;
		Mix_HaltChannel(7);
	}
	AttackZone(dt);


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
	/*---------------------xu li slide---------------------------*/
	SlideSkillHandler();
	/*-------------------------------------------------------------------------------------*/
	//move on X axis

	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->Position().X;
	if (m_Flip == SDL_FLIP_NONE) {
		m_Collider->SetBuffer(-50, -60, 90, 70);
	}
	else {
		m_Collider->SetBuffer(-40, -60, 90, 70);
	}
	m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Width);
	
	
	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->X = m_LastSafePosition.X;
		m_RigidBody->SetVelocity(0, m_RigidBody->Velocity().Y);
	}
	//move on Y axis

	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->Position().Y;
	
	if (m_Flip == SDL_FLIP_NONE) {
		m_Collider->SetBuffer(-50, -60, 90, 70);
	}
	else {
		m_Collider->SetBuffer(-40, -60, 90, 70);
	}
	
	m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Width);
	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->Y = m_LastSafePosition.Y;
		m_RigidBody->SetVelocity(m_RigidBody->Velocity().X, 0);
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
	//Hasagiskill
	HasagiSkillHandler(dt);
	

	/*--------xu li animation ---------*/
	AnimationState();
	m_Animation->Update();
	if (m_GravitySkillAnimation != NULL) {
		m_GravitySkillAnimation->Update();
	}
	if (m_SlashSkillAnimation != NULL) {
		m_SlashSkillAnimation->Update();
	}
	m_SlideIconAnimation->Update();
	m_HasagiIconAnimation->Update();
	m_GravityIconAnimation->Update();
	m_SlashIconAnimation->Update();
	m_HealingIconAnimation->Update();
}


Collider* Warrior::AttackZone(float dt)
{
	if (m_IsAttacking && m_Animation->getSpriteFrame() >= 11 && m_Animation->getSpriteFrame() <= 14) {
		if (m_attackCollider == NULL) {
			m_attackCollider = new Collider();
			
		}
		if (m_Flip == SDL_FLIP_NONE) {
			
			m_attackCollider->SetBuffer(-40, -40, 50, 55);
			m_attackCollider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
		}
		else {
			
			m_attackCollider->SetBuffer(-10, -40, 50, 55);
			m_attackCollider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
		}
	}
	if (m_IsAttacking && m_Animation->getSpriteFrame() == 15) {
		if (m_attackCollider != NULL) {
			delete m_attackCollider;
			m_attackCollider = NULL;
		}
	}
	if (m_IsAttacking && m_Animation->getSpriteFrame() >= 18 && m_Animation->getSpriteFrame() <= 22) {
		if (m_attackCollider == NULL) {
			m_attackCollider = new Collider();

		}
		if (m_Flip == SDL_FLIP_NONE) {

			m_attackCollider->SetBuffer(-40, -30, 40, 45);
			m_attackCollider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
		}
		else {
			m_attackCollider->SetBuffer(-10, -30, 40, 45);
			m_attackCollider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
		}
	}
	if (m_IsAttacking && m_Animation->getSpriteFrame() == 23) {
		if (m_attackCollider != NULL) {
			delete m_attackCollider;
			m_attackCollider = NULL;
		}
	}
	if (m_IsAttacking && m_Animation->getSpriteFrame() >= 24 && m_Animation->getSpriteFrame() <= 28) {
		if (m_attackCollider == NULL) {
			m_attackCollider = new Collider();

		}
		if (m_Flip == SDL_FLIP_NONE) {

			m_attackCollider->SetBuffer(-30, -60, 30, 90);
			m_attackCollider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
		}
		else {
			m_attackCollider->SetBuffer(0, -60, 30, 90);
			m_attackCollider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
		}
	}
	if (m_IsAttacking && m_Animation->getSpriteFrame() == 29) {
		if (m_attackCollider != NULL) {
			delete m_attackCollider;
			m_attackCollider = NULL;
		}
	}
	if (m_IsAttacking && m_Animation->getSpriteFrame() >= 30 && m_Animation->getSpriteFrame() <= 36) {
		if (m_attackCollider == NULL) {
			m_attackCollider = new Collider();

		}
		if (m_Flip == SDL_FLIP_NONE) {

			m_attackCollider->SetBuffer(-30, -10, 30, 25);
			m_attackCollider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
		}
		else {
			m_attackCollider->SetBuffer(0, -10, 30, 25);
			m_attackCollider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
		}
	}
	if (m_IsAttacking && m_Animation->getSpriteFrame() == 37) {
		if (m_attackCollider != NULL) {
			delete m_attackCollider;
			m_attackCollider = NULL;
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
			//m_Animation->SetProps("player", 1, 9, 120, 9);
			m_Animation->SetProps("player_idle", 1, 14, 120, 14);
			m_Animation->Start();
		}
	}

	//running
	if (m_IsRunning && !m_IsAttacking && !m_IsHurt) {
		currentState = "running";
		if (currentState != m_LastState) {
			//m_Animation->SetProps("player", 2, 6, 120, 6);
			m_Animation->SetProps("player_running", 1, 6, 120, 6);
			m_Animation->Start();
		}
	}
	
	//attacking
	if (m_IsAttacking) {
		//std::cout << m_Animation->getSpriteFrame() << std::endl;
		currentState = "attacking";
		if (currentState != m_LastState) {
			//m_Animation->SetProps("player", 3, 12, 30, 12);
			m_Animation->SetProps("player_attacking", 1, 38, 40, 38);
			m_Animation->Start();
		}
	}

	//hurting
	if (m_IsHurt && !m_IsRunning && !m_IsAttacking) {
		currentState = "hurt";
		if (currentState != m_LastState) {
			//m_Animation->SetProps("player", 4, 5, 120, 5);
			m_Animation->Start();
		}
	}
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
			m_SlashSkillAnimation->SetProps("slashskill", 1, 4, 120, 4);
			m_SlashSkillAnimation->Start();
			m_SlashSkillBegin = false;
		}
	}
	if (m_IsSlide) {
		//m_Animation->SetProps("player", 2, 6, 120, 6);
		m_Animation->SetProps("player_running", 1, 6, 120, 6);
		m_Animation->Start();
	}
	m_LastState = currentState;
	
	if (m_CanSlide) {
		m_SlideIconAnimation->SetProps("slideicon", 1, 4, 100, 4);
	}
	else {
		m_SlideIconAnimation->SetProps("cd_slideicon", 1, 4, 100, 4);
	}
	if (m_CanUseGravity) {
		m_GravityIconAnimation->SetProps("gravity_icon", 1, 6, 100, 6);
	}
	else {
		m_GravityIconAnimation->SetProps("cd_gravity_icon", 1, 6, 100, 6);
	}
	if (m_CanUseHasagi) {
		m_HasagiIconAnimation->SetProps("hasagi_icon", 1, 3, 100, 3);
	}
	else {
		m_HasagiIconAnimation->SetProps("cd_hasagi_icon", 1, 3, 100, 3);
	}
	if (m_CanUseSlash) {
		m_SlashIconAnimation->SetProps("slash_icon", 1, 4, 100, 4);
	}
	else {
		m_SlashIconAnimation->SetProps("cd_slash_icon", 1, 4, 100, 4);
	}
}

void Warrior::Clean()
{
	TextureManager::GetInstance()->Clean();
}

void Warrior::HealingSkillHandler() {
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_E) && m_IsHealing == false) {
		SoundManager::GetInstance()->PlaySound("healing_sfx", 0, 4);
		m_HealingIconAnimation->SetProps("cd_healing_icon", 1, 6, 100, 6);
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
		m_HealingIconAnimation->SetProps("healing_icon", 1, 6, 100, 6);
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
		SoundManager::GetInstance()->PlaySound("gravity_voice", 0, 3);
		SoundManager::GetInstance()->PlaySound("gravity_sfx", -1, 2);
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
		Mix_HaltChannel(2);
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
		SoundManager::GetInstance()->PlaySound("slash_sfx", -1, 5);
		SoundManager::GetInstance()->PlaySound("slash_voice", 0, 6);
		
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
		Mix_HaltChannel(5);
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

void Warrior::HasagiSkillHandler(float dt) {
	if (m_isSkill_Hasagi && m_CanUseHasagi) {
		m_skill_Hasagi = new Skill_Hasagi(new Properties("skill_1", m_Transform->X + 40, m_Transform->Y, 64, 64), m_Damage);
		m_skill_Hasagi->setDamage(m_Damage);
		m_skill_Hasagi->Activate(m_Position, Engine::GetInstance()->getMouse());
		m_CanUseHasagi = false;
		m_isSkill_Hasagi = false;
		m_HasagiBeginTime = SDL_GetTicks();
		SoundManager::GetInstance()->PlaySound("hasagi_sfx", 0, 0);
		SoundManager::GetInstance()->PlaySound("hasagi_voice", 0, 1);

	}
	if (!m_CanUseHasagi) {
		m_CurrentHasagiCooldown = (SDL_GetTicks() - m_HasagiBeginTime) / 1000;

	}
	if (m_CurrentHasagiCooldown >= m_HasagiCooldown) {
		m_CurrentHasagiCooldown = 0;
		m_CanUseHasagi = true;
	}
	if (m_skill_Hasagi != NULL) {
		if (m_skill_Hasagi->IsDeleted()) {
			Mix_HaltChannel(2);
			delete m_skill_Hasagi;
			m_skill_Hasagi = NULL;
		}
		else {
			m_skill_Hasagi->Update(dt);
		}
	}
}

void Warrior::SlideSkillHandler() {
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K) && m_CanSlide) {
		Mix_HaltChannel(7);
		m_IsSlide = true;
		m_SlideBeginTime = SDL_GetTicks();
		m_CanSlide = false;
		m_CurrentSlideCooldown = 0;
		m_SlideCount = 0;
		m_IsAttacking = false;
	}

	if (m_CanSlide == false) {
		m_CurrentSlideCooldown = (SDL_GetTicks() - m_SlideBeginTime) / 1000;
	}
	if (m_SlideCount < 7) {
		m_SlideCount++;
	}
	else if (m_SlideCount == 7) {
		m_IsSlide = false;
	}
	if (m_IsSlide) {
		m_RigidBody->ApplyForce(force * 6);
	}
	if (m_CurrentSlideCooldown >= m_SlideCooldown) {
		m_CanSlide = true;
		m_CurrentSlideCooldown = 0;
	}
}

void Warrior::LoadSound() {
	SoundManager::GetInstance()->Load("hasagi_sfx", "assets\\Hasagi_sfx.mp3", SOUND_SFX, 50);
	SoundManager::GetInstance()->Load("hasagi_voice", "assets\\Hasagi_voice.mp3", SOUND_SFX);
	SoundManager::GetInstance()->Load("gravity_voice", "assets\\Gravity_voice.mp3", SOUND_SFX, 50);
	SoundManager::GetInstance()->Load("gravity_sfx", "assets\\Gravity_sfx.mp3", SOUND_SFX, 100);
	SoundManager::GetInstance()->Load("healing_sfx", "assets\\Healing_sfx.mp3", SOUND_SFX, 100);
	SoundManager::GetInstance()->Load("slash_voice", "assets\\Slash_voice.mp3", SOUND_SFX, 50);
	SoundManager::GetInstance()->Load("slash_sfx", "assets\\Slash_sfx.mp3", SOUND_SFX);
	SoundManager::GetInstance()->Load("swordslash_sfx", "assets\\Swordslash_sfx.mp3", SOUND_SFX);
	SoundManager::GetInstance()->Load("player_voice1", "assets\\player_voice1.mp3", SOUND_SFX);
	SoundManager::GetInstance()->Load("player_voice2", "assets\\player_voice2.mp3", SOUND_SFX);
	SoundManager::GetInstance()->Load("player_voice3", "assets\\player_voice3.mp3", SOUND_SFX);
	SoundManager::GetInstance()->Load("player_voice4", "assets\\player_voice4.mp3", SOUND_SFX);
}

void Warrior::Warrior_VoiceHanlder() {
	if (!m_IsAttacking && !m_IsGravitySkill && !m_IsHurt && !m_IsHealing && !m_IsSlashSkill && m_skill_Hasagi == NULL) {
		int randomNum = rand() % 4 + 1;
		if ((SDL_GetTicks() / 1000) % 15 == 0 && m_IsSoundPlay == false) {
			switch (randomNum) {
			case 1: SoundManager::GetInstance()->PlaySound("player_voice1", 0, 8); break;
			case 2: SoundManager::GetInstance()->PlaySound("player_voice2", 0, 9); break;
			case 3: SoundManager::GetInstance()->PlaySound("player_voice3", 0, 10); break;
			case 4: SoundManager::GetInstance()->PlaySound("player_voice4", 0, 11); break;
			}
			m_IsSoundPlay = true;
		}
		if (m_IsSoundPlay == true && (SDL_GetTicks() / 1000) % 10 == 1) {
			m_IsSoundPlay = false;
			
		}

	}
}


