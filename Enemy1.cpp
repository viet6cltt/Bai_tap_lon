#include "Enemy1.h"

#include "TextureManager.h"
#include "Character.h"
#include "Input.h"
#include <SDL.h>
#include "CollisionHandler.h"
#include<iostream>
//#include "Camera.h"
#include "Engine.h"

Enemy1::Enemy1(Properties* props) : Enemy(props)
{
	m_hasReceivedDamage["normal"] = false;
	m_hasReceivedDamage["slash"] = false;
	m_hasReceivedDamage["gravity"] = false;
	m_hasReceivedDamage["hasagi"] = false;
	m_Health = 4000;
	m_Damage = 200;
	m_IsRunning = false;

	m_IsAttacking = false;
	m_CanAttack = true;

	center = new SDL_Point;
	center->x = m_Width / 2;
	center->y = m_Height / 2;

	m_Flip = SDL_FLIP_NONE;

	m_Collider = new Collider();
	//m_Collider->SetBuffer(-45, -40, 45, 40);
	m_attackCollider = NULL;

	m_RigidBody = new RigidBody();
	//m_Position = new Vector2D;

	m_Animation = new Animation();
	m_HealthBar = new HealthBar(new Properties("enemy_bar", m_Transform->X + 70, m_Transform->Y + 43, 29, 5), m_Health);
}


void Enemy1::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip, center);
	//Vector2D cam = Camera::GetInstance()->GetPosition();
	//SDL_Rect box = m_Collider->Get();
	
	/*if (m_attackCollider != NULL) {
		SDL_Rect box1 = m_attackCollider->Get();
		SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box1);
	}*/
	
	//TextureManager::GetInstance()->Draw("enemy_bar", m_Transform->X + 70, m_Transform->Y + 43, 29, 5);
	m_HealthBar->Draw();
	//box.x -= cam.X;
	//box.y -= cam.Y;
	//SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);

}

void Enemy1::Update(float dt) {
	m_HealthBar->setProperties(m_Transform->X + 70, m_Transform->Y + 43, 29, 5);
	m_HealthBar->setCurrentHealth(m_Health);
	m_HealthBar->Update(dt);

	//m_Health -= dt;
	if (isAlive() == false) {
		Clean();
	}
	/*-------xu li tan cong-----------------*/
	if (m_IsAttacking && m_Animation->getSpriteFrame() == 7 && m_FinishAttack == false) {
		m_FinishAttack = true;
	}

	if (m_IsAttacking && m_Animation->getSpriteFrame() != 7 && m_FinishAttack) {
		if (m_attackCollider != NULL) {
			delete m_attackCollider;
			m_attackCollider = NULL;
		}
		m_IsAttacking = false;
		m_CanAttack = true;
		m_FinishAttack = false;
		m_hasDealtDamage = false;
	}
	AttackZone(dt);
	/*-----------------------------------------*/

	

	m_RigidBody->UnSetForce();

	if(!m_IsHurt && !m_IsAttacking) m_RigidBody->ApplyForce(m_Direction * RUN_FORCE);

	/*--------------------------xu li bi thuong-----------------------*/
	if (m_IsHurt) {
		m_RigidBody->UnSetForce();
		if (m_IsAttacking) {
			delete m_attackCollider;
			m_attackCollider = NULL;
		}
	}
	if (m_IsHurt && m_Animation->getSpriteFrame() == 3 && m_FinishHurt == false) {
		m_FinishHurt = true;
	}
	if (m_FinishHurt && m_Animation->getSpriteFrame() != 3) {
		m_IsHurt = false;
	}
	/*-------------------------------------------------------*/

	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->Position().X;
	m_Collider->SetBuffer(-58, -50, 110, 100);
	m_Collider->Set(m_Transform->X,m_Transform->Y , 50, 50);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->X = m_LastSafePosition.X;
	}
	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->Position().Y;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 150, 150);
	m_Collider->SetBuffer(0, 0, 0, 0);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->Y = m_LastSafePosition.Y;
	}

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	//Di chuyen theo nhan vat

	AnimationState();
	
	m_Animation->Update();


}


void Enemy1::AnimationState()
{
	std::string currentState;
	//idle
	if (!m_IsRunning && !m_IsAttacking && !m_IsHurt) {
		currentState = "idle";
		if (currentState != m_LastState) {
			m_Animation->SetProps("skeleton_idle", 1, 4, 100, 4);
			m_Animation->Start();
		}
	}

	//running
	if (m_IsRunning && !m_IsAttacking && !m_IsHurt) {
		currentState = "running";
		if (currentState != m_LastState) {
			m_Animation->SetProps("skeleton_run", 1, 4, 100, 4);
			m_Animation->Start();
		}
	}
	//attacking
	if (m_IsAttacking && !m_IsHurt) {
		currentState = "attacking";
		if (currentState != m_LastState) {
			m_Animation->SetProps("skeleton_attack", 1, 8, 150, 8);
			m_Animation->Start();
		}
	}
	//hurting
	if (m_IsHurt) {
		currentState = "hurt";
		if (currentState != m_LastState) {
			m_Animation->SetProps("skeleton_hurt", 1, 4, 100, 4);
			m_Animation->Start();
		}
	}
	m_LastState = currentState;
}



void Enemy1::Clean()
{
	//TextureManager::GetInstance()->Drop("skeleton_run");
	//TextureManager::GetInstance()->Drop("skeleton_idle");
	//TextureManager::GetInstance()->Drop("skeleton_attack");

}

Collider* Enemy1::AttackZone(float dt) {
	if (m_IsAttacking && m_Animation->getSpriteFrame() >= 6 && m_Animation->getSpriteFrame() <= 7) {
		if (m_attackCollider == NULL) {
			m_attackCollider = new Collider();
		}
		if (m_Flip == SDL_FLIP_NONE) {
			m_attackCollider->SetBuffer(-10, -50, 0, 110);
			m_attackCollider->Set(m_Transform->X + 80, m_Transform->Y, 50, m_Height);
		}
		else {
			m_attackCollider->SetBuffer(0, -50, 0, 110);
			m_attackCollider->Set(m_Transform->X + 20 , m_Transform->Y, 40, m_Height);
		}
	}
	return m_attackCollider;

}

void Enemy1::Follow_Warrior(Vector2D F)
{
	m_Position.X = m_Origin->X;
	m_Position.Y = m_Origin->Y;
	m_Direction = F - m_Position;
	
	m_Direction = m_Direction.Normalize();
	
	m_IsRunning = true;
	if (m_Direction.X > 0) {
		m_Flip = SDL_FLIP_NONE;
	}
	else if (m_Direction.X < 0) {
		m_Flip = SDL_FLIP_HORIZONTAL;
	}

}
