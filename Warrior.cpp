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
	m_Damage = 40;

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

	
	FontManager::GetInstance()->LoadFont("healingskill_cooldown", "assets\\ExpressionPro.ttf", 30);

}

void Warrior::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip,center);
	//Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect box = m_Collider->Get();
	if (m_attackCollider != NULL){
		SDL_Rect box1 = m_attackCollider->Get();
		SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box1);
	}
	if (m_skill_Hasagi != NULL) {
		m_skill_Hasagi->Draw();
	}
	
	//box.x -= cam.X;
	//box.y -= cam.Y;
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);

	//skill
	TextureManager::GetInstance()->Draw("healing", 30, 540, 96, 96);
	if (m_CurrentHealingCooldown == 0) {
		FontManager::GetInstance()->RenderText("healingskill_cooldown","READY", 40, 510, {255,255,255,255});
	}else FontManager::GetInstance()->RenderText("healingskill_cooldown", std::to_string(m_HealingCooldown - m_CurrentHealingCooldown).c_str(), 70, 510, { 255,255,255,255 });
}


void Warrior::Update(float dt)
{
	std::cout << "mau:" << m_Health << std::endl;
	//m_Health -= dt;
	//printf("mau: %d\n", m_Health);
	if (isAlive() == false) {
		Clean();
	}
	
	m_IsRunning = false;
	m_IsCrouching = false;

	m_RigidBody->UnSetForce();

	/*-----xu li tan cong-------------------*/
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J)&&!m_IsAttacking && m_CanAttack) {
		m_FinishAttack = false;
		m_IsRunning = false;
		m_IsAttacking = true;
		m_CanAttack = false; 
		m_hasDealtDamage = false;
	}
	if (m_IsAttacking) {
		m_RigidBody->UnSetForce();
	}
	if (m_IsAttacking && m_Animation->getSpriteFrame() == 11 && m_FinishAttack == false) {
		m_FinishAttack = true;
	}
	if (m_IsAttacking && m_Animation->getSpriteFrame() != 11 && m_FinishAttack) {
		std::cout << m_Animation->getSpriteFrame();
		m_IsAttacking = false;
		m_CanAttack = true;
	}
	AttackZone(dt);

	/*----------------------------------------------*/
	

	if (m_isSkill_Hasagi) {
		m_skill_Hasagi = new Skill_Hasagi(new Properties("skill_1", m_Transform->X + 40, m_Transform->Y, 64, 64), m_Damage);
		m_skill_Hasagi->Activate(m_Position, Engine::GetInstance()->getMouse());
		std::cout << m_Position.X << " " << m_Position.Y << std::endl;
		//std::cout << Engine::GetInstance()->getMouse().X << " " << Engine::GetInstance()->getMouse().Y << std::endl;
		m_isSkill_Hasagi = false;
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
		if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD) {
			m_RigidBody->ApplyForceX(FORWARD * RUN_FORCE);
			m_Flip = SDL_FLIP_NONE;
			m_IsRunning = true;
		}
		if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD) {
			m_RigidBody->ApplyForceX(BACKWARD * RUN_FORCE);
			m_Flip = SDL_FLIP_HORIZONTAL;
			m_IsRunning = true;
		}

		if (Input::GetInstance()->GetAxisKey(VERTICAL) == UPWARD)
		{
			m_RigidBody->ApplyForceY(UPWARD * RUN_FORCE);
			//m_Flip = SDL_FLIP_NONE;
			m_IsRunning = true;
		}
		if (Input::GetInstance()->GetAxisKey(VERTICAL) == DOWNWARD)
		{
			m_RigidBody->ApplyForceY(DOWNWARD * RUN_FORCE);
			//m_Flip = SDL_FLIP_NONE;
			m_IsRunning = true;
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

	
	AnimationState();

	m_Animation->Update();

	/*--------------xu li skill----------*/
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_U) && m_IsHealing == false) {
		m_IsHealing = true;
		m_HealingBeginTime = SDL_GetTicks();
		m_CurrentHealingCooldown = 0;
		m_HealingTimeBefore = -2;
	}
	if (m_IsHealing) {
		m_CurrentHealingCooldown = (SDL_GetTicks() - m_HealingBeginTime)/1000;
		if ( m_CurrentHealingCooldown <= 5 && m_HealingTimeBefore!= m_CurrentHealingCooldown) {
			HealingSkill();
			m_HealingTimeBefore = m_CurrentHealingCooldown;
		}
	}
	if (m_CurrentHealingCooldown >= m_HealingCooldown) {
		m_IsHealing = false;
		m_CurrentHealingCooldown = 0;
	}
}


Collider* Warrior::AttackZone(float dt)
{
	if (m_IsAttacking && m_Animation->getSpriteFrame() >= 10 && m_Animation->getSpriteFrame() <= 11) {
		if (m_attackCollider == NULL) {
			m_attackCollider = new Collider();
			
		}
		if (m_Flip == SDL_FLIP_NONE) {
			std::cout << "da chinh";
			m_attackCollider->SetBuffer(-30, -10, 30, 25);
			m_attackCollider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
		}
		else {
			std::cout << "da chinh";
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
		std::cout << m_Animation->getSpriteFrame() << std::endl;
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
	m_LastState = currentState;
	//if (m_skill_Dao_Pha_Thien_Mon) m_Animation->SetProps("skillDao_Pha_Thien_Mon", 1, 4, 100, 4);
}


void Warrior::Clean()
{
	TextureManager::GetInstance()->Clean();
}



