#include "Enemy_Boss1.h"

#include "TextureManager.h"
#include "Character.h"
#include "Input.h"
#include <SDL.h>
#include "CollisionHandler.h"
#include<iostream>
//#include "Camera.h"
#include "Engine.h"

Enemy_Boss1::Enemy_Boss1(Properties* props) : Enemy(props)
{
	m_hasReceivedDamage["normal"] = false;
	m_hasReceivedDamage["slash"] = false;
	m_hasReceivedDamage["gravity"] = false;
	m_hasReceivedDamage["hasagi"] = false;
	m_Health = 7000;
	m_Damage = 400;
	m_IsRunning = false;
	m_AttackBeginFrames = 4;
	m_AttackFinishFrames = 5;
	m_FinishHurt = false;
	m_hasDealtDamage = false;
	hasFlipped = false;
	//Boss1
	TextureManager::GetInstance()->Load("boss1", "assets\\BringerOfDeath\\SpriteSheet\\BringerofDeathSpritSheet.png");
	is_MapUpdated = false;
	m_IsAttacking = false;
	
	m_CanAttack = true;
	m_IsHurt = false;

	m_IsDying = false;
	m_FinishDying = false;

	center = new SDL_Point();
	center->x = 200;
	center->y = 54;

	m_Flip = SDL_FLIP_NONE;

	m_Collider = new Collider();
	m_attackDetectCollider = new Collider();
	//m_Collider->SetBuffer(-45, -40, 45, 40);
	m_attackCollider = NULL;

	m_RigidBody = new RigidBody();
	//m_Position = new Vector2D;

	m_Animation = new Animation();
	m_HealthBar = new HealthBar(new Properties("enemy_bar", m_Transform->X + 70, m_Transform->Y + 43, 29, 5), m_Health);
}

void Enemy_Boss1::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip,NULL);
	//Vector2D cam = Camera::GetInstance()->GetPosition();
	

	if (m_attackCollider != NULL) {
		SDL_Rect box1 = m_attackCollider->Get();
		SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box1);
	}

	//TextureManager::GetInstance()->Draw("enemy_bar", m_Transform->X + 70, m_Transform->Y + 43, 29, 5);
	if (m_HealthBar != NULL) {
		m_HealthBar->Draw();
	}
	SDL_Rect box = m_Collider->Get();
	SDL_Rect box1 = m_attackDetectCollider->Get();
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box1);
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Enemy_Boss1::Update(float dt) {
	
	if (isAlive() == false) {
		Clean();
	}
	/*----------------xu li tan cong--------------------------*/
	if (m_Animation->getSpriteFrame() > m_AttackFinishFrames) {
		if (m_attackCollider != NULL) {
			delete m_attackCollider;
			m_attackCollider = NULL;
		}
	}
	if (m_IsAttacking && m_Animation->getSpriteFrame() == 1 && m_Animation->getSpriteRow() == 4 && m_FinishAttack == false) {
		m_FinishAttack = true;
	}
	
	if (m_IsAttacking && m_Animation->getSpriteFrame() ==0 && m_FinishAttack) {
		m_IsAttacking = false;
		m_CanAttack = true;
		m_hasDealtDamage = false;
		m_FinishAttack = false;
	}
	AttackZone(dt);
	
	//-----------xu li di chuyen------------------------
	m_RigidBody->UnSetForce();	
	if (!m_IsAttacking && !m_IsHurt && !m_IsDying) {
		m_RigidBody->ApplyForce(m_Direction * RUN_FORCE);
	}
	
	/*--------------------------xu li bi thuong-----------------------*/
	if (m_hasReceivedDamage["hasagi"] == true) {
		m_attackDirection.X = -m_attackDirection.X;
		m_attackDirection.Y = -m_attackDirection.Y;
		m_RigidBody->ApplyForce(m_attackDirection * 1);
	}
	if (m_IsHurt) {
		m_RigidBody->UnSetForce();
		m_IsRunning = false;
		
		if (m_IsAttacking) {
			delete m_attackCollider;
			m_attackCollider = NULL;
		}
	}
	if (m_IsHurt && m_Animation->getSpriteFrame() == 5 && !m_FinishHurt) {
		m_FinishHurt = true;
	}
	if (m_FinishHurt && m_Animation->getSpriteFrame() != 5 ) {
		m_IsHurt = false; 
		m_FinishHurt = false;
	}
	/*-------------------------------------------------------*/

	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->Position().X;
	if (m_Flip == SDL_FLIP_NONE) {
		m_Collider->SetBuffer(-160, -80, 200, 80);
		m_attackDetectCollider->SetBuffer(-130, -60, 160, 50);
	}
	else {
		m_Collider->SetBuffer(-40, -80, 200, 80);
		m_attackDetectCollider->SetBuffer(0, -60, 160, 50);
	}
	m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	/*if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->X = m_LastSafePosition.X;
	}*/

	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->Position().Y;
	if (m_Flip == SDL_FLIP_NONE) {
		m_Collider->SetBuffer(-160, -80, 200, 80);
		m_attackDetectCollider->SetBuffer(-130, -55, 140, 30);
	}
	else {
		m_Collider->SetBuffer(-40, -80, 200, 80);
		m_attackDetectCollider->SetBuffer(0, -55, 140, 30);
	}
	m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	m_attackDetectCollider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	/*if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->Y = m_LastSafePosition.Y;
	}*/
	if (m_Health <= 0 && !m_IsDying) {
		m_IsDying = true;
		delete m_HealthBar;
		m_HealthBar = NULL;
	}
	DyingHandler();
	AnimationState();
	if (m_HealthBar != NULL) {
		if (m_Flip == SDL_FLIP_HORIZONTAL) {
			m_HealthBar->setProperties(m_Transform->X + 75, m_Transform->Y + 50, 29, 5);
		}
		else {
			m_HealthBar->setProperties(m_Transform->X + 195, m_Transform->Y + 50, 29, 5);
		}
		
		m_HealthBar->setCurrentHealth(m_Health);
		m_HealthBar->Update(dt);
	}

	m_Animation->Update();
	
}
void Enemy_Boss1::AnimationState()
{
	std::string currentState;
	//idle
	
	if (!m_IsRunning && !m_IsAttacking && !m_IsHurt&&!m_IsDying) {
		currentState = "idle";
		if (currentState != m_LastState) {
			m_Animation->SetProps("boss1", 1, 8, 100, 8);
			m_Animation->Start();
		}
	}

	//running
	
	if (m_IsRunning && !m_IsAttacking && !m_IsHurt && !m_IsDying) {
		currentState = "running";
		if (currentState != m_LastState) {
			if (m_IsRunning) m_Animation->SetProps("boss1", 2, 8, 100, 8);
			m_Animation->Start();
		}
	}
	//attacking
	if (m_IsAttacking && !m_IsHurt && !m_IsRunning && !m_IsDying) {
		currentState = "attacking";
		if (currentState != m_LastState) {
			if (m_IsAttacking) m_Animation->SetProps("boss1", 3, 10, 200, 8);
			m_Animation->Start();
		}
	}
	//hurting	
	if (m_IsHurt && !m_IsAttacking && !m_IsRunning &&!m_IsDying) {
		currentState = "hurt";
		if (currentState != m_LastState) {
			m_Animation->SetProps("boss1", 4, 4, 150, 8, 2);
			m_Animation->Start();
		}
	}
	if (m_IsDying) {
		currentState = "dying";
		if (currentState != m_LastState) {
			m_Animation->SetProps("boss1", 4, 10, 250, 8, 5);
			m_Animation->Start();
		}
	}
	m_LastState = currentState;

}



void Enemy_Boss1::Clean(){
	TextureManager::GetInstance()->Drop("boss_1");
	//TextureManager::GetInstance()->Drop("skeleton_idle");
	//TextureManager::GetInstance()->Drop("skeleton_attack");

}

void Enemy_Boss1::Follow_Warrior(Vector2D F)
{
	
	if (m_Collider != NULL) {
		//std::cout << m_Collider->Get().w << " " << m_Collider->Get().h << std::endl;
		if (!is_MapUpdated) {
			m_PathFinder = new PathFinder(Map::GetInstance()->get_Map(), m_Collider);
			is_MapUpdated = true;
		}
		m_Position.X = m_Collider->Get().x + (float)m_Collider->Get().w / 2;
		m_Position.Y = m_Collider->Get().y + (float)m_Collider->Get().h / 2;

		m_Direction = m_PathFinder->getDirection(m_Collider, F);
		m_attackDirection = F - m_Collider->GetPosition();
		m_attackDirection.Normalize();
	}

	m_IsRunning = true;
	if (F.X - m_Position.X < 0) {
		m_Flip = SDL_FLIP_NONE;
	}
	else if (F.X - m_Position.X > 0) {
		m_Flip = SDL_FLIP_HORIZONTAL;
	}

	if (m_Flip == SDL_FLIP_HORIZONTAL && !hasFlipped)
	{
		m_Transform->X += 2 * center->x - m_Width;
		m_Origin->X = m_Transform->X + m_Width - center->x;
		hasFlipped = true;  // Đánh dấu rằng hình ảnh đã được lật
	}
	else if (m_Flip == SDL_FLIP_NONE && hasFlipped)
	{
		m_Transform->X -= 2 * center->x - m_Width;
		m_Origin->X = m_Transform->X + center->x;
		hasFlipped = false;  // Đặt lại biến khi hình ảnh không được lật
	}
	else if (m_Flip == SDL_FLIP_NONE && !hasFlipped) {
		m_Origin->X = m_Transform->X + center->x;
	}
	else {
		m_Origin->X = m_Transform->X + m_Width - center->x;
	}

	m_Origin->Y = m_Transform->Y + m_Height / 2;


}



Collider* Enemy_Boss1::AttackZone(float dt) {
	
	if (m_IsAttacking && m_Animation->getSpriteFrame() >= m_AttackBeginFrames && m_Animation->getSpriteFrame() <= m_AttackFinishFrames) {
		//std::cout << m_Animation->getSpriteFrame() << std::endl;
		if (m_attackCollider == NULL) {
			m_attackCollider = new Collider();
			
		}
		if (m_Flip == SDL_FLIP_NONE) {
			m_attackCollider->SetBuffer(-10, -10, 40, 10);
		}
		else {
			m_attackCollider->SetBuffer(-40, -10, 50, 10);
		}
		m_attackCollider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	}
	return m_attackCollider;
}

void Enemy_Boss1::DyingHandler() {
	if (m_IsDying) {
		m_IsRunning = false;
		m_IsAttacking = false;
		m_IsHurt = false;
	}
	if (m_IsDying && m_Animation->getSpriteFrame() == 6 && m_Animation->getSpriteRow() == 5 && !m_FinishDying) {
		//std::cout << "het thuc";
		m_FinishDying = true;
		m_IsDying = false;


	}
}